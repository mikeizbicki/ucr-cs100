#!/bin/bash

classname="ucr-cs100"

###############################################################################

function downloadgrades {
    local user=$1
    clonedir="$classname-$user"
    if [ ! -d "$clonedir" ]; then
        giturl="https://github.com/$user/$classname.git"
        git clone --quiet "$giturl" "$clonedir" 
    else
        cd "$clonedir"
        git pull origin #--quiet
        cd ..
    fi

    cd $clonedir
    git checkout --quiet init
    cd ..
}

function isGraded {
    # is the first word in the file $1 is "/", then it is not graded
    return `! grep '^[[:blank:]]*/' -q "$1"`
}

function getGrade {
    cat "$1" | awk '{print $1;}'
}

function getOutOf {
    if isGraded $1; then
        cat "$1" | awk '{print $3;}'
    else
        cat "$1" | awk '{print $2;}'
    fi
}

function totalGrade {
    local totalgrade=0
    for f in `find "./$classname-$1" -name grade`; do
        if isGraded "$f"; then
            local grade=$(getGrade "$f")
            totalgrade=$[$totalgrade+$grade]
        fi
    done
    echo $totalgrade
}

function runningTotalOutOf {
    totaloutof=0
    for f in `find "./$classname-$1/" -name grade`; do
        if isGraded "$f"; then
            local outof=$(getOutOf "$f")
            totaloutof=$[$totaloutof+$outof]
        fi
    done
    echo "$totaloutof"
}

function totalOutOf {
    totaloutof=0
    for f in `find "./$classname-$1/" -name grade`; do
        local outof=$(getOutOf "$f")
        totaloutof=$[$totaloutof+$outof]
    done
    echo "$totaloutof"
}

