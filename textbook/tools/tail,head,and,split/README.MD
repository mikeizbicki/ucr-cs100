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

If you’re working on something that appends to a file, tail can also echo this behavior at specified intervals. It does this by calling [`sleep 1`] http://linux.die.net/man/1/sleep , then checking each file in its list for a change in file size. 

You might want to change this if you're actively following the file. For example if the file is open in a text editor and rewritten each time it is saved, rather than getting just the last line on update, you may obtain many lines as its appended rather than just the last k lines.

The default behavior for follow is to follow a file descriptor, but follow can follow a file by name if specified by .

This accomplished by reading the file in reverse in chunks of BUFSIZ bytes, then computing an offset. The associated source code can be found and studied in tail.c, which is part of coreutils, starting at line 418.



***********
Head on the other hand prints the first part. Just like with tail, if more than one line is specified, a header is printed for each line. 

`==> file file1 <==` 
first line of file 1
`==> file file2 <==` 
first line of file 2




split: Split a file into pieces.




head [option] .. [file] …

*******


