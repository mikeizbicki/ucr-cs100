
Valgrind Tutorial
=================

What is Valgrind?
-----------------

Valgrind is a linux tool that helps you deal with debugging memory management issues. 

Valgrind has a function called Memcheck that will display the number of allocations and deallocations in bytes.

Checking for problems
---------------------


Let's start with a code example from the program example1.cpp:

```
    int main()
    {   
        char *var = new char[1024];
        return 0;
    }
```

In the code above, we can see that we have allocated some memory using the ```new``` operator.

You can run this program in Valgrind using the commands:

```
    $ g++ example1.cpp
    $ valgrind --tool=memcheck ./a.out
```
   
    
We get the following output:

```
    ==4090== Memcheck, a memory error detector
    ==4090== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==4090== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
    ==4090== Command: ./a.out
    ==4090== 
    ==4090==    
    ==4090== HEAP SUMMARY:  
    ==4090==     in use at exit: 1,024 bytes in 1 blocks
    ==4090==   total heap usage: 1 allocs, 0 frees, 1,024 bytes allocated
    ==4090== 
    ==4090== LEAK SUMMARY:
    ==4090==    definitely lost: 1,024 bytes in 1 blocks
    ==4090==    indirectly lost: 0 bytes in 0 blocks
    ==4090==      possibly lost: 0 bytes in 0 blocks
    ==4090==    still reachable: 0 bytes in 0 blocks
    ==4090==         suppressed: 0 bytes in 0 blocks
    ==4090== Rerun with --leak-check=full to see details of leaked memory
    ==4090== 
    ==4090== For counts of detected and suppressed errors, rerun with: -v
    ==4090== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


If we look at the line under ```HEAP SUMMARY```, we can see that there were still 1,024 bytes still in use when the program exited. These 1024 bytes come from when we allocated the memory for our ```char *```.

Also at the next line, we can see that there was 1 allocation and 0 deallocation. This 1 allocation comes from calling the ```new``` function and the 0 deallocations comes from not calling the ```delete``` function. This implies that there is a memory leak in our program.

We can also look at the ```LEAK SUMMARY``` to see if we can recover any leaked memory.

Looking at the line right below, we see that the 1,024 bytes lost are not recoverable.


### How to fix memory leaks


To obtain more information about where the memory leak may have occurred you can type the command:

```
    $ valgrind --tool=memcheck --leak-check=full ./a.out
```


The extra flag in this call will print out information about what function could be causing the leak and which function call is creating the possibility of the leak.

Between the ```HEAP SUMMARY``` and ```LEAK SUMMARY``` we will get the message:


```
    ==4102== 1,024 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==4102==    at 0x4C2B800: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==4102==    by 0x40071E: main (in /home/william/cs100/hw5/a.out)
```

We can see that in the third line, Valgrind says that the memory leak is cause by the function main and in the second line, Valgrind says the leak is caused by ```new[]```.
We can also see that all the memory that was not deallocated was definitely lost, meaning we cannot retrieve this memory.

This information will help you find where your leaks are at in your program.

     
### Fix all leaks and rerun


If we take our old program example1.cpp and add a ```delete``` right under the ```new``` statement, our problem should be fixed!

This is an important problem to fix because if you never free up your memory when you run programs, it could cause you to run out of memory in your computer. This is not a very good situation to be in.


```
    int main()
    {   
        char *var = new char[1024];
        delete [] var;
        return 0;
    }
```


Now if we recompile and run Valgrind with Memcheck we get:

```
    $ g++ example1.cpp
    $ valgrind --tool=memcheck ./a.out
```


```
    ==2284== Memcheck, a memory error detector
    ==2284== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==2284== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
    ==2284== Command: ./a.out
    ==2284== 
    ==2284== 
    ==2284== HEAP SUMMARY:
    ==2284==     in use at exit: 0 bytes in 0 blocks
    ==2284==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
    ==2284== 
    ==2284== All heap blocks were freed -- no leaks are possible
    ==2284== 
    ==2284== For counts of detected and suppressed errors, rerun with: -v
    ==2284== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

If we look at the ```HEAP SUMMARY``` section, we can see that our change worked and that for 1 allocation we have 1 free.

