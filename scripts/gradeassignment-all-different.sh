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

downloadAllGrades

for file in $studentinfo/*; do
    csaccount=$(basename $file)
    gradeAssignment "$csaccount" "$assn"
done

uploadAllGrades
