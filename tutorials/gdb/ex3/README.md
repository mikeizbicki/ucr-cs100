###Example 3

From the `ex3` folder, compile `ex3.cpp` with the `-g` flag by using following command

```
$ g++ -g ex3.cpp
```


#####Finding Segfaults

Segfaults are caused by accessing memory that you do not have access to during the execution of the program. `gdb` is capable of automatically detecting segfaults. This is demonstrated by `gdb` with `ex3.cpp`. However, GDB cannot automatically locate all segfaults. If GDB does not find the segfault for you, use the `gdb` commands in the previous examples to help you locate the segfaults in your code.

```
(gdb) run
Starting program: /class/classes/dgoer001/hw4/ex3 

Program received signal SIGSEGV, Segmentation fault.
0x00000000004007ae in main () at ex3.cpp:10
10		*pointer = number;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.149.el6.
x86_64 libgcc-4.4.7-11.el6.x86_64 libstdc++-4.4.7-11.el6.x86_64
```

`gdb` found `segfault` at `line 10`

To fix it, change `line 10` to be the following.

```
    pointer = &number;
```

The new code for `ex3.cpp` will now look like

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
