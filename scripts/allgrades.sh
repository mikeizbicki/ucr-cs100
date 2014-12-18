#!/bin/bash

#
# This script displays the grades of all users enrolled in the class.
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

assn="$1"

#######################################
# display

downloadAllGrades

echo "================================================================================"
echo " cs account | name                | pnts /  run ( tot) | grade run  | grade tot "
echo "================================================================================"

percentlist=""
for csaccount in $(getStudentList); do
    name=$(getStudentInfo $csaccount name)
    githubaccount=$(getStudentInfo $csaccount github)

    totalgrade=`totalGrade "$csaccount" "$assn"`
    totaloutof=`totalOutOf "$csaccount" "$assn"`
    rtotaloutof=`runningTotalOutOf "$csaccount" "$assn"`
    rpercent=$(mkPercent $totalgrade $rtotaloutof)
    percent=$(mkPercent $totalgrade $totaloutof)
    #rpercent=`bc <<< "scale=2; 100 * $totalgrade/$rtotaloutof"`
    #percent=`bc <<< "scale=2; 100 * $totalgrade/$totaloutof"`

    percentlist="$percentlist\n$percent"

    printf " $(pad "$csaccount" 10) |"
    printf " $(pad "$name" 19) |"
    printf " %4s / %4s (%4s) | " $totalgrade $rtotaloutof $totaloutof
    dispPercent "$rpercent"
    printf "  "
    percentToLetter "$rpercent"
    printf " | "
    dispPercent "$percent"
    printf "  "
    percentToLetter "$percent"
    echo
done

echo "================================================================================"
