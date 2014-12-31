#!/bin/bash

# FIXME: what if the file named "pipe" already exists and is being used by something else?
mkfifo pipe

while true; do
    nc -lp 8081 < pipe | ./http-stdin.sh > pipe
done

# FIXME: every other web request has a broken connection;
# to get the points, you'll have to make every web request succeed

# FIXME: when our webserver is running and I press ^C,
# the current nc process is stopped but the while loop does not break,
# so another nc process immediately starts.
# To exit the program, we have to press ^Z, and run `killall http.sh; fg`


