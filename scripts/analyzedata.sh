#!/bin/bash

#
# This script analyzes the data from the student's submissions
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

assn="$1"
tag="hw1"

#######################################
# functions

students=$(getStudentList)

# $1 = function to apply
# $2 = (optional) argument to function
function foreachStudent {
    printf "calculating $1 for each student... " >&2
    for student in $students; do
        echo $($1 $student $2)
    done
    echo "done." >&2
}

# $1 = student
# $2 = commit/tag/branch to count at
function numCommits {
    github=$(getStudentInfo "$1" github)
    cd "gradetmp/rshell-$1"
    #echo $(git rev-list --author=$github --count $2)
    echo $(git rev-list --author=$github --count $2)
    cd "../.."
}

# $1 = student
# $2 = commit/tag/branch location to measure
function timelastcommit {
    github=$(getStudentInfo "$1" github)
    cd "gradetmp/rshell-$1"
    git checkout "$2" --quiet 2> /dev/null
    #git checkout master --quiet 2> /dev/null
    git log --author=$github --pretty=format:'%at' | head -n1
    cd ../..
}

# $1 = student
# $2 = starttime
function timefirstcommit {
    local starttime="$2"
    [ -z "$2" ] && starttime=0

    github=$(getStudentInfo "$1" github)
    cd "gradetmp/rshell-$1"
    git checkout master --quiet 2> /dev/null

    #git show --summary $(git merge-base origin/ls origin/master) --pretty=format:'%at'
    git log --author=$github --pretty=format:'%at' | awk "\$1 > $starttime {print}" | tail -n1
    cd ../..
}

function totaltime {
    local starttime=$(timefirstcommit $1 $2)
    local stoptime=$(timelastcommit $1 $3)
    expr $stoptime - $starttime
}

