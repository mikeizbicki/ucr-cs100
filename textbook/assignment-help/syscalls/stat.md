#Getting file information via the Stat system call

So you want to learn how to utilize the Stat syscall?
Very well, let us start by understanding its general purpose.
As we know, one of the many wonderful "doo-dads" of the Linux Terminal is that it allows us to operate inside a director.
Inside of such a directory there can exist all sorts of different files; and sometimes we might want to access certain specific information about one (or more) of those files from inside a program of ours.
With the Stat system call, we can perform exactly that kind of information retrieval and harness it for use inside of our program!

There are two useful ways to perform the Stat system call:

1. stat
2. fstat

The difference between the two lies in what parameters we will pass into their respective system calls.
Now, let's look at their function calls as well as the role each parameter and return value plays in it.
