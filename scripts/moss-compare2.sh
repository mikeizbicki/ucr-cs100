#!/bin/bash

#
# This script runs a detailed moss cheating evaluation on two students.
# It runs moss on all the commits of each student.
#

scriptdir=$(cd $(dirname "$0"); pwd)
source "$scriptdir/config.sh"

mossdir="$scriptdir/../$tmpdir/mossrun"
if [ -d $mossdir ]; then
    rm $mossdir/*.cpp
    rmdir $mossdir
fi
mkdir $mossdir

# copies all commits from "rshell/$1" to $mossdir
# FIXME: this could use a lot of generalization
function copyAllCommits() {
    cd "$tmpdir/rshell-$1"

    # save our current branch so we can restore to this location later
    curbranch=$( git branch | grep -e '\*' | cut -d' ' -f2 )
    for commit in $(git rev-list master); do
        committime=$(git show -s --format=%ci $commit | tr ':' '-' | cut -d' ' -f1,2 | tr ' ' '_')
        echo "$commit @ $committime"

        # copy all source files in commit to $mossdir
        # FIXME: the grep statement doesn't include all the filetypes
        git checkout $commit --quiet
        for file in $(find . | grep "\.cpp$"); do
            echo "  $file"

            cp "$file" "$mossdir/$1-$committime-$(basename $file)"

            # FIXME: exclude files that are allowed to be similar
        done
    done

    # reset git repo
    git checkout $curbranch --quiet
    cd "$scriptdir/.."
}

# run moss on the results
echo "--------------------------------------------------------------------------------"
copyAllCommits $1
copyAllCommits $2
$scriptdir/moss/moss $mossdir/*
