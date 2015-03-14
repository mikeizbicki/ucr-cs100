#Mastering the find command

The Linux find command is a useful tool to search for files from the command line. The find command is available on most linux distros by default so you do not have to install any package. Find has the ability to locate any files even files that you forgot where they are. You can locate files based on various search criterias like file type, name, permissions, user ownership, size ect. You can also use find to travel down subdirectories in case you wanted a recursive directory list.

The basic syntax is:
```
$ find [location] [comparison-criteria] [search-term]
```

Note: For the following examples we will be in the root directory so you can try these examples on your own. I am running these examples on Ubuntu so some file names might be different but the directories in the examples should be present in all root directories. 

##Simple examples:

The simplest example is to use find to print the names of all the files (including dot files) in the current directory and all of its subdirectories as well. You can do this by simply writing:
```
$ find
```

If you are on the root directory you will get a list of paths of all the files on your computer and be warned this will be a very long list!!!

The command above is the same as the following two commands:
```
$ find .         
$ find . -print  
```
Don't believe me? Go on and try them!

###Search a specific directory or path

You can also choose to search for a specific directory or path. Do this by appending the directory name/path after find such as:
```
$ find ./directory-path 
```
and get:
```
./directory-path/files               
./directory-path/subdirectories/files
```
Note that you should get all files in that directory-path as long as the directory-path exists within the current directory.
 
Example: Let's say you really wanted to see all the files in your usr/bin directory because you are curious as to how it is different from your root bin. Then type:
```
$ find ./usr/bin 
``` 
One again you would get a long list of the paths to all your `./usr/bin` files. You should have no trouble seeing all the paths since ./usr is in you root directory and /bin is in your usr directory. But let's say you are very lazy and you don't want to scroll all the way back up to see the files that start with a. What can you possibly do? Well, if you simply append `/a*` bash will carry out filename expansion (a process know as globbing) to recognize and expand wild cards. Globbing will interpret the standard wild character `*`, which can represent any number of characters (including zero). So if you type:
```
$ find ./usr/bin/a* 
```

you will get the paths to all file in your usr/bin directory that start with a. This is because a will be read in and * will represent any number of characters. And if you do:
```
$ find ./usr/bin/*a 
```

then you will get all paths to files ending in a in your usr/bin directory, which would be:
```
./usr/bin/bmtoa          
./usr/bin/calibrate_ppa 
./usr/bin/config_data    
./usr/bin/foo2lava       
./usr/bin/java           
./usr/bin/lzma           
./usr/bin/orca           
./usr/bin/pfbtopfa    
./usr/bin/pnm2ppa      
./usr/bin/remmina       
./usr/bin/unlzma         
./usr/bin/wftopfa        
./usr/bin/xgamma         
```

###Search by file name or file type

Looking through so many file paths can be exhausting so if you know the file name you can search for files by their names using the following:
```
$ find ./directory-path -name "filename.txt"
```
and get:
```
./directory-path/filename.txt               
./directory-path/subdirectories/filename.txt
```

NOTE: If you do not specify a directory or path then the command  `find -name "filename.txt"` will print all the files with the specified name that are in your current directory and its subdirectories.

Example: Let's say you want to want to find all files named "java" in your usr directory then you would type:
```
$ find ./usr -name "java" 
```
and get:
```
usr/share/bash-completion/completions/java   
usr/share/java                               
usr/bin/java                                 
usr/lib/ure/share/java                       
usr/lib/jvm/java-7-openjdk-amd64/bin/java    
usr/lib/jvm/java-7-openjdk-amd64/jre/bin/java
```

If you know the type of file, but don't remember the name you can use:
`$ find ./directory-path -name "*.txt"`
and you will get all txt files in the file directory you search.

Example: Let's say you, being the curious person you are, want to find the paths to all text files in your `./lib/firmware` directory. Since we have our wild card * and we know that all text files end with "txt" we can combine these two and type:  
```
$ find ./lib/firmware -name "*.txt" 
```
Since * can be any number of characters we get:
```
/lib/firmware/carl9170fw/CMakeLists.txt              
/lib/firmware/carl9170fw/carlfw/CMakeLists.txt      
/lib/firmware/carl9170fw/minifw/CMakeLists.txt     
/lib/firmware/carl9170fw/config/CMakeLists.txt    
/lib/firmware/carl9170fw/tools/CMakeLists.txt    
/lib/firmware/carl9170fw/tools/src/CMakeLists.txt    
/lib/firmware/carl9170fw/tools/carlu/CMakeLists.txt  
/lib/firmware/carl9170fw/tools/lib/CMakeLists.txt    
```

NOTE: Just as in the previous example if you do not specify a directory or path then the command `find -name "*.txt"` will print all files of the specified type that are in your current directory and its subdirectories.

Remember: File names might be slightly different depending on your linux distribution. 

##Directory Traversal

