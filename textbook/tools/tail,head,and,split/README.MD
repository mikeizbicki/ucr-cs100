d

Tail




http://www.computerhope.com/unix/utail.htm

Tail prints the last lines of a file.

Head prints the first lines.

Tail and head have various flag options …

…

..

Some of these options may differ across unix versions. Many of them do not work correctly or require different syntax in OSX, so it’s best to use Linux. 

Customizations available
***********
number of bytes output

follow a specific file

--lines = k  

last k lines or  starting with + lines starting with kth

Tail will print the the last k lines from a list of specified files. The default is 10, but it can be specified by the flag --lines=k. If more than one file is specified in the list, it will print an appropriate header to indicate the origin of that set of lines.

If you’re working on something that appends to a file, tail can also echo this behavior at specified intervals. It does this by calling sleep 1 , then checking each file in its list for a change in file size. 

The default behavior for follow is to follow a file descriptor, but follow can follow a file by name if specified by .
http://linux.die.net/man/1/sleep
This accomplished by reading the file in reverse in chunks of BUFSIZ bytes, then computing an offset. The associated source code can be found and studied in tail.c, which is part of coreutils, starting at line 418.



***********
Linux has several commands that can break up a file or display it in different ways.


 

2.3 from manual 
Some GNU programs (at least df, du, and ls) display sizes in “blocks”. You can adjust the block size and method of display to make sizes easier to read. The block size used for display is independent of any file system block size. Fractional block counts are rounded up to the nearest integer.
The default block size is chosen by examining the following environment variables in turn; the first one that is set determines the block size.


However, some of the programs documented here do produce other exit status values and a few associate different meanings with the values ‘0’ and ‘1’. Here are some of the exceptions: chroot, env, expr, nice, nohup, numfmt, printenv, sort, stdbuf, test, timeout, tty. 

12 Special built-in utilities
Some programs like nice can invoke other programs; for example, the command ‘nice cat file’ invokes the program cat by executing the command ‘cat file’. However, special built-in utilities like exit cannot be invoked this way. For example, the command ‘nice exit’ does not have a well-defined behavior: it may generate an error message instead of exiting.
Here is a list of the special built-in utilities that are standardized by POSIX 1003.1-2004.
. : break continue eval exec exit export readonly return set shift times trap unset
For example, because ‘.’, ‘:’, and ‘exec’ are special, the commands ‘nice . foo.sh’, ‘nice :’, and ‘nice exec pwd’ do not work as you might expect.
Many shells extend this list. For example, Bash has several extra special built-in utilities like history, and suspend, and with Bash the command ‘nice suspend’ generates an error message instead of suspending.


2.6 chown, chgrp, chroot, id: Disambiguating user names and IDs
Since the user and group arguments to these commands may be specified as names or numeric IDs, there is an apparent ambiguity. What if a user or group name is a string of digits? 1 Should the command interpret it as a user name or as an ID? POSIX requires that these commands first attempt to resolve the specified string as a name, and only once that fails, then try to interpret it as an ID. This is troublesome when you want to specify a numeric ID, say 42, and it must work even in a pathological situation where ‘42’ is a user name that maps to some other user ID, say 1000. Simply invoking chown 42 F, will set Fs owner ID to 1000—not what you intended.
GNU chown, chgrp, chroot, and id provide a way to work around this, that at the same time may result in a significant performance improvement by eliminating a database look-up. Simply precede each numeric user ID and/or group ID with a ‘+’, in order to force its interpretation as an integer:
    chown +42 F
     chgrp +$numeric_group_id another-file
     chown +0:+0 /


The name look-up process is skipped for each ‘+’-prefixed string, because a string containing ‘+’ is never a valid user or group name. This syntax is accepted on most common Unix systems, but not on Solaris 10.
5.1 head: Output the first part of files


tail:

split: Split a file into pieces.

5.4 csplit:
how to track which parts were copied from the manual to ensure they’re all removed as this *
is fleshed out
using bullet points I guess

Formatting with core utils

head prints the first part 


head [option] .. [file] …

*******


