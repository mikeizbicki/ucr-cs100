#System calls relating to the use of Exec

This file will include the system calls needed to use `exec`. It will include `fork`, `wait` and `exec` itself. `fork` is necessary when using `exec` because `exec` will end the program upon completion and only return if it failed. Therefore we need to create a new process for it to run in. Then we need `wait` so that we do not have any zombie child processes and do not incur race conditions.

##fork:

**includes:**  `#include <unistd.h>`

**declaration:** `pid_t fork(void);`

**returns:** `fork` returns the pid of the child process that it creates to the parent, 0 to the child, or -1 if there was an error.

[man page](http://linux.die.net/man/2/fork)

This is perhaps one of the most important syscall of them all so make sure you really understand this one.

`fork` creates a new process so you can have two programs running at once (multitasking, huzzah!). To create this new process, `fork` creates a copy of the process that was already running. This new process is called a child, while the older process is called the parent.

It's important to note, that `fork` creates an exact copy of the parent process, and that the child and parent both continue running from the line immediately following `fork`. After this, there is no communication between the child and parent processes (except with `wait` or `pipe` which will be explained later), so anything changed in the parent or child after `fork` will not affect the other. You can think of this like a function which creates local copies of variables and once the function ends, these copies go out of scope and disappear.

If you’re creating your own bash shell you will HAVE to use `fork`. You'll use the child process of the `fork` to execute all of your commands because `exec` will end the process its running in upon completion.

`fork` is without a doubt one of the more complicated syscalls and is harder to understand; therefore, we highly encourage you read up on it from multiple sources, and really gain a good understanding of it.

Here is an example of `fork`:
```
int pid = fork();
if (pid == -1)
{
   perror("fork");
   exit(1);
}
else if(pid == 0)//when pid is 0 you are in the child process
{
   cout<<"This is the child process ";
   exit(1);  //when the child process finishes doing what we want it to, 
             //cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   if( -1 == wait(0)) //wait for the child process to finish executing, wait will be explained later on
   perror(“There was an error with wait().”);
}
```

Here we’re setting `pid`, which is an `int`, to the return value of `fork`. This works even though the declaration returns `pid_t`, because `pid_t` is basically an integer, but is defined this way to work across systems and conform to older systems that use `short` or some other data type. If fork returns 0, that means that we are in the child process. Otherwise, if fork returns a non-zero (not including -1, which you must error check), `fork` returned the pid of the child process and we are therefore in the parent. So, as we can see, the first `else if` statement will only be executed by the child process and the second will only be executed by the parent. You have to have the `exit()` statement when you’re done executing everything you want to in the child. If the exit statement isn't present, the child will continue executing through the rest of the code, which is likely intended for the parent. This may cause unforeseen errors and in the case of a shell where we run in a loop, the child will become a zombie process - that is, it will not exit, and continue to run, taking up memory and hampering the program's performance; essentially running two concurrent shells - and we don't want that do we?

Of course, with a child, there must be a parent. In this particular example, the parent simply waits for the child process to finish running (because of the wait call, which will be explained later), and executes after the child process is finished.

Also, when using `fork` it is good practice to create clearly written if statements to completely separate what the child and parent process will do. If you do not, it will become hard to tell what your child and parent are executing and finding errors will become difficult. Below is an example of this good practice:
```
int pid = fork();
if (pid == -1)
{
    perror("fork"); //syscall to output error
    exit(1);
}
else if (pid == 0) //if it is the child process running
{
    //do whatever the child should do
    return 0; //always end the child process after its done
}
else //we are in the parent
{
    if (-1 == wait(0))      //error checking, `wait` should almost always be used
    {                       //in the parent immediately following `fork`
        perror("wait");
        exit(1);
    }
}
//you can do whatever the parent function needs to do here
```

##wait:

**includes:** `#include <sys/types.h>`
          `#include <sys/wait.h>`

**declaration:** `pid_t wait(int *status);`
            `pid_t waitpid(pid_t pid, int *status, int options);`
            `int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);`

**returns:** When an error occurs -1 is returned otherwise it returns the pid of the child that was killed.

[man page](http://linux.die.net/man/2/wait)

`wait`, and associated calls `waitpid` and `waitid`, are system calls used by the parent process to wait for a change in state by a child. It also obtains information about the child exit status upon return.

`wait` is commonly used along with the `fork` function (and is pretty much a necessity). `wait` is used in the parent process, causing it to stop at the line that calls `wait` until the child process finishes executing. This prevents two processes from running at once. Not using `wait` may create errors because otherwise, the child may not necessarily end before the parent creating zombie or, in this specific case, orphaned processes. It may also cause race conditions where it is uncertain which program will be faster in executing and can cause errors based on the order code is executed in. If you want two processes to run at once, you should not use `wait` but again this can cause unforeseen errors and in the end, you still need to use `wait` or something similar to reap the child.

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
   exit(1);  //when the child process finishes doing what we want it to,
             //cout, we want to kill the child process so it doesn’t go on in the program so we exit
}
//if pid is not 0 then we’re in the parent
else if(pid > 0) //parent function
{
   if( -1 == wait(0)) //wait for the child process to finish executing
   perror(“There was an error with wait().”);
}
```

Other than just `wait`, there are two other system calls that will also reap zombie processes, `waitpid` and `waitid`. The advantages of using `waitpid` or `waitid` over simply `wait`, is that wait will only stop the parent process until one of the children ends; it will not wait for any specific child or multiple ones. `waitpid` and `waitid` can wait for specific processes to end, either by its pid or its process group ID, and they can also wait for any child.

The differences between `waitpid` and `waitid` are that `waitid` requires the first parameter, `idtype_t idtype` to specify what kind of data is in the second parameter, `id_t id` (a pid, a process group id, or just any child). `waitpid` will automatically tell based on what you pass into its first parameter (numbers `-1`, `0`, `1` have special meanings when passed in, but you could also put in a pid). All `wait` system calls can tell you the exit status of the child, the parameter `int *status` is used to store the child's exit code. `waitid` does not take an `int *`, but instead a `siginfo_t` struct that will give even more information on the exit status of the child. These returned errors are useful for finding out whether or not your child process ended with an error, as, if it did, `wait` will still succeed even though you likely want to output some sort of message. However, you normally do not need the amount of information given to you by `waitid` to see whether this happened. `waitpid` and `waitid` also have the last parameter `int options`. This is a flag to designate what kind of status change in the child the parent should wait for. You can bitwise or option flags together, `|`, to indicate to wait for any of multiple changes. The option flag marcos can be found on the man page.

Some examples of `wait` variations:
```
int status;
wait(&status); //status will now contain the exit code of the child
              //if it exited normally it should be 0
waitpid(child_pid, &status, 0); //will wait for any change in the process
                               //whose pid is child_pid
waitpid(-1, &status, 0); //same as wait(&status), -1 means wait for any child
                         //process
struct siginfo_t info;
waitid(P_PID, child_pid, &info, WNOHANG | WUNTRACED);
//wait for process whose pid is child_pid and return immediately if no child
//process has ended or if child has stopped
```

An example of when you would want to use `waitpid` or `waitid`:
```
int child_one = fork();
if (child_one == -1)
{
    perror("fork");
    exit(1);
}
else if (child_one == 0)
{
    //do whatever the first child should do
    return 0;
}

//we are in the parent
int child_two = fork();
if (child_two == -1)
{
    perror("fork");
    exit(1);
}
else if (child_two == 0)
{
    //do child two things
    return 0;
}

//in the parent again
waitpid(child_two, NULL, 0); //we want to wait specifically for child two
                             //and not child one
//perhaps we needed to do something with the exit status of child two
//and based on it potentially do something else with the first child
waitpid(child_one, NULL ,0); //now wait for child_one to make sure we reap it
```

Macros used can be found on the man page.

##exec:

**includes:** `#include <unistd.h>`

**declaration:** (multiple declarations depending on which `exec` function is used)

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
        perror(“There was an error with wait(). ");
}
```

(Again, we’re using `perror` to check for errors. PLEASE remember to do so as well!)

The parameters for `execvp` are: `const char *file, char *const argv[]`. In this example, `file` is `argv[0]` and `argv` is `argv[]`. `argv`, in this example, is a char pointer pointer containing the user input of what commands they wish to execute.

For example, the user can input `ls -l -a` and `argv[0] = ls`, `argv[1]= -l`, `argv[2]= -a`. So essentially, `argv[0]` is the command, while everything after is the flag.

As we told you above, `execvp` finds the path for you. If you wanted to use `execv` you would have to add the path to the front of the command, for example if you input `ls` the program would change it to `/usr/bin/ls` for the `execv` call.

