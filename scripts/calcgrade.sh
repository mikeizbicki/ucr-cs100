#!/bin/bash

#
# This script takes a github account as a parameter.  It then displays all the
# grades associated with the account
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

########################################
# check for valid command line params

user="$1"
if [ -z $user ]
then
    echo "no user name given"
    exit
fi

#######################################
# calculate stats

echo "finding grade for github account $user"
downloadgrades "$user"

totalgrade=$(totalGrade "$user")
runningtotaloutof=$(runningTotalOutOf "$user")
totaloutof=$(totalOutOf "$user")

runningpercent=`bc <<< "scale=2; 100 * $totalgrade / $runningtotaloutof"`
percent=`bc <<< "scale=2; 100 * $totalgrade/$totaloutof"`

#######################################
# display everything

echo
echo "==========================================="
echo "    grade        |  assignment"
echo "==========================================="

for f in `find "./$classname-$user" -name grade | sort`; do
    dir=`dirname $f`
    assn=`basename $dir`
    grade="---"
    if isGraded "$f"; then
        grade=$(getGrade "$f")
    fi
    outof=$(getOutOf "$f")
    printf "    %3s / %3s    |  $assn\n" "$grade" "$outof"
done

echo "==========================================="
echo

printf "running total = %4s / %4s = %1.2f\n" $totalgrade $runningtotaloutof $runningpercent
printf "overall total = %4s / %4s = %1.2f\n" $totalgrade $totaloutof $percent
echo
echo
