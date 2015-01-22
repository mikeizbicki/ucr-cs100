Video Tutorial on System Calls
==============================
Here, we have video tutorials for a few select system calls which we found difficult to visualize. Before watching these videos, please make sure you have gone over the [syscall_guide](../../textbook/assignment-help/syscalls) text tutorial. 

##fork()
In this video, we illustrate the basics of `fork()`. We demonstrate how `fork()` creates multiple processes that are identified by a pid, how fork returns an integer from each process to help identify if it is the child or parent, how changes or actions in the child do not carry over into the parent, and how zombie processes may be created and prevented.

[![fork() Video](http://i.imgur.com/3hRxF4x.jpg)](https://www.youtube.com/watch?v=xVSPv-9x3gk)

##Directory Streams
In this video, we illustrate the basics of several system calls that deal with directory streams, namely `opendir()`, `readdir()`, and `close()`. Along with these system calls, we touch on the dirent structure and how we can use it to access file attributes. 

[![Directory Stream Video](http://i.imgur.com/U7s7bwA.jpg)](https://www.youtube.com/watch?v=ru3uxfknAMc)

##dup(), dup2(), and File Descriptors
In this video, we illustrate the basics of `dup()` and `dup2()` and how you can use these system calls to modify the file descriptors of your system. Modifying these file descriptors will allow us to change the direction of input and output of our program (e.g: instead of having our program read stdin from the terminal, we can have our program read stdin from our file, instead).

[![dup(), dup2(), and File Descriptors](http://i.imgur.com/W21y1zM.jpg)](https://www.youtube.com/watch?v=EqndHT606Tw)

##pipes()
In this video, we illustrate the basics of `pipe()` and how you can use it to allow multiple processes or programs to communicate with each other. `Pipe()` takes in an int array of size two, and the indices of this array will act as each end of our pipe. It is now possible to disconnect stdin and stdout from the terminal and reconnect (stdin and stdout) with the ends of the pipe to allow communications between different processes. 

[![pipe() Video](http://i.imgur.com/TeHSXo9.jpg)](https://www.youtube.com/watch?v=uHH7nHkgZ4w)

