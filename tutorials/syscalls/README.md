#Syscalls and How to Use Them

Here, we will present a list of functions that will be useful when programming your own shell.  These functions are called system calls, and they differ from regular functions because a syscall requests a specific service from the operating system’s kernel. 

What’s really cool about syscalls are its error checking capabilities. Each syscall has access to a universal variable `errno`, `include <errno.h>` is required to use this variable, that is set to indicate what error has occured. The return value of each syscall can be furthered combined with other functions to make error checking much easier, which can save many headaches in the long run.

Syscalls might seem confusing to use but we’ll try our best to explain some of them in this list! If you want any more information we've included a link to the man page for each syscall.


##fork:

**includes:**  `#include <unistd.h>`

**declaration:** `pid_t fork(void);`

**returns:** `fork` returns the pid of the child process that it creates, if an error occurs -1 is returned.

[man page](http://linux.die.net/man/2/fork)

This is perhaps one of the most important syscall of them all (one syscall to rule them all!) so make sure you really understand this one.

`fork` creates a new process so you can have two things happening at once (multitasking, huzzah!). To create this new process, `fork` creates a copy of the process that was already running. This new process is called a child process, while the older process is called the parent process. 

If you’re creating your own bash shell you will HAVE to use `fork`. You'll use the child process of the `fork` to execute all of your commands. Inside of the child process is where you’ll use functions such as `exec`, which require two processes (more on this later).

`fork` is without a doubt one of the more complicated syscalls and is harder to understand; therefore, we highly encourage you read up on it from multiple sources, and really gain a good understanding of it.

Here is an example of `fork`:
```
int pid = fork();
if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process "; 
   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   if( -1 == wait(0)) //wait for the child process to finish executing, wait will be explained later on
   perror(“There was an error with wait().”);
}

```

Here we’re setting `pid`, which is an `int`, which also works even though the declaration returns `pid_t`, to the pid of the child process when we’re in the parent, else we return 0 in the child. Everything that happens inside the if statement is everything the child process executes. This happens because `fork` returns 0 when it is the child process, and that’s how we know when to go in the if statement. You have to have the `exit()` statement when you’re done executing everything you want to in the child. If the exit statement isn't present, the child will become a zombie process - that is, it will never never exit, and continue to run in the background, taking up memory and hampering the program's performance - and we don't want that do we? 

Of course, with a child function, there has to be a parent function. In this particular function, the parent function simply waits for the child process to finish running (because of the wait call, which will be explained later), and executes after the child process is finished.

##perror:

**includes:** `#include <stdio.h>, #include <errno.h>`

**declaration:** `void perror(const char *s);`

**returns:** No return value.

[man page](http://linux.die.net/man/3/perror)

The glorious error checker! `perror` is used when an error occurs in a syscall, and techincally isn't a syscall - rather its used WITH every single syscall. The parameter of of `perror` which is a `const char *s` is whatever c-string you wish to output when an error happens (examples below). `perror` outputs your custom c-string and then outputs information on the specific error that happened using information from `errno`. 
    `perror` becomes very useful when you’re debugging your program. If an error happens you’ll be able to ouput your own custom message, which can make the error much easier to find. `perror` is extremely crucial while coding, and adding them after each syscall is considered proper coding etiquette - in fact, many instructors and professors may dock points for not having them (I was a "victim" of this my first assignment). 

Now, we’ll add `perror` to the last example:
```
int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   perror("There was an error with fork(). ");
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process "; 
   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
```
This example adds `perror` to the example we started in `fork`. The if statement basically says if there’s an error in the syscall, then output an error message and exit the program. As you can see, the parameter for `perror` is a c-string, in this case it’s, `There was an error with fork().` This message can be customized however you desire. You can output info about the function its in, the line its on - the choice is yours! But beware, with great power comes great responsibility! Outputting error messages that are irrelevant to your function/program are unlikely to be very helpful.

##wait:

**includes:** `#include <sys/types.h>`
          `#include <sys/wait.h>`

**declaration:** `pid_t wait(int *status);`
        usually when using `wait`, it is used as such: `wait(0);`

**returns:** When an error occurs -1 is returned otherwise it returns the pid of the child that was killed.

[man page](http://linux.die.net/man/2/wait)

`wait` is a system call that is used to wait for state changes in a child function of the parent process. It also obtains information about the child function when its state changes. 

`wait` is commonly used along with the `fork` function (and is pretty much a necessity). `wait` is usually used in the parent function, and tells the parent process to wait for the child process to finish executing before moving on. It also prevents two processes from running at once. However, if you want a process to run in the background in your shell (aka you want two processes running at the same time), you wouldn't want to use `wait`.

examples: here is an example of `wait` with `fork`.
```
int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   perror("There was an error with fork(). ");
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process "; 
   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   if( -1 == wait(0)) //wait for the child process to finish executing
   perror(“There was an error with wait().”);
}
```

##exec:

**includes:** `#include <unistd.h>`

**declaration:** (multiple declarations depending on which `exec` funtion is used)

Here is an example of the two most common ones: `int execv(const char *path, char *const argv[]);`  `int execvp(const char *file, char *const argv[]);`

**returns:** `exec` only returns if there was an error, and in that particular case, it returns a -1.

[man page](http://linux.die.net/man/3/exec)

`exec` can be used to perform commands in the bash shell, such as `ls` `cat` and `echo`, they usually take in some form of converted user input. The two most commonly used ones are `execv` and `execvp`, but we encourage you to look up the other forms of `exec`! 

Now you may be wondering what the difference between the two of them is. `execv` requires that you append the path for the command to it, while `execvp` will automatically retrieve the path for you. Unless you are specifically required to use `execv` (e.g. your instructor wants you to use the path variable to find the particular command the user input), PLEASE use `execvp`. It will save you so much time, and will give you many more hours of much needed sleep.

We’ll show you an example of `execvp` that was used in the child function, in a program meant to create a bash shell:

```
int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   perror("There was an error with fork(). ");
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process ";
   if(-1 == execvp(argv[0], argv)) 
      perror("There was an error in execvp. ");


   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   if( -1 == wait(0)) //wait for the child process to finish executing
   perror(“There was an error with wait().);
}
```

(Again, we’re using `perror` to check for errors. PLEASE remember to do so as well!)

The parameters for `execvp` are: `const char *file, char *const argv[]`. In this example, `file` is `argv[0]` and `argv` is `argv[]`. `argv`, in this example, is a char pointer pointer containing the user input of what commands they wish to execute. 

For example, the user can input `ls -l -a` and `argv[0] = ls`, `argv[1]= -l`, `argv[2]= -a`. So esentially, `argv[0]` is the command, while everything after is the flag.

As we told you above, `execvp` finds the path for you. If you wanted to use `execv` you would have to add the path to the front of the command, for example if you input `ls` the program would change it to `/usr/bin/ls` for the `execv` call.


##dup:

**includes:** `#include <unistd.h>`

**declaration:** These are the two `dup` declarations that are most useful: 
                 `int dup(int oldfd);`  `int dup2(int oldfd, int newfd);`

**returns:** When an error occurs `dup` returns -1 otherwise `dup` returns the new file descriptor.

[man page](http://linux.die.net/man/2/dup)

We all know about the default file descriptors 0, 1 and 2 with 0 meaning stdin, 1 meaning stdout and 2 meaning stderr. `dup(int oldfd)` can be used to copy the file descriptor given for `oldfd`, for example we can do `int fd = dup(1)` which copies stdout to `fd`. `dup` chooses our new file descriptor by choosing the lowest number of the unused descriptors, so if we only have 0, 1 and 2 as our file descriptors(only the default ones) it will choose 3 as our new one. So, in this `dup` example our new `fd` can be used interchangeably with stdout. 

Now say, for example, we wanted to redirect the stdout to the screen into a file. We could use `dup2` (we could also use `dup` but I think `dup2` is a simpler way). The way `dup2` works is it takes two parameters `int oldfd` and `int newfd`, `oldfd` is the file descriptor you want to change to what the `newfd`. Let's take our redirect example, we want to take stdout which is 1 and instead of linking it to 1 we want to link it to whatever file descriptor belongs to the file we want to redirect to. For this redirection we would do something like: `dup2(fd,1)` (where `fd` is the file descriptor for the file we want to write to). `dup2` also closes `newfd` after the call. Therefore, after this call stdout is now closed and instead it is rerouted to the file.


In our previous example we've added a small snippet of `dup` at the end.
```
int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   perror("There was an error with fork(). ");
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process ";
   if(-1 == execvp(argv[0], argv)) 
      perror("There was an error in execvp. ");

   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   if( -1 == wait(0)) //wait for the child process to finish executing
      perror(“There was an error with wait().);

}
int savestdin;
if(-1 == (savestdin = dup(0)))//savestdin is now the same as regular stdin
   perror("There is an error with dup. ");
   
   //something can be done here to overwrite stdin, for example redirection
   
if(-1 == dup2(savestdin,0))//restore stdin, if we would have overwritten stdin this is how we would restore it
   perror("There is an error with dup2. ");
```

Here we can see both `dup` and `dup2` being used. 


##pipe:

**includes:** `#include <unistd.h>`
          `#include <fcntl.h>`

**declaration:** There are two different declarations for `pipe`:
               `int pipe(int pipefd[2]);`
               `int pipe2(int pipefd[2], int flags);`

**returns:** When an error occurs -1 is returned, otherwise 0 is returned.

[man page](http://linux.die.net/man/2/pipe)

`pipe` is another syscall that is harder to understand, so PLEASE utilize outside resources if need be!
   
`pipe` essentially creates an imaginary file that you can write to and read from. The parameter is an int array with two elements, which are the file descriptors for the imaginary file. In the example below, `fd[0]` is the read end of the pipe and `fd[1]` is the write end of the pipe. Let me be clear, however, that pipe ignores the input and only uses the write end as output to whatever it is piping to. 

This function is essential when implementing piping in a bash shell. Piping is moving the stdout of the left side of the pipe into the stdin of whatever program is on the right side of the pipe. For example, you have an executable `names` which outputs a list of names in a random order you can pipe this into `sort` which will sort it alphabetically. This command would look like: `names | sort`. The end result would be the contents of the name executable output to the screen, except sorted. 
   
Now that we’ve gone over the basics of what piping is we can talk about how to use the syscall `pipe` to create this. Because `pipe` creates an imaginary file that you can read and write from you can use this to implement piping in whatever program you desire to do so in. You will take the stdout of the command on the left side of the pipe symbol and write it to the pipe with `dup`. Then, later, you will read that data from the read end of the pipe.
 
Here’s an example of `pipe` in action:
```
const int PIPE_READ = 0;
const int PIPE_WRITE = 1;
int fd[2];
if(pipe(fd) == -1)//call to pipe, it puts the read end and write end file descriptors in fd
   perror("There was an error with pipe(). ");

int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   perror("There was an error with fork(). ");
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the first child process
{
   cout<<"This is the first child process ";

   //write to the pipe
   if(-1 == dup2(fd[PIPE_WRITE],1))//make stdout the write end of the pipe 
      perror("There was an error with dup2. ");
   if(-1 == close(fd[PIPE_READ])//close the read end of the pipe because we're not doing anything with it right now
      perror("There was an error with close. ");

   if(-1 == execvp(argv[0], argv)) 
      perror("There was an error in execvp. ");


   exit(1);  //prevents zombie process
}
//if pid is not 0 then we’re in the first parent
else if(pid > 0) //first parent function
{
   //read end of the pipe
   int savestdin;
   if(-1 == (savestdin = dup(0)))//need to restore later or infinite loop
      perror("There is an error with dup. ");
   if( -1 == wait(0)) //wait for the child process to finish executing
      perror(“There was an error with wait(). ");
   
   int pid2 = fork();
   if(pid2 == -1)//fork's return value for an error is -1
   {
      perror("There was an error with fork(). ");
      exit(1);//there was an error with fork so exit the program and go back and fix it 
   }
   else if(pid2 == 0)//when pid2 is 0 you are in the second child process
   {
      cout << "This is the second child process ";

      if(-1 == dup2(fd[PIPE_READ],0))//make stdin the read end of the pipe 
         perror("There was an error with dup2. ");
      if(-1 == close(fd[PIPE_WRITE])//close the write end of the pipe because we're not doing anything with it right now
         perror("There was an error with close. ");

      if(-1 == execvp(argv2[0], argv2))
         perror("There was an error in excecvp. ");

      exit(1); //prevents zombie process
   }
   else if(pid2 > 0) //second parent function
   {
      if(-1 == wait(0)) //wait for the child process to finish executing
         perror("There was an error with wait(). ");
   }
}
if(-1 == dup2(savestdin,0))//restore stdin
   perror("There is an error with dup2. ");
```

Here we see the full use of the `pipe` syscall. When we call `pipe` we have our `int fd[2]` as the parameter, `pipe` populates this array with the file descriptors of the read and write end of the imaginary file that is created. Then we `fork` the process, and in the child we change the stdout of whatever you are running to the write end of the imaginary file. In our example of `names|sort` the output of our names executable will be the input of our file. Then we go to our parent function and set the stdin to the read end of the `pipe`. We do this because we want the thing we wrote to the imaginary file to be the input to the right side of the pipe. In our example `names|sort` we want the names output to be the input of the sort program. After this we have to immediately call another `fork` function to execute the right side of the pipe.

##getcwd:

**includes:** `#include <unistd.h>`

**declaration:** `char *getcwd(char *buf, size_t size);`

**returns:** When successful, the function returns a pointer to a `string` containing the pathname of the current working directory. On error, it returns `NULL`.

[man page](http://linux.die.net/man/3/getcwd)

As stated above, getcwd gets the c-string containing the current working directory. It inserts the c-string into `buf` to be used later. The parameter size is the length of the `char*` you pass in as the first parameters. For example, if you created `char directory[250]`, you’d pass in `directory, 250`.

Notes: This function is useful when implementing bash commands such as `cd`, and you need to display the current working directory the user is in. 

Here is a quick example of `getcwd` in action:
```
char buf[1024];
if(!getcwd(buf,1024))
   perror(“problem with getcwd.”);
```

`buf` now contains the path to the current directory you're in, you can output it before your command line prompt to simulate the real bash shell. When you create your own bash shell you will have to implement `cd` with `getcwd` instead of using `exec`.

##getpwuid:
**includes:** `#include <pwd.h>`
          `#include <sys/types.h>`

**declaraton:** `struct passwd *getpwuid(uid_t uid);`

**returns:** If an error occurs `NULL` is returned, otherwise it returns a pointer to a `passwd struct` (seen below)

[man page](http://linux.die.net/man/3/getpwuid)
 
Notes: As you can probably see, `getpwuid` is a bit different from the other syscalls previously mentioned. It takes in the  user’s ID, which is in a numerical form. After that, it will return a pointer to a structure, which contains these fields:
```
struct passwd {
    char   *pw_name;       /* username */
    char   *pw_passwd;     /* user password */
    uid_t   pw_uid;        /* user ID */
    gid_t   pw_gid;        /* group ID */
    char   *pw_gecos;      /* user information */
    char   *pw_dir;        /* home directory */
    char   *pw_shell;      /* shell program */
};
```

The main purpose of this function is  to assist in finding info about the user, and their info. This is particularly useful when implementing things such as `ls` (an assignment in cs-100), and is necessary to implement the `-l` flag for `ls`.

Here’s a quick implementation of `getpwuid`, where `s` is a `stat struct`:
```
struct passwd *pw;
if(!(pw = getpwuid(s.st_uid)))
   perror("there was an error in getpwuid. ");
```

##getgrgid:

**includes:** `#include <sys/types.h>`
          `#include <grp.h>`

**declaraton:** `struct group *getgrgid(gid_t gid);`

**returns:** If an error occurs `NULL` is returned, otherwise it returns a pointer to a `group struct`

[man page](http://linux.die.net/man/3/getgrgid)
 
Much like `getpwuid`, `getgrgid` also returns a pointer to a structure, which contains these fields:
```
struct group {
    char   *gr_name;       /* group name */
    char   *gr_passwd;     /* group password */
    gid_t   gr_gid;        /* group ID */
    char  **gr_mem;        /* group members */
};
```

The main purpose of this function is  to assist in finding info about the group and its info, and much like `getpwuid`, is particularly useful  when implementing things such as `ls` (an assignment in cs-100), and is necessary to implement the `-l` flag for `ls`.

Here’s a quick implementation of `getgrgid`, where s is a `stat struct`:
```
struct passwd *gp;
if(!(gp = getgrgid(s.st_gid)))
   perror("there was an error in getgrgid. ");
```
