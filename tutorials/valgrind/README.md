
Valgrind Tutorial
=================

General
-------

Valgrind is a linux tool that helps you deal with debugging memory management issues. 

Valgrind used along side with Memcheck will display how many allocations you have done, how many deallocations and how many bytes were allocated and deallocated.

Finding our problem
-------------------


let's start with a code example from the program example1.cpp:

```
    int main()
    {   
        char *var = new char[1024};
        return 0;
    }
```

In the code above, we can see that we have allocated some memory using the ```new``` operator.

When we run this program in Valgrind using the commands:

```
    $ g++ example1.cpp
    $ valgring --tool=memcheck ./a.out
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


If we look at the line under ```HEAP SUMMARY```, we can see that there were still 1,024 bytes still in use when the program exited. 

Also at the next line, we can see that there was 1 allocation and 0 deallocation, which implies a memory leak.

We can also look at the ```LEAK SUMMARY``` to see if we can recover any leaked memory.

Looking at the line right below, we see that the 1,024 bytes lost are not recoverable.


### How to fix memory leaks


To obtain more information about where the memory leak may have occured you can type the command:

```
    $ valgring --tool=memcheck --leak-check=full ./a.out
```


The extra flag in this call will print out information about what function could be causing the leak and which function call is creating the possiblity of the leak.

Between the ```HEAP SUMMARY``` and ```LEAK SUMMARY``` we will get the message:


```
    ==4102== 1,024 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==4102==    at 0x4C2B800: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==4102==    by 0x40071E: main (in /home/william/cs100/hw5/a.out)
```

We can see that in the third line, valgrind says that the memory leak is cause BY the function main and in the second line, valgrind says the leak is cause AT ```new[]```.

This information will help you find where your leaks are at in your program.

     
### Fix all leaks and rerun


If we take our old program example1.cpp, and add a ```delete``` right under the ```new``` statement, our problem should be fixed!


```
    int main()
    {   
        char *var = new char[1024};
        delete [] var;
        return 0;
    }
```


Now if we recompile and run valgrind with memcheck we get:

```
    $ g++ example1.cpp
    $ valgring --tool=memcheck ./a.out
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

We just looked at a very simple example that only has 6 lines of code, of course there will be more complicated programs and now I will demonstrate valgrind and memcheck with more complex program, example2.cpp.

More complex example
--------------------


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


If we have program like the one above, we can see that the program calls a function that allocates some memory in the main and also in a function. now if we run this program in valgrind with memcheck we will the get the following message:

```
    $ g++ example2.cpp
    $ valgring --tool=memcheck ./a.out
```

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


As we can see the program runs normal, printing out "hello world" twice, but when we look at the ```HEAP SUMMARY``` we see that there were 3 allocations and 1 free. This means that we have a memory leak again.
 
If we look back at our program we can see that we used ```new``` but never called ```delete```.
 
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


And now when we put this through valgrind, we should not have any memory leaks.

```
    $ g++ example2.cpp
    $ valgring --tool=memcheck ./a.out
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

There you have it! Now you can test your programs uing valgrind to catch the pesky memory leaks that are almost impossible to find with the naked eye.

Happy programming!!!
