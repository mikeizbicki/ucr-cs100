#chroot

Syntax
`chroot [-u    user] [-g group] [-G group,group,...] newroot [command]`
[chroot man page] (http://linux.die.net/man/2/chroot)

`chroot` is a command used to run other commands in a limited environment by assigning a new root to the calling process with the syntax
`chroot [-u    user] [-g group] [-G group,group,...] newroot [command]`
If an argument is supplied for command, `chroot` may also execute a single command in a limited environment. Upon success `/` points to the path supplied as an argument. This requires a privileged process, as indicated by `CAP_SYS_CHROOT`, which is further described in the [capabilities man page](http://linux.die.net/man/7/capabilities). Lacking the appropriate permission to call `chroot` or search permission on a component of the path prefix of newroot will result in a runtime error.

```kav@debian:/home/kav$ ls       
Desktop    Downloads  Pictures  Templates  foo
Documents  Music      Public    Videos
kav@debian:/home/kav$ chroot ./foo
chroot: cannot change root directory to ./foo: Operation not permitted
kav@debian:/home/kav$```

In a shell environment such as bash, this will typically run on a forked process initialized by the shell, but the new root path must have a copy of all paths required by that shell. Otherwise this will result in a runtime error.

```root@debian:/home/kav# chroot ./foo
chroot: failed to run command `/bin/bash': No such file or directory
root@debian:/home/kav#```

To set this up in bash, you can locate the path to bash using
`which bash`. Bash has its own dependencies, which are located in the `:` delimited folders and their respective subfolders specified within the `PATH` environment variable. To run this from within bash, `cp -r [old path] newRootFolder` would copy in all necessary folders if applied to each path in `PATH`.

#env invocation

`env` refers to a set of variables that specify information about the setting of a set of processes, such as the working directory, a set of paths indicating the location of specific libraries, and the current user. 

The general syntax is env `[OPTION] [-][NAME=VALUE] [COMMAND[ARGUMENTS]]`. If a blank value is specified, the variable is set to `NULL`. This is different from the `-u` option, which removes the variable from the current environment. The `-i` flag ignores the current environment. It can be used to set up a new one as follows, where sh indicates the shell program to be used in the new environment. 

```root@debian:/home/kav# env -i sh
# env
PWD=/home/kav```

Adding the variable name to this example

```PWD=/home/kav
# env name=Batman```

If a value is not specified for an environment variable, it takes on a `null` value and remains in the list. 
```
# env name=
PWD=/home/kav
name=
```

The `-u` flag can be invoked to remove it. Some variables will be recreated without user input due to dependencies.


If `env` is run in a shell setting without additional arguments, it will print out a list of environment variables associated with the current user. This is equivalent to [`printenv`](http://linux.die.net/man/1/printenv), which brings up a complete list of environment variables. 

````SSH_AUTH_SOCK=/home/kav/.cache/keyring-Ql1NO5/ssh
USERNAME=kav
SESSION_MANAGER=local/debian:@/tmp/.ICE-unix/3126,unix/debian:/tmp/.ICE-unix/3126
PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games
DESKTOP_SESSION=gnome
PWD=/home/kav
GNOME_KEYRING_PID=3108
LANG=en_US.utf8
GDM_LANG=en_US.utf8
GDMSESSION=gnome
SHLVL=1
HOME=/home/kav
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
LOGNAME=kav
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share/:/usr/share/
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-cv5ACjXLpb,guid=b957a96ef583c9f617a322e3550f2df3
WINDOWPATH=7
DISPLAY=:0.0
XAUTHORITY=/var/run/gdm3/auth-for-kav-Dg0L9n/database
COLORTERM=gnome-terminal
_=/usr/bin/env````

These can each be set or unset using their respective names. If the variable is already defined, the `$` should be left off. There should be no spaces between the variable name, `=`, and new value. For example starting from the same terminal.
`LOGNAME=Batman`
`env` now returns the name Batman in the list. I always figured he was a Linux user.
````GNOME_DESKTOP_SESSION_ID=this-is-deprecated
LOGNAME=Batman
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share/:/usr/share/````


An important example would be `PATH`. This gives a complete list of directories that should be searched whenever a command is to be executed in the current environment. To set variables which contain a set of keys, each key should be separated from the last by a `:`. For example `PATH` could be interpreted as `PATH=path_1:path_2:path_3…..:path_k`

A new environment can be created by the command `env -i`. The shell program in use can also be set at this time. 
```
$ env -i /bin/sh
$ env
PWD=/home/kav
$``

If a path is not explicitly specified, the environment will just inherit the previous path from whatever called `env -i`.

#nice
Every process has some level of niceness, giving some indication of its priority where a value greater than 0 indicates a lower priority. Any process can assign a niceness greater than 0 to a given command. It’s also possible to run a task with reduced niceness if the calling process has the privilege `CAP_SYS_NICE`. If for example you wanted to print out any appended contents from file foo.log, this could be accomplished by 
`nice -19 tail -F ` where 19 represents the lowest possible scheduling priority. Seeing as tail will output up to 10 lines by default, it won’t miss any this way from a slowly growing log file. 
`nice -n 19 tail -F ` and
`nice --adjustment=19 tail -F ` 
will produce the same result. The general syntax is
`nice [OPTION] [COMMAND] [ARG LIST]`
If no command is specified, default Linux behavior is to print the current niceness of that process at that time. No option specified increases niceness by 10. This means that if you run a chain of processes with a `nice` `no arg` somewhere in the middle, it will print the niceness at that exact time. This typically resets after the command is finished due to termination of the associated child process.
```
root@debian:/blah# nice
0
root@debian:/blah# nice nice
10
root@debian:/blah#
root@debian:/blah# nice
0
```
If you try to make something really nice, it will go to the highest possible value of 19.

`nice nice nice nice nice nice nice nice`
`19`


In this case the shell calls `nice`. The only argument is `nice`, and no option is specified. The next thing encountered is a command, which is again 'nice`. This results in the default option of +10 niceness followed by a second call to `nice`. Default niceness is 0. Maximum is 19 and minimum is -20. A call to `nice nice nice` calls `nice` with a value of 0 and default options, resulting in a second call to `nice` with niceness 10, and a third call to `nice` with niceness 19. This then prints `19` as no command is specified on the last call. The job then terminates, so a process run after this would again be executed with niceness 0.
```root@debian:/home/kav# nice nice && nice
10
0
root@debian:/home/kav#``` 


/*This is the lowest possible priority you can assign to a given command, but since it's just a string of calls to `nice`, it calls `nice` with decreasing priority. It's important to recognize that the shell itself doesn't change in niceness. This altered priority is limited to the child process spawned by the shell, which in this case was just a recursive chain of calls to `nice`. */


If an option is specified, it acts as an adjustment to the base value rather than a replacement. 

```root@debian:/home/kav# nice -5 nice
5
root@debian:/home/kav# nice -5 nice --5 nice
0```

In this case a command must be specified. Otherwise it will result in a runtime error.
```root@debian:/home/kav# nice -5 nice -5
nice: a command must be given with an adjustment
Try `nice --help' for more information.```

Behavior of `nice` is undefined if called with a built in utility. Typically the command just fails, but defined behavior isn’t guaranteed. 
```root@debian:/# nice -10 exit`
nice: exit: No such file or directory```

To adjust the niceness of a process rather than a single command, [`renice`](http://linux.die.net/man/8/renice).

#nohup
`nohup` prevents a job from terminating when the parent process ends by redirecting output and ignoring `stdin`. Output is sent to the file `nohup.out` in the current working directory by default. Any errors remain directed to `stdout`. Both `stdout` and `stderr` are redirected in the following example.

`nohup ls -l -R  1>output_file  2>error_file`

would print the results of `ls` to output_file and any errors to error_file regardless of whether the shell remains open. 

Data is buffered on input or output. This can cause problems with things that must be updated at intervals or filtered in some way. This only affects functions that work via streams, yet buffer changes invoked by a command will override changes to buffers. This can be used to correct issues where nothing is printed or different streams to the same output are unreasonably far apart. 


#timeout
`timeout` places a limit on the maximum amount of time a command may run prior to exiting. This defaults to seconds, but can be specified by appending a one letter suffix to the duration.

‘s’  for seconds (same as default)
‘m’  for minutes
‘h’  for hours
‘d’  for days


The default signal upon reaching duration is `SIGTERM`. This may be actively caught or ignored by the process. This can be remedied by `--kill`, which sends a kill signal in addition to the default signal. The signal can be modified to any available signal, and duration represents a floating point value.
The general syntax for this is 
```timeout [option] duration[suffix] command [arg]...
timeout [option]```
where command cannot be a special built-in utility.
The following example displays a long format call to `ls` that runs for .003 seconds before receiving a `SIGKILL` signal.
```root@debian:/# timeout --signal=SIGKILL .003 ls -l -R
.:
total 92
drwxr-xr-x   2 root root  4096 Nov  4 20:07 bin
drwxr-xr-x   4 root root  4096 Mar 24 03:25 blah
drwxr-xr-x   3 root root  4096 Nov  4 20:09 boot
drwxr-xr-x  14 root root  3160 Mar 22 14:01 dev
drwxr-xr-x 133 root root 12288 Mar 24 21:03 etc
drwxr-xr-x   4 root root  4096 Mar 19 09:08 home
lrwxrwxrwx   1 root root    30 Nov  4 18:51 initrd.img -> /boot/initrd.img-3.2.0-4-amd64
drwxr-xr-x  16 root root  4096 Nov  4 20:06 lib
drwxr-xr-x   2 root root  4096 Nov  4 18:51 lib64
drwx------   2 root root 16384 Nov  4 18:51 lost+found
drwxr-xr-x   3 root root  4096 Nov  4 18:51 media
Killed```

If the duration is changed to .001 seconds with the same call
```
root@debian:/# timeout --signal=SIGKILL .001 ls -l -R
.:
total 92
Killed
root@debian:/#```

need to reinvestigate that one, it also doesn't take a command but that syntax should be represented
/*It's also possible to call timeout without specifying a duration. A process that receives `SIGTSTP` can be resumed in bash.  To run the same command until ls terminates by calling `exit` or `SIGTSTP` is received , the command would be
`timeout --signal=SIGTSTP ls -l -R`*/

