# timing io operations

You should complete this lab using pair programming with a new partner.

### coding instructions

In this lab, you will implement a version of the `cp` command line program that copies files from one location to another.  You will use three different methods for copying the files and compare their performance.  The methods are:

1. Use the [`std::istream::get`](http://www.cplusplus.com/reference/istream/istream/get/) and [`std::ostream::put`](http://www.cplusplus.com/reference/ostream/ostream/put/) C++ functions to copy the input file to the output file one character at a time.

2. Use the Unix system calls `read()` and `write()` to copy the input file to the output file one character at a time.
  
3. Use the Unix system calls `read()` and `write()` to copy the input file to the output file one buffer at a time.  The buffer should be of size `BUFSIZ`, which is declared in the `stdio.h` include file.

Your final program should have two required arguments (the input and output file) and one optional argument.  If the optional argument is not given, then copy the files using the most efficient of the three methods above.  

If the optional argument is given, then your program will copy the file using each of the three methods, time how long each method takes, and report the results to stdout.  You must show wallclock, user, and system run times. You may use the given `Timer.h` file to measure the run times.  

In order to determine which method is fastest, you'll need to test them on a large file.  Otherwise, the performance differences will not be noticeable.  The file `/usr/share/dict/linux.words` should be sufficiently large.

**IMPORTANT:** If the file you are copying to already exists, your program must print an error.  The built-in `cp` will check to see if the second file is a directory.  If it is, then `cp` will copy the file into the directory. You do NOT have to implement this feature.

**IMPORTANT:** The built-in `cp` program can support copying entire directories using the `-r` flag.  You do not need to implement this feature.  You should simply print an error message if the first argument is a directory.

### deliverables

The deliverables for this lab are more complicated than for previous labs.  We want your `cp` program added to your `rshell` project on github.  Source code should go in the `src` folder, and the `Makefile` needs to be modified to build the `cp` program and put it in the `bin` folder.  This is the same setup we had for the `ls` command you wrote for homework. 

There is one catch though: you are not allowed to commit the code to your own repository.  Your partner must fork your repo, commit the code, and issue a pull request making all the changes.  I want you to get practice contributing to other people's open source projects and having other people contribute to your own projects.

##additional resources
Read the man pages on `open()`, `read()`, `write()`, and `close()` for further information on manipulating file descriptors and buffers.

Here is a complete list of resources created by previous cs100 students that might help with this lab:

* [Syscalls on file descriptors](../../../textbook/assignment-help/syscalls/fd.md)
* [Bitwise Operators](../../../textbook/assignment-help/bitwise-ops/README.md)
