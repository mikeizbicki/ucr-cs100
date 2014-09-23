#!/bin/bash

#
# This script takes all the instructor pgp keys and installs them locally.
# No one except the person finally responsible for grades needs to run it.
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

for file in "$instructorinfo/*"; do
    echo importing $file
    gpg --import $file
done