We just looked at a very simple example that only has 6 lines of code, of course there will be more complicated programs and now I will demonstrate Valgrind and Memcheck with a more complex program, example2.cpp.

Using Valgrind on a more difficult example
------------------------------------------


```
    #include <iostream>
    #include <cstring>
     
    using namespace std;
     
    void doSomething(char *ptr)
    {
        char *var2 = new char[1024]; // create a new char*
        strcpy(var2,ptr); // copy old char* into new char*
        cout << var2 << endl; // output new char*
        //delete [] var2;
    }
     
    int main()
    {   
        char *var = new char[1024]; //create char*
        string str = "hello world"; //create string to go into char*
        strcpy(var,str.c_str()); //copy string into char*
        cout << var << endl; // output char*
        doSomething(var); // call function with char*
        //delete [] var;
        return 0; 
    }  
```

This program listed above just creates a character string or cstring and copies the string "hello world" into it. Then the program outputs the cstring. Then it passes this cstring into a function which declares another cstring and copies the first cstring into the second one. Then the function prints out the cstring. The following is what is supposed to be output by this program

```
    hello world
    hello world
```

In our program above, we call the ```new``` operator twice and never call the ```delete``` operator. We call the first ```new``` operator in our ```main``` function and the second ```new``` in our function ```doSomething```. 

Now lets run our program with Valgrind and Memcheck:

```
    $ g++ example2.cpp
    $ valgrind --tool=memcheck ./a.out
```
We will get the following message:

```
    memory error detector
    ==3311== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==3311== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
    ==3311== Command: ./a.out
    ==3311== 
    hello world
    hello world
    ==3311== 
    ==3311== HEAP SUMMARY:
    ==3311==     in use at exit: 2,048 bytes in 2 blocks
    ==3311==   total heap usage: 3 allocs, 1 frees, 2,084 bytes allocated
    ==3311== 
    ==3311== LEAK SUMMARY:
    ==3311==    definitely lost: 2,048 bytes in 2 blocks
    ==3311==    indirectly lost: 0 bytes in 0 blocks
    ==3311==      possibly lost: 0 bytes in 0 blocks
    ==3311==    still reachable: 0 bytes in 0 blocks
    ==3311==         suppressed: 0 bytes in 0 blocks
    ==3311== Rerun with --leak-check=full to see details of leaked memory
    ==3311== 
    ==3311== For counts of detected and suppressed errors, rerun with: -v
    ==3311== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0))')
```


As we can see the program runs normal, printing out "hello world" twice under the ```Command: ./a.out``` line, but when we look at the ```HEAP SUMMARY``` we see that there were 3 allocations and 1 free. This means that we have a memory leak again.
 
If we look back at our program we can see that we used ```new``` but never called ```delete```.

As stated above ```delete``` is necessary to free up memory so that you don't run into memory issues later on.
 
To fix our problem we need to add in some deletes for the ```VAR``` pointer and the ```PTR``` pointer like such:

```
    #include <iostream>
    #include <cstring>
 
    using namespace std;

    void doSomething(char *ptr)
    {
        char *var2 = new char[1024]; // create a new char*
        strcpy(var2,ptr); // copy old char* into new char*
        cout << var2 << endl; // output new char*
        delete [] var2;
    }
    
    int main()
    {   
        char *var = new char[1024]; //create char*
        string str = "hello world"; //create string to go into char*
        strcpy(var,str.c_str()); //copy string into char*
        cout << var << endl; // output char*
        doSomething(var); // call function with char*
        delete [] var;
        return 0; 
    } 
```


And now when we put this through Valgrind, we should not have any memory leaks.

```
    $ g++ example2.cpp
    $ valgrind --tool=memcheck ./a.out
```

```
    ==3413== HEAP SUMMARY:
    ==3413==     in use at exit: 0 bytes in 0 blocks
    ==3413==   total heap usage: 3 allocs, 3 frees, 2,084 bytes allocated
    ==3413==
    ==3413== All heap blocks were freed -- no leaks are possible
    ==3413== 
    ==3413== For counts of detected and suppressed errors, rerun with: -v
    ==3413== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0))')
```

Now that we made those changes, we can see that there were 3 allocations and 3 frees, which fixes our memory leak problem.

One last example
----------------

While Valgrind can check if you have deallocated memory, it can also check if you have allocated it in the first place.

