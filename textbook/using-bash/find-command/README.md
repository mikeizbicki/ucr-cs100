#Mastering find command

The Linux find command is useful to search for files from the commands line. The find command is available on most liinux distros by default so you do not have to install any package. Find has the ability to locate any files even files that you forgot where they are. You can locate files based on various search criterias like permissions, user ownership, size ect. You can also use find to travel down subdirectories in case you wanted a reursive directory list.
The basic syntax is:
`$ find <location> <comparison-criteria> <search-term>`


##Simple examples:

The simplest ecxample is to use find to print the names of all the files in the directory and all subdirectories. You can do this by simply writing:
`$ find`
`$ find .`
`$ find . -print`
All three commands above are the same and will give you the same output begin with a `.` such as:
`.`
`./file.txt`
`./file.cpp`
`./subdirectory`

You can also choose to search for a specific directory or path. When appending the `./directory-path` after find, you will get a list of all the files in the `./directory-path` if `./directory-path` is in the current directory. Example:
`$ find ./directory-path`
`./directory-path/file.txt`
`./directory-path/main.cpp`
`./directory-path/subdirectory`

If you know the file name you can search for files by their names using the following:
`$ find ./directory-path -name "filename.txt"`
and you will get:
`./directory-path/filename.txt`

NOTE: If you do not specify a directory or path then the command `$ find -name "filename.txt"` will print all the files with the specified name that are in your current directory and its subdirectories.

If you know the type of file, but don't remember the name you can use:
`$ find ./directory-path -name "*.txt"`
and you will get all txt files in the file directory you search, for the above you would get:
`./directory-path/file1.txt`
`./directory-path/file2.txt`
`./directory-path/file3.txt`

NOTE: Just as in the previous example if you do not specify a directory or path then the command `find -name "*.txt"` will print all files of the specfied type that are in your current direcdory and its subdirectories.

NOTE: Having * in front of .txt means that there can be more words before .txt when searching. If you do not have * then only files matching ".txt" exactly will be printed such as when we searched for "filename.txt".

##Directory Traversal

When using find it is important to remember that all subdirectories are searched recursively, which is how all files of a given extension are found. If you do not want to travel through the entire recursive path then you can specify the depth of directory traversal. You can specify the depth of your traversal by using `maxdepth <number-levels>`

Let's say you want to only search in your current directory then use:
`$ find ./directory-path -maxdepth 1 -name "*.cpp"` and get:
`./directory-path/example.cpp`

If instead you wanted to search up to one subdirectory then you simple replace `-maxdepth 1` by `-maxdepth 2` and get:
`$ find ./directory-path -maxdepth 2 -name "*.cpp"` and get:
`./directory-path/example.cpp`
`./directory-path/subdirectory/main.cpp`
`./directory-path/subdirectory2/file.cpp`

NOTE: You can also use `-mindepth <number-levels>` to go to least the number of levels specifiedbefore searching for the files.

##Search by Type

When using find you can choose to search for specific types of files. You may want to only find refular files or only directories.
To only find files we append `-type f` after  `./directory-path`
To only find directories we append `-type d` after `./directory-path`
Just as before we may choose to add a directory or path and if we don't then all files and subdirectories in the current directory will be recursively searched. We also have the option to add `-name "filename"` after `-type f/d`. If we do not specify a name all files or directories (depending which you specified) in the specified directory-path will be recursively printed. 

example for only files:
`$ find ./directory-path -type f -name "filename*"`
`./directory-path/filename.txt`
`./directory-path/subdirectory/filename2.txt`

example for only directories:
`$ find ./directory-path -type d -name "filename*"`
`./directory-path/filename`
`./directory-path/subdirectory/filename2`

NOTE: Appending * to the filename means that there can be more words after filename when searching. If you do not append * then only files or directories with the exact "filename" will be printed. In the above examples if we did not have * appended to filename then we would not have anything printed for only files since filename.txt is not exact match to filename. For only directories if we did not append * to filename we would only get ./directory-path/filename .


##Search by Permission

You can use find to search for files based on their specific permissions. 




##Miscellaneous

###Search multiple directories 
Let's say you want to search  for a filename and know that is either in directory1 or directory2. Using find allows you to search inside two separate directories by simply appending the second directory after the first when using the find command. we can use:
`find ./directory1-path ./directory2-path -type f -name "filename*"`
`./directory1-path/filename.txt`
`./directory2-path/filename.txt`

###Find hidden files
Since we know that hidden files on linux begin wth a period, we can use `-name ".*"` in find to search for hidden files. example:
`$ find ~ -type f -name ".*"`

###Find files for user
Using the find command can help us find files belonging to a particular user. We just need to search in the /root directory such as:
`$ find . -user username`
`.`
`./file.txt`
`./directory/file2.txt` 
`./directory/subdirectory/file3/txt`

We can use any combination of all the search options and narrow down the search such as:
`$ find . -user username -name '*.txt'`

###Deleting files/directories
You can also use find command to remove all specied types of files in a sepcified directory or path. You can do this by appending `exec rm -f {} \;` after identifying the filename/filetype such as:
`$ find /directory-path -type f -name "*txt" -exec rm -f {} \;`
The above command deletes all text files int the directory-path directory. You can switch f for d to remove directories instead and change "*txt" to "directoryname*"

