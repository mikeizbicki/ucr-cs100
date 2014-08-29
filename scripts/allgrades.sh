#!/bin/bash

#
# This script displays the grades of all users enrolled in the class.
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

#######################################
# display

echo "================================================================================"
echo " name                 | cs account | github account   | points      | percent  "
echo "================================================================================"

for file in studentinfo/*; do
    csaccount=`basename $file`
    name=`head -n 1 $file`
    githubaccount=`tail -n 1 $file`
    downloadgrades "$githubaccount"
    
    totalgrade=`totalGrade "$githubaccount"`
    totaloutof=`totalOutOf "$githubaccount"`
    rtotaloutof=`runningTotalOutOf "$githubaccount"`
    rpercent=`bc <<< "scale=2; 100 * $totalgrade/$rtotaloutof"`
    percent=`bc <<< "scale=2; 100 * $totalgrade/$totaloutof"`

    printf " $(pad "$name" 20) |"
    printf " $(pad "$csaccount" 10) |"
    printf " $(pad "$githubaccount" 16) |"
    printf " %4s / %4s | $rpercent " $totalgrade $rtotaloutof
    echo
done

echo "================================================================================"
