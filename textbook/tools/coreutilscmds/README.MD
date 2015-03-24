`chroot` requires a privileged process to run. It is not reversible by a given process, yet that process still needs access to any executables that will run on that process. This is indicated by `CAP_SYS_CHROOT`. 

chroot [-u    user] [-g group] [-G group,group,...] newroot [command]

Following this basic syntax is likely to end with an error like 
`root@debian:/blah# chroot ./lib/`
`chroot: failed to run command `/bin/bash': No such file or directory`.

To run `chroot` from `bash`, you must first copy the folder containing the `bash` executable and those containing its dependencies to the new root path. This can be accomplished by first finding all executable paths using `$PATH`, then using `cp -r  newRootFolder`  for each colon delimited path in the environment variable `$PATH`. If you aren’t sure of the location of a specific executable, it can be found with `which [command]` where `[command]` can simply be replaced with the command name. A chrooted process can still access file descriptors that fall outside of the new root tree.

`env` run on its own in a shell will print out a list of environment variables associated with the current user. Simply typing `env` is equivalent to `printenv`, which brings up a complete list of environment variables. 

`SSH_AUTH_SOCK=/home/kav/.cache/keyring-Ql1NO5/ssh
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
_=/usr/bin/env`
These can each be set or unset using their respective names. If the variable is already defined, the `$` should be left off. There should be no spaces between the variable name, `=`, and new value. For example starting from the same terminal.
LOGNAME=Batman
`env` now returns the name Batman in the list. I always figured he was a Linux user.
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
LOGNAME=Batman
XDG_DATA_DIRS=/usr/share/gnome:/usr/local/share/:/usr/share/

An important example would be path. This gives a complete list of directories that should be searched whenever a command is to be executed in the current environment. To set variables which contain a set of keys, each key should be separated from the last by a `:`. For example `PATH` could be interpreted as `PATH=path1:path2:path3…..:pathn`

A new environment can be created by the command `env -i`. The shell program in use can also be set at this time. 

`$ env -i /bin/sh`
`$ env`
`PWD=/home/kav`
$`

If a path is not explicitly specified, the environment will just inherit the previous path from whatever called `env -i`.

Every process has some level of niceness, giving some indication of its priority where a value greater than 0 indicates a lower priority. Any process can assign a niceness greater than 0 to a given task. It’s also possible to run a task with reduced niceness, but that requires a privileged process. If for example you wanted to print out any appended contents from file foo.log, this could be accomplished by 
`nice -19 tail -F ` where 19 represents the lowest possible scheduling priority. Seeing as tail will output up to 10 lines by default, it won’t miss any this way from a slowly growing log file. 
`nice -n 19 tail -F ` and
`nice --adjustment=19 tail -F ` 
will produce the same result. The general syntax is
`nice [OPTION] [COMMAND] [ARG LIST]`
If no command is specified, default Linux behavior is to print the current niceness of that process at that time. No option specified increases niceness by 10. This means that if you run a chain of processes with a `nice` `no arg` somewhere in the middle, it will print the niceness at that exact time. This typically resets after the command is finished due to termination of the associated child process.

`root@debian:/blah# nice`
`0`
`root@debian:/blah# nice nice`
`10`
`root@debian:/blah#`
`root@debian:/blah# nice`
`0`

If you try to make something really nice, it will go to the highest possible value of 19.
`nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice nice`
`19`

In the other direction, the minimum niceness is -20.
`root@debian:/usr# nice --10 nice`
`-10`
`root@debian:/usr# nice --20 nice`
`-20`
`root@debian:/usr# nice --40 nice`
`-20`

Behavior of `nice` is undefined if called with a built in utility. Typically the command just fails, but defined behavior isn’t guaranteed. 
`root@debian:/# nice -10 exit`
`nice: exit: No such file or directory`

`nohup` prevents a job from terminating when the parent process ends by redirecting output and ignoring `stdin`. Output is sent to the file `nohup.out` in the current working directory by default. Any errors remain directed to `stdout`. Both `stdout` and `stderr` are redirected in the following example.

`nohup ls -l -R  1>output_file  2>error_file`

would print the results of `ls` to output_file and any errors to error_file regardless of whether the shell remains open. 

Data is buffered on input or output. This can cause problems with things that must be updated at intervals or filtered in some way. This only affects functions that work via streams, yet buffer changes invoked by a command will override changes to buffers. This can be used to correct issues where nothing is printed or different streams to the same output are unreasonably far apart. 



`timeout` places a limit on the maximum amount of time a command may run prior to exiting. This defaults to seconds, but can be specified by appending a one letter suffix to the duration.

‘s’   for seconds (same as default)
‘m’ for minutes
‘h’  for hours
‘d’  for days


The default signal upon reaching duration is `SIGTERM`. This may be actively caught or ignored by the process. This can be remedied by `--kill`, which sends a kill signal in addition to the default signal. The signal can be modified to any available signal.
The general syntax for this is 
`timeout [option] duration[suffix] command [arg]...`
`timeout [option]
where command cannot be a special built-in utility.
For example to kill a recursive long format call to `ls` after it runs for one second, the syntax would be 
`timeout  --signal=SIGKILL 1 ls -l -R`
It could also be run just until it receives a specific signal. For example
`timeout --signal=SIGTSTP`


