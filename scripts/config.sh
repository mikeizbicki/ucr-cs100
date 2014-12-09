#!/bin/bash

#
# This script contains common configuration settings and functions.
#

cd $scriptdir

# export all variables to subshells
set -a

#######################################
# configuration (can be modified)

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
# initialization (do not modify!)

# let us quit the shell even if we're in a subshell
trap "exit 1" TERM
export TOP_PID=$$

function failScript {
    kill -s TERM $TOP_PID
}

# cd to the repo's root folder by backtracking until we find the LICENSE file
# this let's the scripts be run from any folder in the repo
while [ ! -e "LICENSE" ]; do
    cd ..
done

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

##########################################
#colors
red="\x1b[31m"
green="\x1b[32m"
yellow="\x1b[33m"
blue="\x1b[34m"
mag="\x1b[35m"
cyn="\x1b[36m"
endcolor="\x1b[0m"

function error {
    echo -e "$red ERROR: $@$endcolor" >&2
    failScript
}
function warning
{
    echo -e "$yellow WARN: $@$endcolor" >&2
}

#######################################
# get student info

# prints the names of the csaccount of each student on a separate line
function getStudentList {
    for file in $studentinfo/*; do
        basename "$file"
    done
}

# $1 = the student's csaccount (which is the name of file containing their info)
# $2 = the attribute you want about the student
function getStudentInfo {
    #csaccount=$(simplifycsaccount $1)
    #if [ -z "$csaccount" ] || [ ! -e "$studentinfo/$csaccount" ]; then
        #error "student $csaccount does not exist"
    #fi
    csaccount="$1"
    if [ -z "$2" ]; then
        error "attribute not given"
    fi

    # FIXME: this matches any attribute that contains $2 rather than equals $2
    ret=$(awk -F "=" "/^$2/ {print \$2}" "$studentinfo/$csaccount" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')
    if [ -z "$ret" ]; then
        error "student $csaccount does not have attribute $2 in their studentinfo file"
    fi
    echo "$ret"
}

# $1 = the student's csaccount (which is the name of file containing their info)
#      OR a string of the form "github=XXX" where XXX is the student's github account
# output is the student's csaccount
function simplifycsaccount {
    local csaccount="$1"
    if [ $(echo "$1" | cut -d'=' -f 1) = "github" ]; then
        csaccount=$(github2csaccount $(echo "$1" | cut -d'=' -f 2))
    fi
    echo "$csaccount"
}

# $1 = the student's github account
function github2csaccount {
    local student=$(grep -r "^[[:space:]]*github[[:space:]]*=[[:space:]]*$1[[:space:]]*\$" ./people/students/ | cut -d':' -f 1)
    if [ ! -z "$student" ]; then
        basename "$student"
    else
        error "github account $1 is not registered"
    fi
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

    # tells git to keep the username and password in memory for the next 15 minutes
    git config credential.helper cache

    echo "downloading repos..."
    accountlist=$(getStudentList)

    # this weird xargs command runs all of the downloadProject functions in parallel
    if ! (echo "$accountlist" | xargs -n 1 -P 100 bash -c "downloadProject $1 \$1 $2" -- ); then
    #if ! (echo "$accountlist" | xargs -n 1 -P 1 bash -c "downloadProject $1 \$1 $2" -- ); then
        echo "ERROR: some repos failed to download;"
        echo "sometimes we exceed github's connection limits due to parallel downloading;"
        echo "trying again might work?"
        echo
        exit 1
    fi
    echo "done"
}

# $1 = project name
# $2 = csaccount of user
# $3 = [optional] branch of project to enter
function downloadProject {
    github=$(getStudentInfo $2 github)
    downloadRepo "$tmpdir/$1-$2" "https://github.com/$github/$1.git" "$3"
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
        #if [ -z "$branch" ]; then
            git clone --quiet "$giturl" "$clonedir"
        #else
            #git clone -b "$branch" --quiet "$giturl" "$clonedir"
        #fi
    else
        echo "  running git pull in [$clonedir]"
        cd "$clonedir"
        git pull origin $branch --quiet > /dev/null 2> /dev/null
        cd "$dir"
    fi

    # switch branch
    if [ ! -z "$branch" ]; then
        cd "$clonedir"
        if git show-ref --verify --quiet "refs/heads/$branch"; then
            git checkout "$branch" --quiet
            git pull origin "$branch" --quiet > /dev/null 2> /dev/null
        else
            git checkout -b "$branch" --quiet
        fi
        cd "$dir"
    fi
}

function uploadAllGrades {
    # tells git to keep the username and password in memory for the next 15 minutes
    git config credential.helper cache

    echo "uploading repos..."
    accountlist=$(getStudentList)

    # this weird xargs command runs all of the uploadGrades functions in parallel
    if ! (echo "$accountlist" | xargs -n 1 -P 4 bash -c "uploadGrades \$1" -- ); then
        error "ERROR: some repos failed to upload; sometimes we exceed github's connection limits due to parallel uploading; trying again might work?"
    fi
    echo "done"
}

# $1 = the cs account of the student to upload grades
function uploadGrades {
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

# $1 = the csaccount of the student
# $2 = the assignment to grade
function gradeAssignment {
    local csaccount="$1"
    local assn="$2"
    local name=$(getStudentInfo "$csaccount" name)
    local githubaccount=$(getStudentInfo "$csaccount" "github")

    local file="$tmpdir/$classname-$csaccount/$assn/grade"

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

# $1 = the grade file
function isGraded {
    # is the first word in the file $1 is "/", then it is not graded
    return `! grep '^[[:blank:]]*/' -q "$1"`
}