If we take our example2.cpp code and modify it slightly on the first line in ```main```:

```
    #include <iostream>
    #include <cstring>
 
    using namespace std;

    void doSomething(char *ptr)
    {
        char *var2 = new char[1024]; // create a new char*
        strcpy(var2,ptr); // copy old char* into new char*
        cout << var2 << endl; // output new char*
        delete [] var2;
    }
    
    int main()
    {   
        char *var;       //= new char[1024]; //create char*
        string str = "hello world"; //create string to go into char*
        strcpy(var,str.c_str()); //copy string into char*
        cout << var << endl; // output char*
        doSomething(var); // call function with char*
        delete [] var;
        return 0; 
    } 
```
I modified the ```char *var = new char[1024]``` to ```char *var``` in order to induce the problem of not allocating memory before using that memory.

When we compile and run this program through Valgrind using Memcheck, we get:

```
    $ g++ example2.cpp
    $ valgrind --tool=memcheck ./a.out
```

```
    ==4942== Memcheck, a memory error detector
    ==4942== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==4942== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
    ==4942== Command: ./a.out
    ==4942== 
    ==4942== Use of uninitialised value of size 8
    ==4942==    at 0x4C2E1E0: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==4942==    by 0x400C4D: main (in /home/william/ucr-cs100/tutorials/valgrind/a.out)
    ==4942== 
    ==4942== 
    ==4942== Process terminating with default action of signal 11 (SIGSEGV)
    ==4942==  Bad permissions for mapped region at address 0x400AC0
    ==4942==    at 0x4C2E1E0: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==4942==    by 0x400C4D: main (in /home/william/ucr-cs100/tutorials/valgrind/a.out)
    ==4942== 
    ==4942== HEAP SUMMARY:
    ==4942==     in use at exit: 36 bytes in 1 blocks
    ==4942==   total heap usage: 1 allocs, 0 frees, 36 bytes allocated
    ==4942== 
    ==4942== LEAK SUMMARY:
    ==4942==    definitely lost: 0 bytes in 0 blocks
    ==4942==    indirectly lost: 0 bytes in 0 blocks
    ==4942==      possibly lost: 36 bytes in 1 blocks
    ==4942==    still reachable: 0 bytes in 0 blocks
    ==4942==         suppressed: 0 bytes in 0 blocks
    ==4942== Rerun with --leak-check=full to see details of leaked memory
    ==4942== 
    ==4942== For counts of detected and suppressed errors, rerun with: -v
    ==4942== Use --track-origins=yes to see where uninitialized values come from
    ==4942== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
    Segmentation fault (core dumped)
```

We can see right under ```Command:``` that we have the statement ```Use of uninitialized value of size 8```. This statement implies that we tried to use memory, that we have not allocated, which would cause a segmentation fault. This segmentation fault is shown at the end of the output.

We also see that below the line ```Process terminating with default action of signal 11(SIGSEGV)``` we get the message ```Bad permissions for mapped region at address 0x400AC0```. The ```Bad permission``` statement also states that we have not allocated the memory that we want to access.

We can see that Valgrind and Memcheck are trying to help us find our issue by giving us the message ```Use --track-origins=yes to see where uninitialized values come from```. So let's give this a try ourselves:

Let's run the command:

```
    $ valgrind --tool=memcheck --track-origins=yes ./a.out
```

We get the following output that is different from before:

```
    ==5278== Use of uninitialised value of size 8
    ==5278==    at 0x4C2E1E0: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==5278==    by 0x400C4D: main (in /home/william/ucr-cs100/tutorials/valgrind/a.out)
    ==5278==  Uninitialised value was created by a stack allocation
    ==5278==    at 0x400BFA: main (in /home/william/ucr-cs100/tutorials/valgrind/a.out)
```

The extra two lines added from before tell you what function the uninitialized value was created in, in this case ```main```.


This feature of Valgrind and Memcheck can help tremendously in debugging your programs and save you tons of time.

Conclusion
----------

Valgrind has a lot of functionality that can drastically decrease your debugging time and let you focus on being a better programmer. 

Now you can test your programs using Valgrind to catch the pesky memory leaks that are almost impossible to find with the naked eye.

Happy programming!!!
