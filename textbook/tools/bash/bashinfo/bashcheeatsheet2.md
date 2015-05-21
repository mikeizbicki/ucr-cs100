#Bash Shell Cheatsheet 2
###cp 
Copies files and directories.
```
cp [flags] FileToCopy DestinationPath
```
You can copy many files at a time into a directory, or just copy one file.
```
cp [flags] FileToCopy1 FileToCopy2 FileToCopy3 DestinationPath
```
To copy a directory, you need to use the `-r` or `-R` flags to recursively copy eveything in.
Files will keep their name unless you don’t enter a path or directory that is the current directory, and instead enter a new name for the copy file.
```
cp [flags] file1 file1WithNewName
cp -r testfile1 newfile
```
Another flag is the `-v` flag which outputs the files as they are copied, which is useful for recursive copies.
```
$cp -r -v test1 test2
test1 -> test2
test1/b -> test2/b
test1/c -> test2/c
```
###sort
Outputs given input in sorted order.
Takes in a file, reads it, and outputs each line.
If no files are specified, it takes in stdin.
```
sort [flags] file1 file2 file2...
```
`-n` sorts numerically, `-r` is for reverse order
###mv
###rm
###wc
###rmdir
###chown
###chgrp
###touch
###tee
###printenv
###id
###logname
###whoami
###groups
###users
###chown
###chgrp
###date
###nproc
###uname
###hostname
###hostid
###kill
###fg
###bg
###sleep
