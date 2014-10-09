#!/bin/bash

#
# This script contains common configuration settings and functions.
#

set -a

#######################################
# configuration

# the github project name
classname="ucr-cs100"

# tmp folder for all student repos
tmpdir="gradetmp"

# branch of student git repository that stores the grades
gradesbranch="grades"

# folder containing instructor pgp keys
instructorinfo="people/instructors"

# folder containing student information
studentinfo="people/students"

#######################################
# let us quit the shell even if we're in a subshell

trap "exit 1" TERM
export TOP_PID=$$

function failScript {
    kill -s TERM $TOP_PID
}

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
    elif [ ${#1} = 4 ]; then
        printf "  "
    elif [ "$1" = 0 ]; then
        printf "  0.0"
    fi
    printf "$1"
}

function error {
    echo "ERROR: $@" >&2
    failScript
}

#######################################
# get student info

# $1 = the student's csaccount (which is the name of file containing their info)
# $2 = the attribute you want about the student
function getStudentInfo {
    if [ ! -e "$studentinfo/$1" ]; then
        error "student $1 does not exist"
    fi
    if [ -z "$2" ]; then
        error "attribute not given"
    fi

    # FIXME: this matches any attribute that contains $2 rather than equals $2
    ret=$(awk -F "=" "/^$2/ {print \$2}" "$studentinfo/$1" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    if [ -z "$ret" ]; then
        error "student $1 does not have attribute $2 in their studentinfo file"
    fi
    echo "$ret"
}

function getStudentList {
    for file in $studentinfo/*; do
        basename "$file"
    done
}

#######################################
# download/edit grades

function downloadAllGrades {
    downloadAllProjects "$classname" "$gradesbranch"
}

# $1 = csaccount of student to download grades for
function downloadGrades {
    giturl="$(getStudentInfo $1 giturl)"
    clonedir="$tmpdir/$classname-$1"
    downloadRepo "$clonedir" "$giturl" "$gradesbranch"
}

# $1 = the name of the repo on github that has the students' projects
# $2 = [optional] branch of project to enter
function downloadAllProjects {
    echo "downloading repos..."
    accountlist=""
    for student in $(getStudentList); do
        githubaccount=$(getStudentInfo $student github)
        accountlist="$accountlist $githubaccount"
    done

    # NOTE: this weird xargs command runs all of the downloadProject functions in parallel
    if ! (echo "$accountlist" | xargs -n 1 -P 4 bash -c "downloadProject $1 \$1 $2" -- ); then
        echo "ERROR: some repos failed to download;"
        echo "sometimes we exceed github's connection limits due to parallel downloading;"
        echo "trying again might work?"
        echo
        exit 1
    fi
    echo "done"
}

# $1 = project name
# $2 = github account of user
# $3 = [optional] branch of project to enter
function downloadProject {
    downloadRepo "$tmpdir/$1-$2" "https://github.com/$2/$1.git" "$3"
}

# $1 = the directory to place the repo
# $2 = the repo's url (not necessarily on github)
# $3 = [optional] branch to enter in the repo
function downloadRepo {
    local clonedir="$1"
    local giturl="$2"
    local branch="$3"

    local dir=$(pwd)

    # download repo
    if [ ! -d "$clonedir" ]; then
        echo "  running git clone on [$giturl]"
        git clone --quiet "$giturl" "$clonedir"
    else
        echo "  running git pull in [$clonedir]"
        cd "$clonedir"
        git pull origin --quiet > /dev/null 2> /dev/null
        cd "$dir"
    fi

    # switch branch
    if [ ! -z "$branch" ]; then
        cd "$clonedir"
        if git show-ref --verify --quiet "refs/heads/$branch"; then
            git checkout "$branch" --quiet
        else
            git checkout -b "$branch" --quiet
        fi
        cd "$dir"
    fi
}

# $1 = the cs account of the student to upload grades
function uploadgrades {
    clonedir="$tmpdir/$classname-$1"
    cd "$clonedir"
    for file in `find . -name grade`; do
        git add $file
    done
    git commit -S -m "graded assignment using automatic scripts"

    echo "changes committed... uploading to github"
    git push origin "$gradesbranch"
    # FIXME: we should be reporting an error if git fails... but how?
    #if [ $? ]; then
        #echo "upload successful :)"
    #else
        #echo "upload failed :( error code: $?"
    #fi
    cd ../..
}

# $1 = the path of the grade file to edit
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


