
# coreutils

As described by its [GNU page](https://www.gnu.org/software/coreutils/), coreutils is a set of utilities that provide file, shell, and text manipulation.
It is not part of Unix, but it ships with all Linux distributions.
This page provides some basic detail and potential use cases of a subset of the coreutils package, specifically the [`chroot`](http://linux.die.net/man/2/chroot), [`env`](http://linux.die.net/man/1/env), [`nice`](http://linux.die.net/man/1/nice), [`nohup`](http://linux.die.net/man/1/nohup), [`stdbuf`](http://linux.die.net/man/1/stdbuf), and [`timeout`](http://linux.die.net/man/1/timeout) commands.
These tools allow us to modify the environment of a command and apply certain restrictions.

## chroot 
[`chroot`](http://linux.die.net/man/1/chroot) allows a [privileged process](http://linux.die.net/man/7/capabilities) to execute a single command with restricted file access.
It will launch a new shell window if no command is specified. 
The command specified to [`chroot`](http://linux.die.net/man/1/chroot) can access files that are reachable from its path argument as well as open file descriptors.
If the calling process lacks the privilege [`CAP_SYS_CHROOT`](http://linux.die.net/man/7/capabilities), the call will fail due to insufficient privileges.

```
$ mkdir newroot
$ chroot newroot
chroot: cannot change root directory to newroot: Operation not permitted
```
If the command executable or one of its runtime dependencies is unreachable starting from the path specified to [`chroot`](http://linux.die.net/man/1/chroot), it will result in a runtime error.

```
$ sudo chroot newroot
chroot: failed to run command `/bin/bash': No such file or directory
```

The error here can be remedied by first determining bash's location and runtime dependencies, then copying them into the folder `newroot`.
The location of bash's executable file can be determined using `which`.
Its runtime dependencies can be listed by calling [`ldd`](linux.die.net/man/1/ldd) with the path returned by `which`.

```
$ which bash
/bin/bash
$ ldd /bin/bash
linux-vdso.so.1 =>  (0x00007fffd0dff000)
libtinfo.so.5 => /lib/x86_64-linux-gnu/libtinfo.so.5 (0x00007f7451e80000)
libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f7451c7c000)
libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f74518ef000)
/lib64/ld-linux-x86-64.so.2 (0x00007f74520bd000)
```

We can then copy the appropriate files using [`cp`](http://linux.die.net/man/1/cp).

```
$ cp /lib/x86_64-linux-gnu/libtinfo.so.5 newroot
$ cp /lib64/ld-linux-x86-64.so.2 newroot
$ cp /lib/x86_64-linux-gnu/libc.so.6 newroot
$ cp /lib/x86_64-linux-gnu/libdl.so.2 newroot
$ cp /bin/bash /newroot/bin/bash
$ cp /bin/bash /newroot/bin/bash
```

We may need to copy additional code to accomplish some tasks, but it's best to copy the minimum required amount for security and maintainability reasons.
This might be used to limit access of a [daemon](http://linux.die.net/man/3/daemon), which requires root privileges.
An example implementation for running Apache in Debian is described [here](https://www.debian.org/doc/manuals/securing-debian-howto/ap-chroot-apache-env.en.html).
Parentheses are used here to launch a subprocess, which executes the command, launching a new shell window with access restricted to the directory `newroot` and its subdirectories.

```
$ (sudo chroot newroot)
```

## env
[`env`](http://linux.die.net/man/1/env) allows us to run a command in a modified environment without affecting the original environment or the environments of other concurrent processes.
This is accomplished by modifying one or more of a set of environment variables, which control things such as the command prompt, the preferred text editor, the current working directory, and the paths that should be searched for executable files.
If no command is specified `env` prints out a full list of environment variables.
This is a quick way to see what variables have been set.

```
$ env
NNTPSERVER=news.cs.ucr.edu
HOSTNAME=hammer.cs.ucr.edu
TERM=xterm-color
SHELL=/bin/bash
HISTSIZE=100
...
```

Extending our previous example, we can now safely launch a subshell to run untested executables.

```
$ (env -i - PWD=newroot PS1="safeenvironment $" sudo chroot newroot)
```

The `-i` flag was specified to start the new shell with an empty environment.
We can also launch a new shell with a blue prompt that displays the current working directory.

```                                           
$ env PS1="\[\033[0;34m\]$PWD $:\[\033[0m\]" /bin/bash
```

We can also explicitly specify a directory to be searched for a given executable.
This could be used in cases where the executable is stored on a different drive, and it does not require a privileged process. 

```
$ env PATH="/bin" sh
```

## nice
[`nice`](http://linux.die.net/man/1/nice) allows a user to run a process with modified scheduling priority, typically referred to as niceness.
If several processes are running concurrently, those with with lower niceness will receive more CPU time to complete their tasks.
The default niceness is 0, minimum is -20, and maximum is 19. 
The argument passed to [`nice`](http://linux.die.net/man/1/nice) indicates the amount to adjust the current niceness for the specified command.
Any user may specify a positive niceness adjustment.
Processes with the privilege `CAP_SYS_NICE` may also specify a negative niceness adjustment.
No adjustment specified will result in an increase of 10.
For example [Folding@home](https://folding.stanford.edu/) is a distributed computing project aimed at understanding improper folding of proteins and its link to specific diseases.
We might want to contribute to this as long as it doesn't interrupt our normal tasks.
The following starts a command line tool to devote spare cpu cycles to the project. 
A positive niceness adjustment is used to ensure that it does not interrupt other tasks.
The following will download and run the OSX client from the command line.
If `wget` is unavailable, the client can be downloaded via a web browser.

```
$ wget "https://fah-web.stanford.edu/file-releases/public/release/fahclient/osx-10.6.4-64bit/v7.4/fahclient_7.4.4-64bit-release.tar.bz2"
$ tar -xjvf fahclient_7.4.4-64bit-release.tar.bz2
$ nice -n -19 ./fahclient_7.4.4-64bit-release/FAHClient
```

To modify the niceness of a process that is already running, we use [`renice`](http://linux.die.net/man/8/renice) instead.
[`renice`](http://linux.die.net/man/8/renice) may set niceness by pid, user, or process group.
Assuming a background script owned by `root` is causing some user process to be less responsive, we can use [`renice`](http://linux.die.net/man/8/renice) to lower the priority of their current processes.

```
$ sudo renice -n -20 -u root
0: old priority 0, new priority -20
```

This assigns all root processes the highest possible scheduling priority.

## nohup
[`nohup`](http://linux.die.net/man/1/nohup) prevents a job from terminating when the parent process ends by catching the `SIGHUP` signal.
Output is sent to the file `nohup.out` in the current working directory by default.
That way command output will not halt if the terminal window is closed.
Errors remain directed to `stdout` unless they are explicitly redirected.
This is especially useful when dealing with [daemon](http://linux.die.net/man/3/daemon) processes, where the process must not be interrupted by termination of the calling process.
For example let's say you need to manually start [`crond`](http://linux.die.net/man/8/crond), which is responsible for running scheduled tasks described by a set of [`crontab`](http://linux.die.net/man/5/crontab) files.
It should continue running even if the calling process terminates, but it should not steal cycles from other user processes.
In the example below, if an empty string is returned, it means [`crond`](http://linux.die.net/man/8/crond) is not running.
We would then launch [`crond`](http://linux.die.net/man/8/crond) with the lowest scheduling priority.
[`nohup`](http://linux.die.net/man/1/nohup) is used there to provide immunity to hangups.
The following example could also be applied to any other [daemon](http://linux.die.net/man/3/daemon) process.

```
$ crondpid="$(pidof crond)"
$ if ! [ -n "$crondpid" ] 
$     then sudo nohup nice -n 19 crond $PATH
$ fi
```

## stdbuf
Buffering allows for temporary storage of data that is to be written to another location or accessed by a function.
This helps to mitigate the number of system calls, but it can cause other problems.
[`stbuf`] allows the user to use modified input or output buffering for a given command.

Data is generally kept in temporary storage until certain conditions are met.
This is called buffering.
In a terminal setting the most common type is line buffering, where action is taken on the data upon encountering a newline character.
In the following example, the initial data from a routine maintenance script is filtered to grab the last 10 lines and print out any that contain `/dev/disk`.
New lines will also be filtered as the file is updated due to the `-f` flag.
This example was done to keep a record of disk space after the removal of temporary files.
It can also be used in a similar manner to display errors in other log files.

```
$ tail -f log.out | grep "/dev/disk"
```

If we want this process to continue for hours, days, or months, it would be better to ensure the process remains uninterrupted using `nohup`.

```
$ nohup tail -f log.out | nohup grep "/dev/disk" >> nohup.out
```

Unfortunately `grep` does not always append to `nohup.out` when `log.out` is updated, because output here is not line buffered.
Instead data is read until the buffer is full, which may be problematic if the buffer is large and updates are infrequent.
We can restore its previous behavior using `stdbuf` with its output line buffering option.

```
$ nohup stdbuf -o L tail -f log.out | nohup stdbuf -o L grep "/dev/disk" >> nohup.out
```

## timeout
[`timeout`](http://linux.die.net/man/1/timeout) places a limit on the maximum amount of time a command may run prior to exiting.
This is specified as a floating point value indicating the maximum duration.
It may be specified with an optional suffix to indicate unit.
Suffixes are seconds (s), minutes (m), hours (h), or days (d).
If no suffix is specified, the value is interpreted in seconds.
The default signal sent upon reaching the specified duration is `SIGTERM`.
This may be actively caught or ignored by the process.
To ensure the process ends we can use `--kill`, which sends `SIGKILL` in addition to the default signal.
The signal can be modified to any available signal.
To run [`ping`](http://linux.die.net/man/8/ping) on site goggle.com with low priority and `SIGTERM` sent at the 30 second mark, the command would be the following.

```
$ timeout --signal=SIGTERM 30 ping goggle.com
```

This will ping a connection. If more than 30 seconds elapse without a response, `SIGTERM` will be sent to the process.
This could be used to test either a remote server or an NIC.