# $1 = student
# $2 = commit/tag/branch location to measure
function linesOfCode {
    cd gradetmp/rshell-$1
    git checkout "$2" --quiet 2>/dev/null
    if [ -d src ]; then
        wc -l src/* | tail -n1 | grep -o '^[[:space:]]*[[:digit:]]*[[:space:]]'
    else
        echo 0
    fi
    cd ../..
}

# $1 = student
# $2 = commit/tag/branch location to measure
function linesOfCodeWithoutComments {
    cd gradetmp/rshell-$1
    git checkout "$2" --quiet 2>/dev/null
    local total=0
    if [ -d src ]; then
        for file in src/*; do
            if [ ! -d "$file" ] && [ "$file" != "a.out" ]; then
                local lines=$(../../scripts/rmcomments.sh $file | wc -l | grep -o '[[:digit:]]*')
                #echo "lines=$lines" >&2
                [ ! -z "$lines" ] && total=$(($total + $lines))
            fi
        done
    fi
    echo "student=$1; loc=$total" >&2
    echo $total
    cd ../..
}

# $1 = data file to generate the bar plot from;
#      data file must have a singe column of numbers and nothing else
function barplot_percent {
    file=$(basename $1)

    echo "
    set style fill solid border
    #set yrange [0:]
    #set xrange [-5:115]
    unset key
    set xtics nomirror
    set ytics 10
    set xlabel 'grade'
    set ylabel 'number of students'

    set boxwidth 2
    binwidth=3.3333333333
    bin(x)=binwidth*floor(x/binwidth)
    gradebin(x)=bin(x>100?100:x)

    green(x)=x>=90?1:0
    blue(x)=(x<90&&x>=80)?1:0
    yellow(x)=(x<80&&x>=70)?1:0
    red(x)=x<=70?1:0

    plot '$file' using (gradebin(\$1)):(green(\$1)) smooth freq with boxes lc rgb '#00cd00'   ,\
         '$file' using (gradebin(\$1)):(blue(\$1)) smooth freq with boxes lc rgb '#00cdcd'    ,\
         '$file' using (gradebin(\$1)):(yellow(\$1)) smooth freq with boxes lc rgb '#cdcd00'  ,\
         '$file' using (gradebin(\$1)):(red(\$1)) smooth freq with boxes lc rgb '#cd0000'

    #unset style
    #unset yrange
    #unset xrange
    #unset xtics
    #unset ytics
    #unset xlabel
    #unset boxwidth
    "
}

# $1 = data file to generate the scatter plot from;
#      the first column is the x-axis, the second column the y-axis
function scatterplot {
    file=$(basename $1)
    echo "
    set style fill solid border
    #set yrange [0:]
    #set xrange [1412800000:]
    set xrange [0:]
    unset key
    unset ytics
    set xtics nomirror
    set ytics 10
    #set ylabel 'grade'
    #set xlabel 'number of commits'

    f(x) = a*x + b
    fit f(x) '$file' u 1:2  via a, b

    g(x) = c*x + d
    fit g(x) '$file' u 1:2:((\$2<20)?10000:1)  via c, d
    #fit g(x) '$file' u 1:2:((\$2<20 || \$1<=0)?10000:1)  via c, d

    #plot '$file' using 1:2 with points lw 4 lc rgb '#ff0000'
    plot '$file' using 1:2 with points lw 4 lc rgb '#ff0000',\
         f(x) lw 2 lt 1 lc rgb '#ff0000',\
         g(x) lw 2 lt 2 lc rgb '#ff0000'
    "
}

# $1 = data file to generate the scatter plot from;
#      the first column is the x-axis, the second column the y-axis
# $2 = end time (or "" for no end time)
function countdown {
    file=$(basename $1)

#echo "set xtics 86400; set grid xtics" >> scratch/out.gnu

    #[ ! -z "$2" ] && date="1413961199"

    if [ -z "$2" ]; then
        date=0
        start=0
        end=14
    else
        date="$2"
        start="-14"
        end="2"
    fi

    xrange="[$(( $date + $start*86400 )) : $(( $date + $end*86400 ))]"
    xtics="\"0\" $date"
    for i in $(seq $start $end); do
        tictime=$(( $date + $i * 86400 ))
        xtics="\"$i\" $tictime, $xtics"
    done

    echo "
    set style fill solid border
    set yrange [0:120]
    set xrange $xrange #[1412800000:]
    unset key
    unset ytics
    set arrow 1 from $date,0 to $date,120 nohead
    set xtics nomirror
    set xtics ($xtics)
    set grid xtics # linestyle 1 lt 2 lw 1
    set ytics 10
    #set ylabel 'grade'
    #set xlabel 'number of commits'

    f(x) = a*x + b
    fit f(x) '$file' u 1:2  via a, b

    g(x) = c*x + d
    fit g(x) '$file' u 1:2:((\$2<20)?10000:1)  via c, d

    plot '$file' using 1:2 with points lw 4 lc rgb '#ff0000',\
         f(x) lw 2 lt 1 lc rgb '#ff0000',\
         g(x) lw 2 lt 2 lc rgb '#ff0000'

    unset arrow 1
    "
}

#######################################
# what to do

#cd scratch
#echo > datafile

[ ! -d scratch ] && mkdir scratch
datafile="scratch/datafile"
out="scratch/out.gnu"

###################
echo "generating data"

foreachStudent "echo" > $datafile.csaccount
foreachStudent "numCommits" "$tag" 2>/dev/null > $datafile.numCommits
foreachStudent "runningTotalGradePercent"  "$assn" > $datafile.totalGrade
foreachStudent "timelastcommit" "$tag" > $datafile.timelastcommit
foreachStudent "timefirstcommit" "1414011199"> $datafile.timefirstcommit
#foreachStudent "timefirstcommit" "$tag" "1415011199"> $datafile.timefirstcommit
foreachStudent "totaltime" "1414011199" "$tag" > $datafile.totaltime
foreachStudent "linesOfCode" "$tag" > $datafile.linesOfCode
#foreachStudent "linesOfCodeWithoutComments" "$tag" > $datafile.linesOfCodeWithoutComments

paste $datafile.numCommits $datafile.totalGrade > $datafile.numCommits-vs-totalGrade
paste $datafile.timelastcommit $datafile.totalGrade > $datafile.timelastcommit-vs-totalGrade
paste $datafile.timefirstcommit $datafile.totalGrade > $datafile.timefirstcommit-vs-totalGrade
paste $datafile.totaltime $datafile.totalGrade > $datafile.totaltime-vs-totalGrade
paste $datafile.linesOfCode $datafile.totalGrade > $datafile.linesOfCode-vs-totalGrade
paste $datafile.linesOfCodeWithoutComments $datafile.totalGrade > $datafile.linesOfCodeWithoutComments-vs-totalGrade

paste $datafile.csaccount $datafile.numCommits $datafile.totalGrade $datafile.timelastcommit $datafile.timefirstcommit $datafile.linesOfCode $datafile.linesOfCodeWithoutComments $datafile.totalGrade > $datafile.all

###################
echo "plotting data"

outfile="$(tr / . <<< $assn).ps"
echo "
    set terminal postscript enhanced
    set output '$outfile'

    set xrange [-20:]
    " > scratch/out.gnu

barplot_percent $datafile.totalGrade >> scratch/out.gnu

echo "
    set yrange [0:120]
    set xrange [-5:]
    set grid xtics
    " >> scratch/out.gnu

echo "set ylabel 'grade'; set xlabel 'number of commits'" >> scratch/out.gnu
scatterplot $datafile.numCommits-vs-totalGrade >> scratch/out.gnu
echo "set ylabel 'grade'; set xlabel 'lines of code' " >> scratch/out.gnu
scatterplot $datafile.linesOfCode-vs-totalGrade >> scratch/out.gnu
#echo "set ylabel 'grade'; set xlabel 'lines of code (without comments)' " >> scratch/out.gnu
#scatterplot $datafile.linesOfCodeWithoutComments-vs-totalGrade >> scratch/out.gnu

assn0duedate="1413961199"
assn1duedate="1415750400"
duedate=$assn1duedate
echo "set ylabel 'grade'; set xlabel 'time of last commit' " >> scratch/out.gnu
countdown $datafile.timelastcommit-vs-totalGrade "$duedate" >> scratch/out.gnu
echo "set ylabel 'grade'; set xlabel 'time of first commit' " >> scratch/out.gnu
countdown $datafile.timefirstcommit-vs-totalGrade "$duedate" >> scratch/out.gnu
echo "set ylabel 'grade'; set xlabel 'total time' " >> scratch/out.gnu
countdown $datafile.totaltime-vs-totalGrade >> scratch/out.gnu

cd scratch
gnuplot out.gnu
#
