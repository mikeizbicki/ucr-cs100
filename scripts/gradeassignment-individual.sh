#!/bin/bash

#
# This script takes two parameters: a github account and an assignment folder.
# It then opens the associated grade file, let's the user edit it, and
# uploads the modified grades to github.
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

########################################
# check for valid command line params

user=$(simplifycsaccount "$1")
if [ -z $user ]; then
    echo "no user name given"
    exit
fi

assn="$2"
if [ -z $assn ]; then
    echo "no assignment given"
    exit
fi

#######################################
# grade assignment

downloadGrades $user

gradeAssignment "$user" "$assn"

uploadGrades $user
