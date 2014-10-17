#!/bin/bash

#
# This script takes as a parameter an assignment folder.  
# Then it opens up a single editor window
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

tmpfile=$(mktemp)
cat "$assn/grade" > "$tmpfile"
echo "#######################" >> "$tmpfile"
echo "#" >> "$tmpfile"
echo "# grading everyone's assignment right now" >> "$tmpfile"
echo "#" >> "$tmpfile"
echo "# (all lines starting with # are comments and won't be saved)" >> "$tmpfile"
echo "#" >> "$tmpfile"
echo "#######################" >> "$tmpfile"

vim $tmpfile

# delete all the comments from the tmpfile
sed -i "/^\#/d" "$tmpfile"

downloadAllGrades

printf "copying grade file..."
for file in $studentinfo/*; do
    csaccount=$(basename $file)
    cp $tmpfile "$tmpdir/$classname-$csaccount/$assn/grade"
done
echo "done."

uploadAllGrades

