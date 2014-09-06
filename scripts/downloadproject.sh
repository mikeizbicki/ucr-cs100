#!/bin/bash

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

# perform download

user="$2"
proj="$1"
clonedir="$tmpdir/$proj-$user"
if [ ! -d "$clonedir" ]; then
    giturl="https://github.com/$user/$proj.git"
    echo "  running git clone on [$giturl]"
    git clone --quiet "$giturl" "$clonedir" 
else
    echo "  running git pull on [$clonedir]"
    cd "$clonedir"
    git pull origin --quiet > /dev/null
    cd ../..
fi
