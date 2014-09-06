#!/bin/bash

#
# this script downloads everyone's projects and runs them through the
# plagarism detection software moss
#

scriptdir=`dirname "$0"`
source "$scriptdir/config.sh"

#######################################
# download projects

for file in studentinfo/*; do
    csaccount=`basename $file`
    name=`head -n 1 $file`
    githubaccount=`tail -n 1 $file`

    downloadproject "$githubaccount" "rshell"
done
