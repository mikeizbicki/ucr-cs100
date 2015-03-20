#Mastering the find command

The find command let's you search for files from the command line. The find command is available on most linux distros by default. Find locates any files on your computer. We can locate files based on various search criterias. We can search by file type, name, permissions, user ownership, size, ect. Find travels down to all directories recursively to search for our file.

The basic syntax is:
```
$ find [location] [comparison-criteria] [search-term]
```

##Simple examples:

The simplest example is to use find to print the names of all the files in your working directory. This will include all dot files and all subdirectories as well. You can do this by writing:
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

##Search a specific directory or path

You can also choose to search for a specific directory or path. Do this by appending the directory name/path after find. You should see all files in that directory/path as long as the directory/path exists within the current directory.
 
Example: Let's say you wanted to see all the files in your usr/bin directory because you are curious as to how it is different from your root bin. Then type:
```
$ find ./usr/bin 
```
 
Once again you would get a long list of the paths to all your `./usr/bin` files. You should have no trouble seeing all the paths since ./usr is in you root directory and /bin is in your usr directory. Let's say you are lazy and you don't want to scroll all the way back up to see the files that start with a. What can you do? You can append `/a*` to the file path. In bash `*` can represent any number of characters (including zero). So if you type:

```
$ find ./usr/bin/a* 
```

you will get the paths to all file in your usr/bin directory that start with a. This is because a will be read in and `*` will represent any number of characters. And if you do:

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

##Search by file name 

Looking through so many file paths can be exhausting! With find if you know the file name you can search for files by their names using the following:

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
```
$ find ./directory-path -name "*.txt"
```
and you will get all txt files in the file directory you search.


##Directory Traversal

When using find it is important to remember that all subdirectories are searched recursively. This is how all files of a given extension are found. If you do not want to travel through the entire recursive path then you can specify the depth of directory traversal. You can specify the depth of your traversal by using:
```
maxdepth [number-levels]
```


Let's say you want to only search in your current directory then use:

```
$ find ./directory-path -maxdepth 1
```

If instead you wanted to search up to one subdirectory then you would replace `-maxdepth 1` by `-maxdepth 2` and type:
```
$ find ./directory-path -maxdepth 2 
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


If you were to combine `-maxdepth` with `-name` to look for your sbin directory within your usr directory then your terminal would look like:

```
$ find ./usr -maxdepth 1 -name "sbin" 
./usr/sbin                            
```

NOTE: You can also use `-mindepth [number-levels]` to go to least the number of levels specified before searching for the files.


If you were to type:

```
$ find ./bin -maxdepth 1 -name "*grep" 
```

then you would get the same result as the example:

```
$ find ./bin -name "*grep"
./bin/fgrep  
./bin/grep   
./bin/zgrep  
./bin/zfgrep 
./bin/egrep 
./bin/zegrep 
./bin/bzgrep 
```

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


##Search multiple directories 
Let's say you want to search  for a file and all you know is that it's either in directory1 or directory2. No need to search both directories separately. Find allows you to search both directories at the same time. All we have to do is append directory2 after directory1! We can use:

```
$ find ./directory1-path ./directory2-path 
./directory1-path/files                  
./directory1-path/subdirectories/files   
./directory2-path/files                 
./directory2-path/subdirectories/files   
```

##Find hidden files
Since we know that hidden files on linux begin with a period, we can use the following to search for hidden files:

```
$ find ~ -type f -name ".*"
```

##Find files by size
Let's say one day you forget everything about a file you are working on. If all you remember is that its size was 50 MB, then you can use find to search for the file using its size. All you would do is type:

```
$ find / -size 50M 
```

Now let's say you think it's between 50MB and 100MB then you would type:

```
$ find / -size +50M -size -100 
```


##Find files for user
Using the find command can help us find files belonging to a particular user. We just need to search in the root directory as follows:

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

##Search by Type

When using find you can choose to search for specific types of files. You may want to only find regular files or only directories.
To only find files we append `-type f` after  `./directory-path`
To only find directories we append `-type d` after `./directory-path`

Just as before we may choose to add a directory or path. If we don't then all files and subdirectories in the current directory will be recursively searched. We also have the option to add `-name "filename"` after `-type f/d`. If we do not specify a name all files or directories (depending which you specified) in the specified directory-path will be recursively printed. 

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

Now for a real life example:
Let's say you have all your pictures in jpg format, but you want to convert them all to png for whatever reason.
We can do this by using find with loops! 

```
for f in $(find ./home -type f -name "*.jpg"); do convert $f $f.png; done
```

The above command will search your home directory for all `*jpeg` files. When a `.jpg` file is found we will then run the command `convert`  and convert the file to a `.png` file. 
If we did not use find in the loop and instead used the built-in bash glob like:

```
$ for f in *; do convert $f $f.png; done
```
then every file in your current working directory would be changed. We would not recursively descend into the subdirectories. It is not good to run this if you have various file types in your current working directory. We might get some errors when convert fails to convert some files.

The find command allows us to run arbitrary commands inside the loop. So if we wanted to do something else with the files we found we would change the command `convert` for whatever it is we wanted to do. We could run multiple commands or pass in a command that will run for each file we found.


##Deleting files/directories
You can also use find command to remove all specied types of files in a specified directory or path. We can do this since we saw in the previous section that find allows us to run commands on the files we found. We can delete files by appending `exec rm -f {} \;` after identifying the filename/filetype such as:

```
$ find /directory-path -type f -name "*txt" -exec rm -f {} \;
```

The above command deletes all text files int the directory-path directory. You can switch `f` for `d` to remove directories instead and change `*txt`. 

Now let's say you are running out of space in your computer and since all your files are backed up (and on github) you want to delete all files larger than 100 MB. Then you would do:

```
find ./home/username/diretory-path -type f -name *.log -size +100M -exec rm -f {} \;
```

As you can see find can be used in various ways. Mastering all of these techniques will come in handy when you want to execute certain commands on certain files. As the previous examples shows you can use find with -exec in various ways. That, however, is not the full extent of find! You can use find in combination with xargs, grep and even pipes. Be creative and try out a few combinations and soon enough you will be a pro at using find.
