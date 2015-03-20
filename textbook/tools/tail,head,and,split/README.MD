

Head, tail, and split are all part of the coreutils package that accompanies Linux. Their implementations on other unix based systems may vary, and they certainly differ on Mac OSX, where some flags may not be implemented. This guide pertains to the defined Linux implementation. 

Customizations available
`Head` by default prints out the first 10 lines from the file or file descriptor depicted by a list of file or file descriptor arguments folowing an arbitrary number of flags. By default this outputs the last 10 lines specified by its argument list. The actual number of lines can be customized or instead defined in terms of bytes. `Head` can accept either a file name or file descriptor. `Head` works by buffering up to 4096 bytes at a time from the start of the file and writing to `stdout` including newline characters. 

A call to print the last ten lines of 3 files would be

`head file1 file2 file3`

This would print

`==> file file1 <==` 
`first 10 lines of file1`
`==> file file2 <==` 
`first line of file2`

where the files may also be specified by absolute path or by file descriptor. If only one file is specified, no headers will be printed unless either `-v` or `--verbose` is specified before the first file name. Conversely file names can also be suppressed in longer lists using `-q`, `--quiet`, or `--silent`.

A different number of lines can be specified using the syntax
`head -n  file1` or `head --lines=number_greater_than_zero`
so to print the first million lines of text where lines are specifically delimited by a newline character, we would use something like
`head -n 1000000 warandpeace` or `head --lines=1000000 warandpeace`

This will print up to the specified number of lines. In case the file isn't formatted with newline characters, it's possible to specify a maximum number of bytes. To do this using the previous example, try
`head -c  1000000 warandpeace` or `head --bytes=1000000





