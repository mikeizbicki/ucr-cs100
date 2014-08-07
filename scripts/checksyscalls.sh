#!/bin/bash

# 
# This script takes any number of CPP files as parameters.  For each file, it
# checks to see if there is a matching call to perror for every syscall.  If
# there is not, we assume that proper error checking is not happening.  Then
# we output a grade modifier that deducts 5 points for every extra syscall.
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

# we'll pipe files through these commands to remove spurious counts
rmcomments="$scriptdir/rmcomments.sh"
rmstr="sed s/\"[^\"]*\"//g"

# define all the regexes for syscalls likely to be used by students
syscalls="
    \<getlogin\>
    \<getlogin_r\>
    \<gethostname\> 
    \<execl 
    \<execv 
    \<fork\> 
    \<wait\> 
    \<waitpid\> 
    \<open\> 
    \<read\> 
    \<write\>
    \<readdir\>
    \<readdir_r\>
    \<stat\>
    \<pipe\>
    \<dup2\>
    \<dup\>
    \<chdir\>
    \<getcwd\>
    \<getwd\>
    \<get_current_directory_name\>
    "

# calculate number of syscalls
numsyscalls="0"
for syscall in $syscalls; do
    count=`cat $@ | "$rmcomments" | $rmstr | grep -e "$syscall" | wc -l`
    numsyscalls=$[$numsyscalls + $count]
done

# calculate number of perror
numperror=`cat $@ | "$rmcomments" | $rmstr | grep -e "\<perror\>" | wc -l`

# calculate the grade modifier
grademod="0"
if [ "$numperror" -lt "$numsyscalls" ]; then
    grademod=$[ 5 * ($numsyscalls - $numperror) ]
fi

# output results
echo "number of syscalls... $numsyscalls"
echo "number of perror..... $numperror"
echo "grade modifier....... -$grademod"

exit $grademod
