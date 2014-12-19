###Automatic Segfault Detection

In this example, compile `segfault.cpp` and run it through `gdb` with the following command

```
$ g++ -g segfault.cpp
$ gdb a.out
```
Once you have started up `gdb` with `a.out`, run `gdb` with the `run` command


```
(gdb) run
Starting program: /class/classes/dgoer001/hw4/ex1 

Program received signal SIGSEGV, Segmentation fault.
0x00000000004007ae in main () at ex1.cpp:10
10		*pointer = number;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.
x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
```

The great thing about `gdb` is that it can automatically locate segfaults.

As you can see, `gdb` has found a segfault in `segfault.cpp`at `line 10`

To fix it, change `line 10` to be the following.

```
    pointer = &number;
```

The new code for `segfault.cpp` will now look like

```
#include <iostream>
using namespace std;
int main()
{
    int *pointer = NULL;
    int number = 0;
    pointer = &number;
    // proper output should be 0
    cout << *pointer << endl;
    return 0;
}
```
`gdb` will run the new `segfault.cpp` with no problem.
```
(gdb) run
Starting program: /class/classes/dgoer001/gdb/src/a.out 
0
[Inferior 1 (process 35008) exited normally]
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64

```

As you can see, `gdb`was able to point out the location of the segfault, therefore making the debugging process a lot easier.
