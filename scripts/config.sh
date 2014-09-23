#!/bin/bash

#
# This script contains common configuration settings and functions.
#

#######################################
# configuration

# the github project name
classname="ucr-cs100"

# tmp folder for all student repos
tmpdir="gradetmp"

# folder containing instructor pgp keys
instructorinfo="instructorinfo"

#######################################
# misc display functions

# pad the input $1 with extra spaces so that is has exactly length $2
function pad {
    ret="${1:0:$2}                                                  "
    ret="${ret:0:$2}"
    echo "$ret"
}

# add the padding to the left
function padPercent {
    if [ ${#1} = 5 ]; then
        printf " "
    elif [ "$1" = 0 ]; then
        printf "  0.0"
    fi
    printf "$1"
}

#######################################
# download/edit grades

function downloadAllProjects {
    local proj="$1"
    echo "downloading repos..."
    accountlist=""
    for file in studentinfo/*; do
        githubaccount=`tail -n 1 $file`
        accountlist="$accountlist $githubaccount"
    done
        
    if ! (echo "$accountlist" | xargs -n 1 -P 4 "$scriptdir/downloadproject.sh" "$proj"); then
        echo "ERROR: some repos failed to download; sometimes we exceed github's connection limits due to parallel downloading; trying again might work?"
        exit 1
    fi
    echo "done"
}

function downloadAllGrades {
    downloadAllProjects "$classname"
}

function downloadgrades {
    "$scriptdir/downloadproject.sh" "$classname" "$1"
    #downloadproject "$1" "$classname"
}

function uploadgrades {
    local user=$1
    clonedir="$tmpdir/$classname-$user"
    cd "$clonedir"
    for f in `find . -name grade`; do
        git add $f
    done
    git commit -S -m "graded assignment using automatic scripts"

    echo "changes committed... uploading to github"
    git push origin
    #if [ $? ]; then
        #echo "upload successful :)"
    #else
        #echo "upload failed :( error code: $?"
    #fi
    cd ../..
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
    sed -i "/^\#/d" "$file" 
}

#######################################
# parsing grades

function isGraded {
    # is the first word in the file $1 is "/", then it is not graded
    return `! grep '^[[:blank:]]*/' -q "$1"`
}

function getGrade {
    head -n 1 "$1" | sed 's/\// /' | awk '{print $1;}'
}

function getOutOf {
    if isGraded $1; then
        head -n 1 "$1" | sed 's/\// /' | awk '{print $2;}'
    else
        head -n 1 "$1" | sed 's/\// /' | awk '{print $1;}'
    fi
}

# calculates the total points for user $1 in directory $2
function totalGrade {
    local totalgrade=0
    local assn="$2"
    if [ -z "$assn" ]; then
        assn="."
    fi
    for f in `find "./$tmpdir/$classname-$1/$assn" -name grade`; do
        if isGraded "$f"; then
            local grade=$(getGrade "$f")
            totalgrade=$[$totalgrade+$grade]
        fi
    done
    echo $totalgrade
}

# calculates the total possible points for user $1 in directory $2 on submitted assignments only
function runningTotalOutOf {
    totaloutof=0
    local assn="$2"
    if [ -z "$assn" ]; then
        assn="."
    fi
    for f in `find "./$tmpdir/$classname-$1/$assn" -name grade`; do
        if isGraded "$f"; then
            local outof=$(getOutOf "$f")
            totaloutof=$[$totaloutof+$outof]
        fi
    done
    echo "$totaloutof"
}

# calculates the total possible points for user $1 in directory $2 on all assignments 
# this function is used for calculating the final grade
function totalOutOf {
    totaloutof=0
    if [ -z "$assn" ]; then
        assn="."
    fi
    for f in `find "./$tmpdir/$classname-$1/$assn" -name grade`; do
        local outof=$(getOutOf "$f")
        totaloutof=$[$totaloutof+$outof]
    done
    echo "$totaloutof"
}

#######################################
# displaying grades

function colorPercent {
    local per="$1"
    if [[ -z $1 ]]; then
        resetColor
    elif ((`bc <<< "$per>90"`)); then
        printf "\x1b[32m"
    elif ((`bc <<< "$per>80"`)); then
        printf "\x1b[36m"
    elif ((`bc <<< "$per>70"`)); then
        printf "\x1b[33m"
    else
        printf "\x1b[31m"
    fi
}

function resetColor {
    printf "\x1b[0m"
}

function dispPercent {
    local per="$1"
    colorPercent "$per"
    printf "$(padPercent $per)"
    resetColor
}

function percentToLetter {
    per="$1"
    colorPercent "$1"
    if ((`bc <<< "$per>97"`)); then
        printf "A+"
    elif ((`bc <<< "$per>93"`)); then
        printf "A "
    elif ((`bc <<< "$per>90"`)); then
        printf "A-"
    elif ((`bc <<< "$per>87"`)); then
        printf "B+"
    elif ((`bc <<< "$per>83"`)); then
        printf "B "
    elif ((`bc <<< "$per>80"`)); then
        printf "B-"
    elif ((`bc <<< "$per>77"`)); then
        printf "C+"
    elif ((`bc <<< "$per>73"`)); then
        printf "C "
    elif ((`bc <<< "$per>70"`)); then
        printf "C-"
    elif ((`bc <<< "$per>67"`)); then
        printf "D+"
    elif ((`bc <<< "$per>63"`)); then
        printf "D "
    elif ((`bc <<< "$per>60"`)); then
        printf "D-"
    else
        printf "F "
    fi
    resetColor
}


