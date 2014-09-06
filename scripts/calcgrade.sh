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
if [ -z $user ]; then 
    echo "no github account given"
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

for f in `find "./$tmpdir/$classname-$user" -name grade | sort`; do
    dir=`dirname $f`
    assn=`basename $dir`
    grade="---"
    if isGraded "$f"; then
        grade=$(getGrade "$f")
    fi
    outof=$(getOutOf "$f")

    if [ ! $grade = "---" ]; then 
        cmd="scale=2; 100*$grade/$outof"
        assnPercent=$(bc <<< "$cmd" 2> /dev/null)
        colorPercent "$assnPercent"
        printf "    %3s / %3s    " "$grade" "$outof"
        resetColor
        printf "|"
        colorPercent "$assnPercent"
        printf "  $assn\n" 
        resetColor
    else
        printf "    %3s / %3s    " "$grade" "$outof"
        printf "|"
        printf "  $assn\n" 
    fi
done

echo "==========================================="
echo

printf "running total = %4s / %4s = " $totalgrade $runningtotaloutof 
dispPercent "$runningpercent"
printf "  "
percentToLetter "$runningpercent"
echo
printf "overall total = %4s / %4s = " $totalgrade $totaloutof 
dispPercent "$percent"
printf "  "
percentToLetter "$percent"
echo
echo
