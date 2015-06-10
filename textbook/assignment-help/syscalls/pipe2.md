#Pipe System Call
Documentation on the pipe. This call is used to create a data path in which communication between processes can occur. There are `pipe()` and `pipe2()` sys calls.

##Pipe2
Contains identical includes and return values. The key difference is that pipe2 has an extra parameter, int flags that affect the behaviour of the call.

`int pipe2(int pipefd[2], int flags);`

If flags are set to 0, pipe2 behaves exactly like pipe.

O_NONBLOCK flag saves extra calss to fcntl to produce the same result...

O_CLOEXEC flag sets the close-on-exec flag to the file descriptors...


The array pipefd[2] returns 2 file descriptors linking the ends of the pipe, or data path. pipefd[0] is the read end and pipefd[1] is the write end. When data is written to pipefd[1] the pipe is buffered by the kernel until the data is read from pipefd[0] signalling the data has successfully moved throough the pipe.

Pipe is a key call in performing any operations where multiple processes need to communicate with each other. This is essential for I/O redirection. A basic operation, shown in the man pipe page, to provide rough understanding is the output to standard out in the child process from data in the parent.

###Example:

The steps are setting up the pipefd[2] array, getting the data to output, creating the pipe, creating the child process, closing unused ends, reading data from one to end to the other for output, and lastly closing the pipe and child.

```
pipefd[2];
pid_t child;
char buf;

if(argc != 2) {
	fprintf(stderr, "Usage: %s <string>\n", argv[0]);
	exit(1);
}

if(pipe(pipefd) == -1) {		// Creates and error checks the pipe
	perror("pipe");	
	exit(1);
}

child = fork();
if(child == -1) {
	perror("fork");
	exit(1);
}

if(child == 0) {
	close(pipefd[1];		// Closes unused write end

	while(read(pipefd[0], &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);

	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

else {
	close(pipefd[0]);
	write(pipefd[1], argv[1], strlen(argv[1]));
	close(pipefd[1]);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
```

You can see in the example that once the pipe is created the fork creates the child there is a duplicate of the pipe, cloned to the child. Depending on the operation to occur an end of the pipe is closed in the child since the communication happens one direction at a time. Once the pipe connection is established between the processes, data transfer can occur by writing to pipefd[1] and waiting for the buffer or reading from pipefd[0].

This precedent is the same basis for redirection. For example, output redirection to a file. The function is executed normally in its process with some form of `exec`. The output of the function is them written to pipefd[1] instead of standard output. The read end, pipefd[0] is then used to fill the content of an opened file in another process, thus linking the processes by thefile descriptor data path.
