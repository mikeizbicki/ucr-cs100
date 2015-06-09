#strace Tutorial

###What is strace?
`strace` is a debugging tool that lists and organizes the system calls an executable uses.

###Using strace
Let's first run `strace` on [example1.cpp](example1.cpp) without any flags to see what the output will typically look like.
All of our example code in this tutorial are included here in this directory.

In the terminal, run `strace` with this command:

```
$ g++ example1.cpp -o example1.out
$ strace example1.out
```

In particular, we will be looking at these lines of code:

```
cout << "Hello, I am a child!" << endl;

...
...
...

cout << "Hello, I am a parent!" << endl;
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

WHOA what's going on?
Looks like a lot, right?
Don't worry, it's not as complicated as it seems.
We normally won't need to pay attention to the stuff between `execvp` and the system call we're looking for (which in this case, is `write`).
We will ignore these lines, since we won't be using them to debug our code.

Let's take the line with `write`, for example:

```
write(1, "Hello, I am a parent\n", 22Hello, I am a parent!
)   = 22
```

`strace` starts off by printing the system call with its passed-in arguments, followed by the return value of the system call itself.

The first parameter into `write` is `1` (one), which represents the file descriptor for `stdout`.
The second parameter is something we recognize---our string `"Hello, I am a parent!\n"`.
The third parameter is `22Hello, I am a parent!
`.
The 22 stands for the size of the string, and is followed by what the output of the string would look like.
The return value following the `=` (`)   = 22`) is also the size of the string, which is 22.

###Using strace with flags

The output of `strace` alone may seem hard-to-read when looking for something specific.
`strace` is able to trace a specific system call with the `-e` flag.
This flag directs `strace` to follow "every" usage of any system calls you pass in.

Let's `strace` the system call `write` in our example code:

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

There!
That looks much more simple and straight to the point.
If you want to look at multiple specific system calls, you separate each of them with a comma (no spaces!), like so:

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

Notice that the `read` system calls are listed before the `write` system calls.
The order of which you pass in the values (`write` and `read`) does not affect the output.
This is because when the program is executed, `read` happens to be called before `write`.

What if we want to count how many times our system calls are used?
We accomplish "counting" with the `-c` flag.

In the terminal, run `strace` with the `-c` flag:

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

To look further into how long each usage of a system call is taking, we will calculate the "relative time" between each successive call using the `-r` flag:

```
$ strace -r example1.out
```

The output we get is:

```
     0.000000 execve("./example1.out", ["example1.out"], [/* 36 vars */]) = 0
     0.000937 brk(0)                    = 0x137f000
     0.000082 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe029ad7000
     0.000067 access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
     0.000081 open("/etc/ld.so.cache", O_RDONLY) = 3
     0.000058 fstat(3, {st_mode=S_IFREG|0644, st_size=97493, ...}) = 0
     0.000067 mmap(NULL, 97493, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fe029abf000
     0.000077 close(3)                  = 0
     0.000106 open("/usr/lib64/libstdc++.so.6", O_RDONLY) = 3
     0.000076 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\360c%[;\0\0\0"..., 832) = 832
     0.000073 fstat(3, {st_mode=S_IFREG|0755, st_size=989840, ...}) = 0
     0.000070 mmap(0x3b5b200000, 3166648, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3b5b200000
     0.000054 mprotect(0x3b5b2e8000, 2097152, PROT_NONE) = 0
     0.000055 mmap(0x3b5b4e8000, 36864, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe8000) = 0x3b5b4e8000
     0.000070 mmap(0x3b5b4f1000, 82360, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x3b5b4f1000
     0.000054 close(3)                  = 0
     0.000062 open("/lib64/libm.so.6", O_RDONLY) = 3
     0.000057 read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0p>\240S;\0\0\0"..., 832) = 832
     0.000063 fstat(3, {st_mode=S_IFREG|0755, st_size=599392, ...}) = 0
     0.000065 mmap(0x3b53a00000, 2633912, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3b53a00000
     0.000052 mprotect(0x3b53a83000, 2093056, PROT_NONE) = 0
     0.000079 mmap(0x3b53c82000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x82000) = 0x3b53c82000
     0.000117 close(3)                  = 0
     0.000062 open("/lib64/libgcc_s.so.1", O_RDONLY) = 3
     0.000059 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\20) Y;\0\0\0"..., 832) = 832
     0.000061 fstat(3, {st_mode=S_IFREG|0755, st_size=93320, ...}) = 0
     0.000065 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe029abe000
     0.000053 mmap(0x3b59200000, 2186584, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3b59200000
     0.000049 mprotect(0x3b59216000, 2093056, PROT_NONE) = 0
     0.000049 mmap(0x3b59415000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x15000) = 0x3b59415000
     0.000056 close(3)                  = 0
     0.000056 open("/lib64/libc.so.6", O_RDONLY) = 3
     0.000053 read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0p\356aS;\0\0\0"..., 832) = 832
     0.000054 fstat(3, {st_mode=S_IFREG|0755, st_size=1926760, ...}) = 0
     0.000061 mmap(0x3b53600000, 3750152, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x3b53600000
     0.000048 mprotect(0x3b5378a000, 2097152, PROT_NONE) = 0
     0.000048 mmap(0x3b5398a000, 20480, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x18a000) = 0x3b5398a000
     0.000058 mmap(0x3b5398f000, 18696, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x3b5398f000
     0.000094 close(3)                  = 0
     0.000081 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe029abd000
     0.000065 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe029abb000
     0.000060 arch_prctl(ARCH_SET_FS, 0x7fe029abb720) = 0
     0.000158 mprotect(0x3b5398a000, 16384, PROT_READ) = 0
     0.000068 mprotect(0x3b53c82000, 4096, PROT_READ) = 0
     0.000540 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe029aba000
     0.000138 mprotect(0x3b5b4e8000, 28672, PROT_READ) = 0
     0.000074 mprotect(0x3b5341f000, 4096, PROT_READ) = 0
     0.000050 munmap(0x7fe029abf000, 97493) = 0
     0.000218 clone(child_stack=0, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fe029abb9f0) = 13141
     0.000180 wait4(-1, Hello, I am a child!
NULL, 0, NULL)  = 13141
     0.000413 --- SIGCHLD (Child exited) @ 0 (0) ---
     0.000067 fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 1), ...}) = 0
     0.000107 mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fe029ad6000
     0.000096 write(1, "Hello, I am a parent!\n", 22Hello, I am a parent!
) = 22
     0.000068 write(1, "\n", 1
)         = 1
     0.000075 exit_group(0)             = ?
```

The execution time is printed before each system call line `<#.######>`. 
This can be useful in that you can distinguish between the same system calls, and pinpoint problems.
For example, let's say one `open` oddly takes much longer than the other `open`'s, which could help you find a starting point for debugging a program.


We will next demonstrate how to isolate problems using strace.

###Using strace to find errors

Let's try to use what we've learned so far to debug this really simple program: [main.cpp](main.cpp)! 

We compile the program and there are no errors.
Awesome.
But wait... when we run the program, `perror` tells us that something went wrong when the terminal tried to open the input file.

Since we know that the program is having problems with opening our file `data.dat`, let's use `strace -e open` to pinpoint the `open` system call.

```
$ strace -e open ./main.out
open("~/.c9/local/lib/tls/x86_64/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
open("/usr/lib/x86_64-linux-gnu/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
open("~/.c9/local/lib/tls/x86_64/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
open("~/.c9/local/lib/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
open("~/.c9/local/lib/tls/x86_64/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
open("data.dat", O_RDONLY)              = -1 ENOENT (No such file or directory)
Could not open input file.
+++ exited with 1 +++
```

If we look at the very last `open`, we see:

```
open("data.dat", O_RDONLY)              = -1 ENOENT (No such file or directory)
Could not open input file.
```

It turns out that the program couldn't open the file because there was no `data.dat` to begin with!
Let's say that we fix this by touching `data.dat`.
We run `./main.out`, and there are no more errors!

Even though the program works now, let's run `strace` again to see the difference:

```
$ strace -e open ./main.o
open("~/.c9/local/lib/tls/x86_64/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
open("/usr/lib/x86_64-linux-gnu/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
open("~/.c9/local/lib/tls/x86_64/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
open("~/.c9/local/lib/tls/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
open("~/.c9/local/lib/tls/x86_64/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/tls/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/x86_64/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("~/.c9/local/lib/libm.so.6", O_RDONLY|O_CLOEXEC) = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
open("data.dat", O_RDONLY)              = 3
open("output.dat", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 4
+++ exited with 0 +++
```

In this example, using `perror` is sufficient in finding the problem.
However, `perror` may not catch all of the problems in more complicated code, so this method is more useful in cases where `perror` may fail.

###Saving the output of strace

Say that we want to keep a record `strace`'s output.
An idea that comes to mind may be to use redirection in the terminal.
However, doing so would actually redirect the output of the executable instead of `strace`.

To correctly accomplish this task, all we need to do is run strace with the `-o` flag, followed by the name of the file to store the output in, and then the executable's name.

```
$ strace -o output.txt ./main.out
```

If the output file does not already exist, then it will be created.
If the file already exists, the contents of the file will be overwritten with the output of `strace`.

###So... why strace?

Because `strace` provides system call details, it is useful if a program is behaving unexpectedly (i.e. continually crashing, performance issues).
For instance, in the example in which we were trying to open a program that didn't exist, `strace` is also much easier to use than code debuggers and is useful to system administrators.
