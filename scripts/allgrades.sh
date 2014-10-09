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
    #csaccount=`basename $file`
    #name=`head -n 1 $file`
    #githubaccount=`tail -n 1 $file`
   #
    totalgrade=`totalGrade "$githubaccount" "$assn"`
    totaloutof=`totalOutOf "$githubaccount" "$assn"`
    rtotaloutof=`runningTotalOutOf "$githubaccount" "$assn"`
    rpercent=`bc <<< "scale=2; 100 * $totalgrade/$rtotaloutof"`
    percent=`bc <<< "scale=2; 100 * $totalgrade/$totaloutof"`

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

#plotting

#echo "1 " > datafile
#echo "4 " >> datafile
#echo "13 " >> datafile
#echo "21 " >> datafile
#outfile="test"
#tmpfile=`mktemp`
#echo -e "$percentlist" > "$tmpfile"
#gnuplot <<< "
#set terminal pngcairo enhanced size 500,300
#set output '$outfile.png'
#
#set style fill solid border
#set yrange [0:]
#set xrange [-5:105]
#unset key
#unset ytics
#set xtics nomirror
#
#set boxwidth 2
#binwidth=3.3333333333
#bin(x)=binwidth*floor(x/binwidth)
#gradebin(x)=bin(x>100?100:x)
#
#green(x)=x>90?1:0
#blue(x)=(x<=90&&x>80)?1:0
#yellow(x)=(x<=80&&x>70)?1:0
#red(x)=x<=70?1:0
#
#plot '$tmpfile' using (gradebin(\$1)):(green(\$1)) smooth freq with boxes lc rgb '#00cd00'   ,\
     #'$tmpfile' using (gradebin(\$1)):(blue(\$1)) smooth freq with boxes lc rgb '#00cdcd'    ,\
     #'$tmpfile' using (gradebin(\$1)):(yellow(\$1)) smooth freq with boxes lc rgb '#cdcd00'  ,\
     #'$tmpfile' using (gradebin(\$1)):(red(\$1)) smooth freq with boxes lc rgb '#cd0000' \
#" > "$outfile.png"
