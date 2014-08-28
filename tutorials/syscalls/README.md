#Syscalls and How to Use Them

Here, we will present a list of functions that will be useful when programming your own shell.  These functions are called system calls, they differ from regular functions because a syscall requests a specific service from the operating system’s kernel. 

What’s really cool about syscalls is how you can check if an error occured. Each syscall has access to a universal variable ‘errno’ (include <errno.h> to use this variable) that it sets to indicate what error happened. The return value of each syscall tells you whether an error occurred, be sure to check what return value indicates an error occurred. 

Syscalls might seem confusing to use but we’ll try our best to explain some of them in this list! If you want any more info be sure to google the man page.



##fork:

**includes:**  `#include <unistd.h>`

**declaration:** `pid_t fork(void);`

**returns:** fork returns the pid of the child process that it creates, if an error occurs -1 is returned.

[man page](http://linux.die.net/man/2/fork)

Fork creates a new process so you can have two things happening at once. To create this new process fork creates a copy of the process that was already running. This new process is called a child process. 

If you’re creating your own bash shell you will need to use fork. When you create your own bash shell you will use the child process of the fork to execute all of your commands. Inside of the child process is where you’ll use exec.

Fork is one of the more complicated syscalls and is harder to understand, we highly encourage you look up more on it.

Here is an example of fork:
```
int pid = fork();
if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process "; 
   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
```

Here we’re setting pid, which is an int (which also works even though the declaration returns pid_t), to the pid ID of the child process when we’re in the parent, else we return 0 in the child. Everything that happens inside the if statement is everything the child process executes. This happens because fork returns 0 when it is the child process, that’s how we know when to go in the if statement. You have to have the exit() statement when you’re done executing everything you want to in the child or else the child will run alongside the parent. 

##perror:

**includes:** `#include <stdio.h>, #include <errno.h>`

**declaration:** `void perror(const char *s);`

**returns:** No return value.

[man page](http://linux.die.net/man/3/perror)

Perror is used when an error occurs in a syscall. The parameter of of perror (const char *s) is whatever c-string you wish to output when an error happens. Perror outputs your custom c-string and then it outputs information on the specific error that happened using information from errno. 
    Perror becomes very useful when you’re debugging your program. If something has gone wrong and you don’t know why, you should add perror statements after each syscall. If an error happened you’ll get your own custom message about it. Perrors are extremely crucial while coding, and adding them after each syscall is considered proper coding etiquette - in fact, many instructors and professors may dock points for not having them. 

Now, we’ll add perror to the last example:
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
This example adds perror to the example we started in fork. The if statement basically says, if there’s an error in the syscall then output an error message and exit the program. As you can see, perror’s parameter is a c-string, in this case it’s, “There was an error with fork().” this message can be customized however you wish to be more descriptive, for example you can state at what line of the code the error is happening at, so you can go back and try to fix the error.

##wait:

**includes:** `#include <sys/types.h>`
          `#include <sys/wait.h>`

**declaration:** `pid_t wait(int *status);`
        usually when using wait, it is used as such: `wait(0);`

**returns:** When an error occurs -1 is returned otherwise it returns the pid of the child that was killed.

[man page](http://linux.die.net/man/2/wait)

examples: here is an example of wait with fork.
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

Notes: Wait is commonly used along with the fork function (and is pretty much necessary). Wait is used in the parent function, and tells the parent process to wait for the child process to finish executing before moving on. It also prevents two processes from running at once. However, if you want a process to run in the background in your shell you don't want to wait.

##exec:

**includes:** `#include <unistd.h>`

**declaration:** (multiple declarations depending on which exec funtion is used)

Here is an example of the two most common ones: `int execv(const char *path, char *const argv[]);`  `int execvp(const char *file, char *const argv[]);`

**returns:** exec only returns if there was an error, and in that particular case, it returns a -1.

[man page](http://linux.die.net/man/3/exec)

Exec can be used to perform commands in the bash shell, such as ls, cat, and echo, they usually take in some form of converted user input. The two most commonly used ones are execv and execvp. We encourage you to look up the other forms of exec. 
Execv requires that you append the path for the command to it, while execvp will automatically retrieve the path for you. Unless you are specifically required to use execv (e.g. your instructor wants you to use the path variable to find the particular command the user input), PLEASE use execvp. It will save you so much time, and will give you many more hours of much needed sleep.

We’ll show you an example of execvp that was used in created a bash shell, this call to execvp is in the child process(refer to fork):
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

(Again, we’re using perror to check for errors. Please use this method when doing your own programming!) 
The parameters for execvp are: (const char *file, char *const argv[]). In this example file is argv[0] and argv[] is argv. Our argv is the user input of what command they want to execute each element of argv is a part of the command. For example, the user can input “ls -l -a” and argv[0] = ls, argv[1]=-l, argv[2]=-a. 
As we told you above, execvp finds the path for you. If you wanted to use execv you would have to add the path to the front of the command, for example if you input “ls” the program would change it to “/usr/bin/ls” for the execv call.

##pipe:

**includes:** `#include <unistd.h>`
          `#include <fcntl.h>`

**declaration:** There are two different declarations for pipe:
               `int pipe(int pipefd[2]);`
               `int pipe2(int pipefd[2], int flags);`

**returns:** When an error occurs -1 is returned, otherwise 0 is returned.

[man page](http://linux.die.net/man/2/pipe)

Pipe is another syscall that is harder to understand, please look up more information on the man page if you need it!
   
Essentially, pipe creates an imaginary file that you can write and read to. The parameter is an int array with two elements, these are the file descriptors for the imaginary file. fd[0] is the read end of the pipe and fd[1] is the write end of the pipe. 

This function is extremely useful when implementing piping in your own bash shell. Piping is moving the stdout of the left side of the pipe into the stdin of whatever program is on the right side of the pipe. For example, you have an executable “names” which outputs a list of names in a random order you can pipe this into “sort” which will sort it alphabetically. This command would look like: “names | sort”.
   
Now that we’ve gone over the basics of what piping is we can talk about how to use the syscall pipe to create this. Because pipe creates an imaginary file that you can read and write from you can use this to do your own piping. You will take the stdout of the command on the left side of the pipe symbol ( | ) and write it to the pipe with dup. Then, later, you will read that data from the read end of the pipe.
 
Here’s an example using pipe:
```
int fd[2];
if(pipe(fd) == -1)//call to pipe, it puts the read end and write end file descriptors in fd
   perror("There was an error with pipe(). ");

int pid = fork();
if(pid == -1)//fork’s return value for an error is -1
{
   perror("There was an error with fork(). ");
   exit(1);//there was an error with fork so exit the program and go back and fix it
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process ";

   //write to the pipe
   if(-1 == dup2(fd[1],1))//make stdout the write end of the pipe 
      perror("There was an error with dup2. ");
   if(-1 == close(fd[0])//close the read end of the pipe
      perror("There was an error with close. ");

   if(-1 == execvp(argv[0], argv)) 
      perror("There was an error in execvp. ");


   exit(1);  //when the child process finishes doing what we want it to, cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   //read end of the pipe
   int savestdin;
   if(-1 == (savestdin = dup(0)))//need to restore later or infinite loop
      perror("There is an error with dup. ")
   if(-1 == dup2(fd[0],0))//make stdin the read end of the pipe 
      perror("There was an error with dup2. ");
    if(-1 == close(fd[1])//close the write end of the pipe
      perror("There was an error with close. ");
   if( -1 == wait(0)) //wait for the child process to finish executing
      perror(“There was an error with wait().);

   //here you have to do another fork to execute the right side of the pipe command, as in the above example (“names | sort”) you would execute the sort command, we will leave this as an example for you to do.

}
if(-1 == dup2(savestdin,0))//restore stdin
   perror("There is an error with dup2. ")
```

Here we see the full use of pipe to implement piping in a shell. When we call pipe we have our int fd[2] as the parameter, pipe populates this array with the file descriptors of the read and write end of the imaginary file that is created. Then we fork the process, and in the child we change the stdout of whatever you are running to the write end of the imaginary file. In our example of “names|sort” the output of our names executable will be the input of our file. Then we go to our parent function and set the stdin to the read end of the pipe. We do this because we want the thing we wrote to the imaginary file to be the input to the right side of the pipe. In our example “names|sort” we want the names output to be the input of the sort program. After this we have to immediately call another fork function to execute the right side of the pipe. For this we have to call a function that is similar to the exec example, we will leave this as a workable example for you.

##getcwd:

**includes:** `#include <unistd.h>`

**declaraton:** `char *getcwd(char *buf, size_t size);`

**returns:** When successful, the function returns a pointer to a string containing the pathname of the current working directory. On error, it returns NULL.

[man page](http://linux.die.net/man/3/getcwd)

As stated above, getcwd gets the c-string containing the current working directory. It inserts the c-string into buf to be used later. The parameter size is the length of the char* you pass in as the first parameters. For example, if you created char directory[250], you’d pass in (directory, 250).

Notes: This function is useful when implementing bash commands such as cd, and you need to display the current working directory the user is in. 

Here is a quick example of getcwd in action:
```
char buf[1024];
if(!getcwd(buf,1024))
   perror(“problem with getcwd.”);
```

buf now contains the path to the current directory you're in, you can output it before your command line prompt to simulate the real bash shell. Because cd is not a built-in command in a bash shell you will have to implement it with getcwd instead of using exec.

##getpwuid:
**includes:** `#include <pwd.h>`
          `#include <sys/types.h>`

**declaraton:** `struct passwd *getpwuid(uid_t uid);`

**returns:** If an error occurs NULL is returned, otherwise it returns a pointer to a passwd struct(seen below)
 
Notes: As you can probably see, getpwuid is a bit different, as it is a struct. It takes in the  user’s ID, which is in a numerical form. After that, it will return a pointer to a structure, which contains these fields:
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

For the most up to date version of this struct, please visit the [man page](http://linux.die.net/man/3/getpwuid)

The main purpose of this function is  to assist in finding info about the user, and their info. This is particularly useful when implementing things such as ls (an assignment in cs-100), and is necessary to implement the -l flag for ls.

Here’s a quick implementation of getpwuid, where s is a stat struct:
```
struct passwd *pw;
if(!(pw = getpwuid(s.st_uid)))
   perror("there was an error in getpwuid. ");
```

##getgrgid:

**includes:** `#include <sys/types.h>`
          `#include <grp.h>`

**declaraton:** `struct group *getgrgid(gid_t gid);`

**returns:** If an error occurs NULL is returned, otherwise it returns a pointer to a group struct
 
Much like getpwuid, getgrgid also returns a pointer to a structure, which contains these fields:
```
struct group {
    char   *gr_name;       /* group name */
    char   *gr_passwd;     /* group password */
    gid_t   gr_gid;        /* group ID */
    char  **gr_mem;        /* group members */
};
```

For the most up to date version of this struct, please visit the [man page](http://linux.die.net/man/3/getgrgid)


The main purpose of this function is  to assist in finding info about the group and its info, and much like getpwuid, is particularly useful  when implementing things such as ls (an assignment in cs-100), and is necessary to implement the -l flag for ls.

Here’s a quick implementation of getgrgid, where s is a stat struct:
```
struct passwd *gp;
if(!(gp = getgrgid(s.st_gid)))
   perror("there was an error in getgrgid. ");
```

##Conclusion:

Thanks for reading our short tutorial on a couple of important syscalls! These only scratch the surface of the many syscalls that exist, and we encourage you to explore as many of them as you can. We hope that our explanations, as well as our coding examples can greatly help your understanding of some initially confusing syscalls. Be sure to refer to the man pages of each syscall for the most up-to-date informatioin!