When using find it is important to remember that all subdirectories are searched recursively, which is how all files of a given extension are found. If you do not want to travel through the entire recursive path then you can specify the depth of directory traversal. You can specify the depth of your traversal by using `maxdepth [number-levels]`

Let's say you want to only search in your current directory then use:
```
$ find ./directory-path -maxdepth 1 
``` 
and get:
```
./directory-path/files
```

If instead you wanted to search up to one subdirectory then you simple replace `-maxdepth 1` by `-maxdepth 2` and type:
```
$ find ./directory-path -maxdepth 2 
``` 
to get:
```
./directory-path/files               
./directory-path/subdirectories/files
```

Example: 
```
$ find ./usr -maxdepth 1
./usr                   
./usr/sbin             
./usr/games           
./usr/include          
./usr/src             
./usr/share          
./usr/bin           
./usr/local        
./usr/lib         
```

If you were to combine -maxdepth with -name to look for your sbin directory within your usr directory then your terminal would look like:
```
$ find ./usr -maxdepth 1 -name "sbin" 
./usr/sbin                            
```

NOTE: You can also use `-mindepth [number-levels]` to go to least the number of levels specified before searching for the files.

##Search by Type

When using find you can choose to search for specific types of files. You may want to only find regular files or only directories.
To only find files we append `-type f` after  `./directory-path`
To only find directories we append `-type d` after `./directory-path`
Just as before we may choose to add a directory or path and if we don't then all files and subdirectories in the current directory will be recursively searched. We also have the option to add `-name "filename"` after `-type f/d`. If we do not specify a name all files or directories (depending which you specified) in the specified directory-path will be recursively printed. 

example for only files:
```
$ find ./directory-path -type f      
./directory-path/files               
./directory-path/subdirectories/files
```

example for only directories:
```
$ find ./directory-path -type d              
./directory-path/directories                 
./directory-path/subdirectories/directories  
```

Let's say you want to find all the files in the root bin directory that end with grep. Then you would combine -type f and -name and grep as follows:

```
$ find ./bin -type f -name "*grep"
```

and get:
```
./bin/fgrep  
./bin/grep   
./bin/zgrep  
./bin/zfgrep 
./bin/egrep 
./bin/zegrep 
./bin/bzgrep 
```

If you were to type:
```
$ find ./bin -maxdepth 1 -type f -name "*grep" 
```
then you would get the same result as above.


##Search by Permission

You can use find to search for files based on their specific permissions. Let's say you want to search for all the executable files in your usr/bin directory then you would type:
```
$ find ./usr/bin -perm /a=x 
```
and you would get a long list of your executable files.

On the other hand if you wanted to find read only files you would use:
```
$ find ./usr/bin -perm /u=r 
```

You can combine -perm with -maxdepth by doing:
```
$ find ./usr/bin -maxdepth 1 -perm /u=r 
```

##Miscellaneous

###Search multiple directories 
Let's say you want to search  for a filename and know that is either in directory1 or directory2. Using find allows you to search inside two separate directories by simply appending the second directory after the first when using the find command. We can use:
```
$ find ./directory1-path ./directory2-path 
./directory1-path/files                  
./directory1-path/subdirectories/files   
./directory2-path/files                 
./directory2-path/subdirectories/files   
```

###Find hidden files
Since we know that hidden files on linux begin with a period, we can use the following to search for hidden files:
```
$ find ~ -type f -name ".*"
```

###Find files by size
Let's say one day you forget everything about a file you are working on, but happen to remember its size was 50 MB then you can use find to search for the file using its size. All you would do is type:
```
$ find / -size 50M 
```
Now let's say you think it's between 50MB and 100MB then you would type:
```
$ find / -size +50M -size -100 
```


###Find files for user
Using the find command can help us find files belonging to a particular user. We just need to search in the /root directory such as:
```
$ find ./ -user username           
./home/username/files                           
./home/username/directories/files                
./home/username/directories/subdirectories/files
```

We can use any combination of all the search options and narrow down the search such as:
```
$ find . -user username -name '*.txt'
```

###Deleting files/directories
You can also use find command to remove all specied types of files in a specified directory or path. You can do this by appending `exec rm -f {} \;` after identifying the filename/filetype such as:
```
$ find /directory-path -type f -name "*txt" -exec rm -f {} \;
```
The above command deletes all text files int the directory-path directory. You can switch `f` for `d` to remove directories instead and change `*txt`. 

Now let's say you are running out of space in your computer and since all your files are backed up (and on github) you want to delete all files larger than 100 MB. Then you would do:
```
find ./home/username/diretory-path -type f -name *.log -size +100M -exec rm -f {} \;
```

As you can see find can be used in various ways and mastering all of these techniques will come in handy when you begin to search for files in order to execute certain commands on them. As the previous examples shows you can use find with -exec in various ways. That, however, is not the full extent of find! You can use find in combination with xargs, grep and even pipes. Be creative and try out a few combinations and soon enough you will be a pro at using find.
