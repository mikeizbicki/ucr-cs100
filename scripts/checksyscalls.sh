#!/bin/bash

#This function takes in argument folder or files and puts them in an array called FILES. 
#I am aware that this does not work for folders inside folders but I do not know recursion yet.
CURR=1

for f in "$@"
do
   if [[ -d $f ]]; then
      for s in "$f"*
      do
         FILES[$CURR]=$s
         CURR=$((CURR+1))
      done
 
   else
      FILES[$CURR]=$f
      CURR=$((CURR+1))
   fi
done


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
    echo "usage: $0 filetograde"
    exit 1
fi

# we'll pipe files through these commands to remove spurious counts
rmcomments="$scriptdir/rmcomments.sh"
rmstr="sed s/\"[^\"]*\"//g"
rminclude="sed s/#.*//"

# define all the regexes for syscalls likely to be used by students
syscalls='
		ioctl
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
    close
    read
    readlink
    write
    opendir
    closedir
    readdir
    readdir_r
    lstat
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
    getpwuid
    getgrgid
    '

#The new assigment takes care to no include calls like ifs.close()
#which is not a syscall but a member function.
#It also includes the edge case where the call may start with no 
#whitespaces on the left.
args=""
for syscall in $syscalls; do
args="$args -e [^._]\<$syscall\>[^(]*([^)]*) -e ^\<$syscall\>[^(]*([^)]*) "
#args="$args -e $syscall[^(]*([^)]*) "
done

# calculate number of syscalls
syscalls=`cat ${FILES[@]} | "$rmcomments" | $rmstr | $rminclude | sed -e 's/^[ \t]*//' | grep -e -o $args -n | sed -e 's/^\([1234567890][1234567890]\):/0\1:/' | sed -e 's/\([1234567890]\):/\1:  /'`
numsyscalls=$(echo "$syscalls" | wc -l)

# calculate number of perror
perrors=`cat ${FILES[@]} | "$rmcomments" | $rmstr | $rminclude | sed -e 's/^[ \t]*//' | grep -n -e "\<perror\>" | sed -e 's/^\([1234567890][1234567890]\):/0\1:/' | sed -e 's/\([1234567890]\):/\1:  /'`
numperror=`echo "$perrors" | wc -l`

# print vars
function printvars {
    [ ! -z "$2" ] && export GREP_COLOR="$2"
    if [ ! -z "$1" ]; then
        IFS=$'\n'
        for line in $1; do
            IFS=' '
            echo "  $line" | grep -e "\<perror\>([^)]*)" $args --color=always
        done
    fi
}
echo
echo "lines with syscalls:"
out="$(printvars "$syscalls" '1;31')
     $(printvars "$perrors" '1;32')
    "
echo "$out" | sed -e 's/^ */  /' | sort

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