# $1 = the grade file
function getGrade {
    head -n 1 "$1" | sed 's/\// /' | awk '{print $1;}'
}

# $1 = the grade file
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

# calculates the current percentage for user $1 in directory $2
function runningTotalGradePercent {
    mkPercent $(totalGrade $1 $2) $(runningTotalOutOf $1 $2)
}

# calculates the final percentage for user $1 in directory $2
function totalGradePercent {
    mkPercent $(totalGrade $1 $2) $(totalOutOf $1 $2)
}

#######################################
# displaying grades

# $1 = numerator
# $2 = denominator
function mkPercent {
    if [ "$2" = "0" ]; then
        #echo "NaN"
        if [ "$1" = "0" ]; then
            echo "0.00"
        else
            echo "100.00"
        fi
    else
        bc <<< "scale=2; 100 * $1/$2"
    fi
}

# $1 = percent
function colorPercent {
    local per="$1"
    if [[ -z $1 ]]; then
        resetColor
    elif ((`bc <<< "$per>90"`)); then
        printf "$green"
    elif ((`bc <<< "$per>80"`)); then
        printf "$cyn"
    elif ((`bc <<< "$per>70"`)); then
        printf "$yellow"
    else
        printf "$red"
    fi
}

function resetColor {
    printf "$endcolor"
}

# $1 = percent
function dispPercent {
    local per="$1"
    colorPercent "$per"
    printf "$(padPercent $per)"
    resetColor
}

# $1 = percent
function percentToLetter {
    per="$1"
    colorPercent "$1"
    if ((`bc <<< "$per>=97"`)); then
        printf "A+"
    elif ((`bc <<< "$per>=93"`)); then
        printf "A "
    elif ((`bc <<< "$per>=90"`)); then
        printf "A-"
    elif ((`bc <<< "$per>=87"`)); then
        printf "B+"
    elif ((`bc <<< "$per>=83"`)); then
        printf "B "
    elif ((`bc <<< "$per>=80"`)); then
        printf "B-"
    elif ((`bc <<< "$per>=77"`)); then
        printf "C+"
    elif ((`bc <<< "$per>=73"`)); then
        printf "C "
    elif ((`bc <<< "$per>=70"`)); then
        printf "C-"
    elif ((`bc <<< "$per>=67"`)); then
        printf "D+"
    elif ((`bc <<< "$per>=63"`)); then
        printf "D "
    elif ((`bc <<< "$per>=60"`)); then
        printf "D-"
    else
        printf "F "
    fi
    resetColor
}

##################################
#checks if a public key is in the instructor files
# $1 = file to check
# $2 = key to compare
function includesKey
{
    local instructor=$1
    local key=$2

    if [ ! -f $instructor ]; then
        return 1
    fi

    local instructorKeys=$( gpg --with-fingerprint $instructor | sed -n '/pub/p' | cut -c 12,13,14,15,16,17,18,19 )

    if [[ $instructorKeys == *$key* ]]; then
        return 0
    else
        return 1
    fi
}

##########################################
#checks if keys are installed
checkKeys()
{
    which gpg > /dev/null 2> /dev/null
    if [ ! $? -eq 0 ];then
        error "you need to install gpg:$yellow https://www.gnupg.org/download/"
    fi
    for INST in people/instructors/*;do
        local STR=${INST##*/}
        if [[ $STR == *@* ]];then
            gpg --list-keys $STR  > /dev/null 2> /dev/null
            if [ ! $? -eq 0 ] ;then
                warning "Instructor keys were not installed! Installing..."
                scripts/install-instructor-keys.sh
                echo -e "$green Done installing keys!!$endcolor"
            fi
        fi
    done
}

