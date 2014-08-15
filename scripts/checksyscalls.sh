#!/bin/bash

# 
# This script takes any number of CPP files as parameters.  For each file, it
# checks to see if there is a matching call to perror for every syscall.  If
# there is not, we assume that proper error checking is not happening.  Then
# we output a grade modifier that deducts 5 points for every extra syscall.
#
# BUGS: This script will only detect syscalls if they are immediately followed
# by a parenthesis.  This should never overcount syscalls, but could undercount
# them in the presence of macros, function pointers, or other fanciness.
#
scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

if [ -z $1 ]; then
    echo "expecting a file to grade"
fi

# we'll pipe files through these commands to remove spurious counts
rmcomments="$scriptdir/rmcomments.sh"
rmstr="sed s/\"[^\"]*\"//g"
rminclude="sed s/#.*//"

# define all the regexes for syscalls likely to be used by students
syscalls="
    getlogin
    getlogin_r
    gethostname
    execl
    execle
    execlp 
    execv 
    execvl
    execvp 
    fork
    wait
    waitpid
    open
    read
    write
    readdir
    readdir_r
    stat
    pipe
    dup2
    dup
    chdir
    getcwd
    getwd
    get_current_directory_name
    signal
    sigaction
    "

# calculate number of syscalls
echo
echo "lines with syscalls:"
numsyscalls="0"
for syscall in $syscalls; do
    lines=`cat $@ | "$rmcomments" | $rmstr | $rminclude | grep -n -e "\<$syscall\> *("`
    count=0
    if [ ! -z "$lines" ]; then
        IFS=$'\n'
        for line in $lines; do
            echo "  $line"
        done
        IFS=" "
        count=`echo $lines | wc -l`
    fi
    numsyscalls=$[$numsyscalls + $count]
done

# calculate number of perror
echo
echo "lines with perror:"
lines=`cat $@ | "$rmcomments" | $rmstr | $rminclude | grep -n -e "\<perror\>"` 
numperror=0
if [ ! -z "$lines" ]; then
    IFS=$'\n'
    for line in $lines; do
        echo "  $line"
    done
    IFS=" "
    numperror=`echo "$lines" | wc -l`
fi

# calculate the grade modifier
grademod="0"
if [ "$numperror" -lt "$numsyscalls" ]; then
    grademod=$[ 5 * ($numsyscalls - $numperror) ]
fi

# output results
echo 
echo "summary:"
echo "  number of syscalls... $numsyscalls"
echo "  number of perror..... $numperror"
echo "  grade modifier....... -$grademod"

#echo
#echo "relevant system calls:"
#for syscall in $syscalls; do
    #cat $@ | $rmcomments | $rmstr | grep -ne "$syscall" "$1"
#done
#
#echo
#echo "relevant perror calls:"
#cat $@ | $rmcomments | $rmstr | grep -ne "\<perror\>" "$1"

exit $grademod
