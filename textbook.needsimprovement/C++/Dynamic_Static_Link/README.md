#Dynamic and static linking

Linking is a process of combining multiple [object files](http://en.wikipedia.org/wiki/Object_file) into a single [executable file](http://en.wikipedia.org/wiki/Executable).
Linking is performed by programs called [linkers](http://en.wikipedia.org/wiki/Linker_(computing)) (also named link editors).

**Definition of static link:**

[Static linking](https://kb.iu.edu/d/akqn) is the process of copying all libraries that are used in the program into the final executable file. The actual linking takes place at the last step of compile process. 
```
 $ gcc -o static-executable-name src_file.c libctest.a
```
[Static libraries](http://en.wikipedia.org/wiki/Static_library) end with `.a`.
([reference](http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html))

**Definition of dynamic link:**

[Dynamic linking](https://kb.iu.edu/d/akqn) is the process of placing the names of all [shared libraries](http://cs-fundamentals.com/c-programming/static-and-dynamic-linking-in-c.php#create-and use-shared-libraries) (also called dynamic linked library) in the final executable file. The actual linking takes place at run time.
```
 $ gcc -o dynamic-executable-name src_file.c libctest.so
```
Shared libraries end with `.so`.
([reference](http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html))

## Examples of Using Dynamic Link and Static Link
**How to create a static link library:**

create a header file basemath.h
```
 int add(int, int);
 int sub(int, int);
```

 create a source file add.c
```
 int add(int num1, int num2)
 {
     return (num1 + num2);
 }
```

 create another source file sub.c

 create a source code file main.c
```
 #include "basemath.h"
 #include <stdio.h>
 int main()
 {
     int x = 10;
     int y = 20;
     printf("\n%d + %d = %d", x, y, add(x, y));
     printf("\n%d + %d = %d", x, y, sub(x, y));
     return 0;
 }
```

 compile add.c to create the object file add.o
```
 $ gcc -c add.c
```

 compile sub.c to create the object file sub.o

 create a static library basemath.a by using add.o and sub.o
```
 $ ar rs basemath.a add.o sub.o
```
 *[ar](http://linux.die.net/man/1/ar): create, modify, and extract from archive* 
     
 *`rs`: flags of `ar`*

 compile main.c to create the object file main.o
```
 $ gcc -c main.c
```

 link main.o with static library basemath.a to create the final executable file main_st
```
 $ gcc -o main_st main.o basemath.a
```

 display all the files in the current folder
```
 $ ls
```
 after the first section, you should have all the files listed below:
```
 add.c  add.o  basemath.a  basemath.h  main.c  main.o  main_st  sub.c  sub.o
```

**How to create a dynamic link library(also called shared library):**

 remove all the object files(.o files) first
```
 $ rm *.o
```

 compile add.c to create the object file add.o by using [-fPIC](http://stackoverflow.com/questions/5311515/gcc-fpic-option) flag
```
 $ gcc -fPIC -c add.c
```
*`-fPIC` option enables [position independent code](http://en.wikipedia.org/wiki/Position-independent_code) generation, a requirement for shared library. `-fpic` is similar as `-fPIC` that can be used. However, the difference is that: `-fPIC` works for all situations; `-fpic` only works for some situations.*

 compile sub.c to create the object file add.o by using -fPIC flag

 create a dynamic link library basemath.so from add.o sub.o
```
 $ gcc -shared -o basemath.so add.o sub.o
```
*[-shared](https://gcc.gnu.org/onlinedocs/gcc-4.9.2/gcc/Link-Options.html): Produce a shared object which can be linked with other objects to form an executable.*

 install the dynamic link library by copying the library into one of the standard directories( /usr/lib and /lib)
```
 $ sudo cp basemath.so /usr/lib
```
*[sudo](http://linux.die.net/man/8/sudo) allows a permitted user to execute a command as the superuser or another user, as specified by the security policy.*

 run [ldconfig](http://linux.die.net/man/8/ldconfig) to create the necessary links to the most recent libraries found in the standard directories( /usr/lib and /lib) specified on the command line
```
 $ sudo ldconfig
```

 create main.o again because we remove it in the beginning of this section

 link main.o with dynamic library basemath.so to create the final executable file main_dy
```
 $ gcc -o main_dy main.o basemath.so
```

 display all the files in the current folder
```
 $ ls
```

 now you will have all the files listed below
```
 add.c  add.o  basemath.a  basemath.h  basemath.so  main.c  main_dy  main.o  main_st  sub.c  sub.o
```

## Run both Static and Dynamic Linked Final Executable File
In this section, we have three parts. First part, we run `./main_st` and `./main_dy` to check the output. Second part, we change our basemath.a and basemath.so file, then run `./main_st` and `./main_dy` again to compare the new output with the first part's output. Third part, we remove both basemath.a and basemath.so file, then run `./main_st` and `./main_dy` again.

**Run `./main_st` and `./main_dy` without changing the library**
```
 $ ./main_st

 10 + 20 = 30
 10 - 20 = -10
 
 $ ./main_dy

 10 + 20 = 30
 10 - 20 = -10
```
At this point, you can see the outputs of both `./main_st` and `./main_dy` are same.

**Now let's modify the libraries basemath.a and basemath.so**
    
modify add.c
```
 int add(int num1, int num2)
 {
     return 2*(num1 + num2);
 }
```

redo following steps
```
 $ # regenerate static link library
 $ rm *.o
 $ gcc -c add.c
 $ gcc -c sub.c
 $ ar rs basemath.a add.o sub.o
 $ # regenerate dynamic link library
 $ rm *.o
 $ gcc -c -fPIC add.c
 $ gcc -c -fPIC sub.c
 $ gcc -shared -o basemath.so add.o sub.o
 $ sudo cp basemath.so /usr/lib
 $ sudo ldconfig
```

**Run `./main_st` and `./main_dy` again**
```
 $ ./main_st

 10 + 20 = 30
 10 - 20 = -10
 
 $ ./main_dy

 10 + 20 = 60
 10 - 20 = -10

```
Now you can see the difference between the two programs. `./main_dy`'s output changes because `./main_dy` always links to the latest dynamic link library at run time. By contrast, `./main_st`'s output doesn't change because `./main_st` includes the static library at the last step of compiling.

**Remove both basemath.a and basemath.so libraries**
```
 $ rm basemath.a basemath.so
 $ sudo rm /usr/lib/basemath.so
```

**Run `./main_st` and `./main_dy` the third time**
```
 $ ./main_st

 10 + 20 = 30
 10 - 20 = -10
 
 $ ./main_dy
 ./main_dy: error while loading shared libraries: basemath.so: cannot 
 open shared object file: No such file or directory
```
After removing both libraries (basemath.a and basemath.so), `./main_st`, which uses static link, can still run because basemath.a is contained in `./main_st`. However, `./main_dy`, the one using dynamic link, gives an error message because it cannot find its shared library.

## Differences between Dynamic Link and Static Link
**Advantage of dynamic link:**

Program can **share identical code** instead of owning individual copies of the same library; as a result, the size of the program is relatively smaller when using dynamic link. When a new version of a shared library is released, it **automatically replaces its old version**. In other words, when user runs a program, the program always automatically uses the newest version of the shared library. As a result, User does not need to recompile the program if the shared library gets updated.

**Disadvantage of dynamic link:**

Dynamic link has a **run-time loading cost** because all the names of the files in shared library need to be connected to the actual file at the run time. In Windows, suppose that there is a program A uses shared library (dll) V2.0. When you install a program B that requires the same library with V1.0, you may find program A stops working because the V2.0 dll has been overwritten with V1.0. This is called [DLL HELL](http://en.wikipedia.org/wiki/DLL_Hell). Recent versions of windows are capable of storing multiple versions of a dll, and supplying the correct one on request.

**Advantage of static link:**

Do not need to carry along a copy of the library that is being used. There is **no additional run-time loading time costs** since the static library get complied into the final executable file at the compile time.

**Disadvantage of static link:**

The size of program is relatively bigger when the program uses static link instead of using dynamic link. Every time when the static library gets updated, the whole program needs to get recompiled in order to install the update.

[This is a stackoverflow link that contains very good examples about the differences between dynamic and static link.](http://stackoverflow.com/questions/140061/when-to-use-dynamic-vs-static-libraries)
