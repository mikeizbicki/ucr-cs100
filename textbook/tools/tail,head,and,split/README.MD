

Head, tail, and split are all part of the coreutils package that accompanies Linux. Their implementations on other unix based systems may vary, and they certainly differ on Mac OSX, where some flags may not be implemented. This guide pertains to the defined Linux implementation. 

Customizations available
***********
`Head` by default prints out the first 10 lines from the file or file descriptor depicted by a list of file or file descriptor arguments folowing an arbitrary number of flags. By default this outputs the last 10 lines specified by its argument list. The actual number of lines can be customized or instead defined in terms of bytes. `Head` can accept either a file name or file descriptor. `Head` works by buffering up to 4096 bytes at a time from the start of the file and writing to `stdout` including newline characters. 

A call to print the last ten lines of 3 files would be

`head file1 file2 file3`

This would print

`==> file file1 <==` 
`first 10 lines of file1`
`==> file file2 <==` 
`first line of file2`

where the files may also be specified by absolute path or by file descriptor. If only one file is specified, no headers will be printed unless either `-v` or `--verbose` is specified before the first file name.

A different number of lines can be specified using the syntax
`head --lines=K file1` 
so to print the first million lines of text, we would use something like
`head --lines=1000000 warandpeace`

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


