#strace Tutorial

###What is strace?
strace is a debugging tool that helps you trace the system calls of an executable.

###Using strace
Let's first run strace without any flags to see what the output will typically look like.

We'll use this example code:

```
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int main() {
	int pid = fork();

	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	else if(pid == 0) {
		cout << "Hello, I am a child!" << endl;
		exit(1);
	}
	else {
		if(wait(0) == -1) {
			perror("wait");
			exit(1);
		}
		cout << "Hello, I am a parent!" << endl;
	}

	cout << endl;
	return 0;
}
```

In the terminal, run strace with this command:

```
$ g++ example1.cpp -o example1.out
$ strace example1.out
```

Your output should look something like this:

```
execve("./example1.out", ["example1.out"], [/* 16 vars */]) = 0
brk(0)                                  = 0xf2ce000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x2ab8b2f85000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x2ab8b2f86000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY)      = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=198546, ...}) = 0
mmap(NULL, 198546, PROT_READ, MAP_PRIVATE, 3, 0) = 0x2ab8b2f87000
close(3)                                = 0
open("/usr/lib64/libstdc++.so.6", O_RDONLY) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000\364$]:\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=976312, ...}) = 0
mmap(0x3a5d200000, 3145600, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3a5d200000
mprotect(0x3a5d2e6000, 2093056, PROT_NONE) = 0
mmap(0x3a5d4e5000, 36864, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe5000) = 0x3a5d4e5000
mmap(0x3a5d4ee000, 73600, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x3a5d4ee000
close(3)                                = 0
open("/lib64/libm.so.6", O_RDONLY)      = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`>\240W:\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=614992, ...}) = 0
mmap(0x3a57a00000, 2629816, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3a57a00000
mprotect(0x3a57a82000, 2093056, PROT_NONE) = 0
mmap(0x3a57c81000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x81000) = 0x3a57c81000
close(3)                                = 0
open("/lib64/libgcc_s.so.1", O_RDONLY)  = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\36 \\:\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=58400, ...}) = 0
mmap(0x3a5c200000, 2151784, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3a5c200000
mprotect(0x3a5c20d000, 2097152, PROT_NONE) = 0
mmap(0x3a5c40d000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xd000) = 0x3a5c40d000
close(3)                                = 0
open("/lib64/libc.so.6", O_RDONLY)      = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\360\332aW:\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1726296, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x2ab8b2fb8000
mmap(0x3a57600000, 3506520, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3a57600000
mprotect(0x3a5774f000, 2097152, PROT_NONE) = 0
mmap(0x3a5794f000, 20480, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x14f000) = 0x3a5794f000
mmap(0x3a57954000, 16728, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x3a57954000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x2ab8b2fb9000
arch_prctl(ARCH_SET_FS, 0x2ab8b2fb9710) = 0
mprotect(0x3a5794f000, 16384, PROT_READ) = 0
mprotect(0x3a57c81000, 4096, PROT_READ) = 0
mprotect(0x3a5d4e5000, 24576, PROT_READ) = 0
mprotect(0x3a5741c000, 4096, PROT_READ) = 0
munmap(0x2ab8b2f87000, 198546)          = 0
clone(child_stack=0, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x2ab8b2fb97a0) = 30940
wait4(-1, Hello, I am a child!
NULL, 0, NULL)                = 30940
--- SIGCHLD (Child exited) @ 0 (0) ---
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 10), ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x2ab8b2f87000
write(1, "Hello, I am a parent!\n", 22Hello, I am a parent!
) = 22
write(1, "\n", 1
)                       = 1
exit_group(0)                           = ?
```

WHOA what's going on? Looks like a lot, right? Don't worry, it's not as complicated as it seems.
We normally won't need to pay attention to the stuff between `execvp` and the system call we're looking for (which in this case, is `write`). We will ignore these lines, since we won't be using them to debug our code.

Let's take the line with `write`, for example:

```
write(1, "Hello, I am a parent\n", 22Hello, I am a parent!
)   = 22
```

The trace starts off by printing the system call with its passed-in arguments, followed by the return value of the system call itself.

The first parameter into `write` is `1` (one), which represents the file descriptor for `stdout`. The second parameter is something we recognize -- our string `"Hello, I am a parent!\n"`. The third parameter is `22Hello, I am a parent!`. The 22 stands for the size of the string. The return value following the `=` (`)   = 22`) is also the size of the string, which is 22.

###Using strace with flags

The output of strace alone may seem hard-to-read when looking for something specific. strace is able to trace a specific system call with the `-e` flag.

Let's trace the system call `write` in our example code:

```
$ strace -e write example1.out
```

This is what the output should look like:

```
Hello, I am a child!
--- SIGCHLD (Child exited) @ 0 (0) ---
write(1, "Hello, I am a parent!\n", 22Hello, I am a parent!
) = 22
write(1, "\n", 1
)                       = 1
```

There! That looks much more simple and straight to the point. If you want to look at multiple specific system calls, you separate each of them with a comma (no spaces!), like so:

```
$ strace -e write,read example1.out
```

This is the output we get:

```
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000\364$]:\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0`>\240W:\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\36 \\:\0\0\0"..., 832) = 832
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\360\332aW:\0\0\0"..., 832) = 832
Hello, I am a child!
--- SIGCHLD (Child exited) @ 0 (0) ---
write(1, "Hello, I am a parent!\n", 22Hello, I am a parent!
) = 22
write(1, "\n", 1
)                       = 1
```

Notice that the `read` system calls are listed before the `write` system calls. The order of which you pass in the values (`write` and `read`) does not affect the output. This is because when the program is executed, `read` happens to be called before `write`.

What if we want to count how many times our system calls are called? We accomplish this with the `-c` flag.

In the terminal, run strace with the `-c` flag:

```
$ strace -c example1.out
```

Your output should look something like this:

```
Hello, I am a child!
Hello, I am a parent!

% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
   nan    0.000000           0         4           read
   nan    0.000000           0         2           write
   nan    0.000000           0         5           open
   nan    0.000000           0         5           close
   nan    0.000000           0         6           fstat
   nan    0.000000           0        16           mmap
   nan    0.000000           0         8           mprotect
   nan    0.000000           0         1           munmap
   nan    0.000000           0         1           brk
   nan    0.000000           0         1         1 access
   nan    0.000000           0         1           clone
   nan    0.000000           0         1           execve
   nan    0.000000           0         1           wait4
   nan    0.000000           0         1           arch_prctl
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                    53         1 total
```

If you notice any of the system calls taking a longer-than-usual amount of time to run, it may be the source of unwanted behavior.


We will next demonstrate how to isolate problems using strace.

###Using strace to find errors
