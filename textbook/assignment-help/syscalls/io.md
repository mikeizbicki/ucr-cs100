Input and Output System Calls
===
This document describes the system calls pertaining to input and output redirections. These system calls involve manipulating file descriptors such as stdin(0), stdout(1) and stderr(2). The system calls that will be described here are `pipe` and `dup`

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
   if(-1 == close(fd[PIPE_READ]))//close the read end of the pipe because we're not doing anything with it right now
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

   if(-1 == dup2(savestdin,0))//restore stdin
      perror("There is an error with dup2. ");
}
```

Here we see the full use of the `pipe` syscall. When we call `pipe` we have our `int fd[2]` as the parameter, `pipe` populates this array with the file descriptors of the read and write end of the imaginary file that is created. Then we `fork` the process, and in the child we change the stdout of whatever you are running to the write end of the imaginary file. In our example of `names|sort` the output of our names executable will be the input of our file. Then we go to our parent function and set the stdin to the read end of the `pipe`. We do this because we want the thing we wrote to the imaginary file to be the input to the right side of the pipe. In our example `names|sort` we want the names output to be the input of the sort program. After this we have to immediately call another `fork` function to execute the right side of the pipe.



