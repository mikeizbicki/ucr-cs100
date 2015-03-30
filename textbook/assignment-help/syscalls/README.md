#Syscalls and How to Use Them

Within this folder, you will find tutorials on functions that will be useful when programming your own shell.  These functions are called system calls, or syscalls, and they differ from regular functions because a syscall requests a specific service from the operating system’s kernel.

All system calls will be described in their respective files, but there will be a brief description of what each does here. exec.md will explain system calls relating to `exec` and includes `fork`, `wait`, and `exec`. io.md will include system calls that relate to input and output redirection and include `dup` and `pipe`. dir.md covers the three system calls `opendir`, `readdir`, and `closedir` which solely deal with directory access and properties. stat.md will explain the system calls related to gathering all the collective info on a file, including  `stat`, `fstat`, `lstat`. getinfo.md will include system calls that retrieve information about a process or environment variable. These include `getcwd`, `getpwuid`, and `getgrgid`. Lastly, the file `fd.md` covers files related to manipulating file descriptors: `open`, `read`, `write`, and `close`.

Also included are demonstrations which walk through the reasoning behind the structure of some of these code blocks, and why they're used in conjunction with these system calls to achieve a greater goal. Currently, `dir.md` and `fd.md` each have their own `_demo` files with the `stat.md` housing its own demonstration.

`exec`: will execute a file

`fork`: will create a copy of the running process

`wait`: will wait for a child process and reap it

`dup`: creates a copy of a file descriptor

`pipe`: creates a pipe, or data channel for communication

`opendir`: creates a pointer to a stream of a directory's entries

`readdir`: access a directory's entries' properties

`closedir`: close the stream to a directory's entries

`stat`: gets information about a passed in file

`fstat`: gets information about a file passed in by a file descriptor

`lstat`: gets information about a passed in file or symbolic link, depending on what was passed in

`getcwd`: gets the current working directory

`getpwuid`: gets information about a passed in username

`getgrgid`: gets information about a group which matches a passed in group ID

`open`: creates a file descriptor to a file

`read`: adds to a file descriptor or buffer the contents of a passed in file descriptor

`write`: adds to a file descriptor the contents of another file descriptor or buffer

`close`: closes the passed in file descriptor, sealing all changes made to it

The only function we will discuss in this README will be `perror`, an error checking function which should be used with every system call.

Syscalls might seem confusing to use but we’ll try our best to explain some of them in this list! If you want any more information we've included a link to the man page for each syscall.

##perror:

**includes:** `#include <stdio.h>, #include <errno.h>`

**declaration:** `void perror(const char *s);`

**returns:** No return value.

[man page](http://linux.die.net/man/3/perror)

The glorious error checker! `perror` is used when an error occurs in a syscall, and technically isn't a syscall - rather its used WITH every single syscall. The parameter of `perror`, `const char *s`, can be any c-string you wish to output when an error happens (examples below). `perror` will output the c-string you specify followed by information on the specific error that happened using information from `errno`. These are output to `stderr` so in the event that you mess up your standard output, `stdout` or `cout`, it will still print to the screen (unless you mess up your `stderr` too, then I'm sorry it won't help).

`errno` is a global `int` variable that is written to by system calls upon exiting (if it was successful, `errno` is still set, but to success), and will be set to a different value based on the reason the syscall failed. There is no need to try to remember the actual value for each error, `perror` will automatically print out the corresponding error based on the value of `errno` when it is called. If there is any reason that you need these values for checking why a system call failed, they are given as macros in the man page of the specific system call. Examples on the output will be shown in the example below.

For these reasons, `perror` is very useful when you’re debugging your program. It will give you not only your message which should indicate which system call failed, but also an error message from the system that is specified by `errno`. `perror` is extremely crucial while coding, and adding them after each syscall is considered proper coding etiquette - in fact, many instructors and professors may dock points for not having them (I was a "victim" of this my first assignment). The reason for this is because there are many reasons as to why a system call may fail and if you do not properly check each one, they can cause large and also confusing errors.

Now, we will show an example of `perror` with `fork`:
```
int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   //perror("There was an error with fork(). ");
   perror("fork"); //although you certainly can use the above, it is good
                   //practice not to write more information than necessary
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process ";
   exit(1);  //when the child process finishes doing what we want it to, cout, 
             //we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
```

So if fork fails, the output will look something like this:

`fork: Resource temporarily unavailable`

We can see that it outputs our `char *` appended by a `:` and then the error message from the system.

We use the `if` statement to see if our system call failed. Generally system calls will return `-1` or `NULL` upon error depending on what data type they return. In this case, `fork` returns `-1` so we check to see if it failed. If it did, then output an error message and exit the program. As you can see, we set our parameter for `perror` as simply, `fork`. This message can be customized however you desire. Additional useful information you can output is the function it’s in, the line it’s on in your code, among other things - the choice is yours! But beware, with great power comes great responsibility! Outputting error messages that are irrelevant or unnecessarily long are unlikely to be very helpful.

