#!/bin/bash

# 
# This script takes as a parameter an assignment folder.  Then it iterates
# through the grades of everyone enrolled in the class and lets the 
# user enter grades for each assignment.
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

########################################
# check for valid command line params

assn="$1"
if [ -z $assn ]; then
    echo "no assignment given"
    exit
fi

#######################################
# grade assignment

# tells git to keep the username and password in memory for the next 15 minutes
git config --global credential.helper cache

for student in studentinfo/*; do
    csaccount=`basename $student`
    name=`head -n 1 $student`
    githubaccount=`tail -n 1 $student`

    downloadgrades "$githubaccount"
    gradefile "$tmpdir/$classname-$githubaccount/$assn/grade"
    uploadgrades "$githubaccount"
done    
