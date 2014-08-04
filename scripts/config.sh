#!/bin/bash

#
# This script contains common configuration settings and functions.
#

#######################################
# configuration

# the github project name
classname="ucr-cs100"

#######################################
# download/edit grades

function downloadgrades {
    local user=$1
    clonedir="$classname-$user"
    if [ ! -d "$clonedir" ]; then
        giturl="https://github.com/$user/$classname.git"
        git clone --quiet "$giturl" "$clonedir" 
    else
        cd "$clonedir"
        git pull origin --quiet > /dev/null
        cd ..
    fi

    #cd $clonedir
    #git checkout --quiet init
    #cd ..
}

function uploadgrades {
    local user=$1
    clonedir="$classname-$user"
    cd "$clonedir"
    for f in `find . -name grade`; do
        git add $f
    done
    git commit -m "graded assignment using automatic scripts"

    echo "changes committed... uploading to github"
    git push origin
    #if [ $? ]; then
        #echo "upload successful :)"
    #else
        #echo "upload failed :( error code: $?"
    #fi
    cd ..
}

function gradefile {
    file="$1"

    mkdir -p `dirname $1`

    # let the grader know who they're grading
    echo "#####################################" >> "$file"
    echo "#" >> "$file"
    echo "# $file" >> "$file"
    echo "#" >> "$file"
    echo "# name      = $name" >> "$file"
    echo "# csaccount = $csaccount" >> "$file"
    echo "# github    = $githubaccount" >> "$file"
    echo "#" >> "$file"
    echo "# any line that begins with a # is a comment and won't be written to the file" >> "$file"
    echo "#" >> "$file"
    echo "#####################################" >> "$file"

    vim "$file"

    # delete all the comments from the file
    tmpfile="${file}.tmp"
    sed "/^\#/d" "$file" > "$tmpfile"
    rm "$file"
    mv "$tmpfile" "$file"

    # FIXME: the above implementation is unsafe whenever the tmpfile already exists
    # sed can't write to it's own output, though
}

#######################################
# parsing grades

function isGraded {
    # is the first word in the file $1 is "/", then it is not graded
    return `! grep '^[[:blank:]]*/' -q "$1"`
}

function getGrade {
    head -n 1 "$1" | awk '{print $1;}'
}

function getOutOf {
    if isGraded $1; then
        head -n 1 "$1" | awk '{print $3;}'
    else
        head -n 1 "$1" | awk '{print $2;}'
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

#######################################
# misc functions

# pad the input $1 with extra zeros so that is has exactly length $2
function pad {
    ret="${1:0:$2}                                                  "
    ret="${ret:0:$2}"
    echo "$ret"
}
