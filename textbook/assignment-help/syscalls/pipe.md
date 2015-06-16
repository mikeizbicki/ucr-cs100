#Pipe System Call
Documentation on the pipe. This call is used to create a data path in which communication between processes can occur. There are `pipe()` and `pipe2()` sys calls.

##Pipe
###Inclusion
`#include <fcntl.h>`

`#include <unistd.h>`

###Declaration
`int pipe(int pipefd[2]);`

###Return Value
Returns 0 on success. If an error occurs, -1 is returned and errno is set.

##Pipe2
Contains identical includes and return values. The key difference is that pipe2 has an extra parameter, int flags that affect the behaviour of the call.

`int pipe2(int pipefd[2], int flags);`

If flags are set to 0, pipe2 behaves exactly like pipe.

O_NONBLOCK flag saves extra calss to fcntl to produce the same result...

O_CLOEXEC flag sets the close-on-exec flag to the file descriptors...


The array pipefd[2] returns 2 file descriptors linking the ends of the pipe, or data path.

pipefd[0] is the read end

pipefd[1] is the write end

Pipe is a key call in performing any operations where multiple processes need to communicate with each other.

###Example:
Declaration of pipefd array and necessary variables and checking the proper amount of arguments.

```
pipefd[2];
pid_t child;
char buf;

if(argc != 2) {
	fprintf(stderr, "Usage: %s <string>\n", argv[0]);
	exit(1);
}
```

Establishes the pipe, aka data tunnel

```
if(pipe(pipefd) == -1) {		// Creates and error checks the pipe
	perror("pipe");	
	exit(1);
}
```

Pipes are used to communicate through processes, so here the child process to which we will communicate is forked.

```
child = fork();
if(child == -1) {
	perror("fork");
	exit(1);
}
```

In the child, the write end of the pipe is closed because we are only reading on this side.

```
if(child == 0) {
	close(pipefd[1];		// Closes unused write end

	while(read(pipefd[0], &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);

	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}
```

The function then reads from the read end of the pipe and outputs to standard out as long as the data is does not cause an error in read.


```
else {
	close(pipefd[0]);
	write(pipefd[1], argv[1], strlen(argv[1]));
	close(pipefd[1]);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
```

Back in the parent, the read end of the pipe is closed because the parent is writing to the child.

The write function sends the command line argument array `argv[1]` and the length through the pipe.

Lastly, the write end of the pipe is closed, the child is waited for, and the function exits with a success status.
