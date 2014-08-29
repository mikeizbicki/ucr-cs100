
Valgrind Tutorial
=================

General
-------

Valgrind is a linux tool that helps you deal with debugging memory management issues. 

Valgrind used along side with Memcheck will display how many allocations you have done, how many deallocations and how many bytes were allocated and deallocated.

Finding our problem
-------------------


 * let's start with a code example from the program test.cpp:

```
    1)  int main()
    2)  {   
    3)      char *var = new char[1024};
    4)      return 0;
    5)  }
```

 * In the code above, we can see on line number 3 that we have allocated some memory using the new operator.

 * When we run this program in Valgrind using the command:

```
    valgring --tool=memcheck ./a.out
```
   
    
 * We get the following output:

```
    1)==4090== Memcheck, a memory error detector
    2)==4090== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    3)==4090== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
    4)==4090== Command: ./a.out
    5)==4090== 
    6)==4090==    
    7)==4090== HEAP SUMMARY:  
    8)==4090==     in use at exit: 1,024 bytes in 1 blocks
    9)==4090==   total heap usage: 1 allocs, 0 frees, 1,024 bytes allocated
    10)==4090== 
    11)==4090== LEAK SUMMARY:
    12)==4090==    definitely lost: 1,024 bytes in 1 blocks
    13)==4090==    indirectly lost: 0 bytes in 0 blocks
    14)==4090==      possibly lost: 0 bytes in 0 blocks
    15)==4090==    still reachable: 0 bytes in 0 blocks
    16)==4090==         suppressed: 0 bytes in 0 blocks
    17)==4090== Rerun with --leak-check=full to see details of leaked memory
    18)==4090== 
    19)==4090== For counts of detected and suppressed errors, rerun with: -v
    20)==4090== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


 * If we look at like number 8, we can see that there were still 1,024 bytes still in use when the program exited. 

 * Also at line 9, we can see that there was 1 allocation and 0 deallocation, which implies a memory leak.

 * We can also look at the leak summary to see if we can recover any leaked memory.

 * Looking at line 12, we see that the 1,024 bytes lost are not recoverable.


How to fix memory leaks
-----------------------

 * To obtain more information about where the memory leak may have occured you can type the command:

```
        valgring --tool=memcheck --leak-check=full ./a.out
```


 * The extra flag in this call will print out information about what function could be causing the leak and which function call is creating the possiblity of the leak.

 * Between the HEAP SUMMARY and LEAK SUMMARY we will get the message:


```
    1)==4102== 1,024 bytes in 1 blocks are definitely lost in loss record 1 of 1
    2)==4102==    at 0x4C2B800: operator new[](unsigned long) (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    3)==4102==    by 0x40071E: main (in /home/william/cs100/hw5/a.out)
```

 * We can see that at line 3, valgrind says that the memory leak is cause BY the function main and at line 2, valgrind says the leak is cause AT new[].

 * This information will help you find where your leaks are at in your program.

    
Fix all leaks and rerun
-----------------------

 * If we take our old program and add a delete right under it, our problem should be fixed!


```
    1)  int main()
    2)  {   
    3)      char *var = new char[1024};
    4)      delete [] var;
    5)      return 0;
    6)  }
```


 * Now if we run memcheck again we will get:


```
    1)==2284== Memcheck, a memory error detector
    2)==2284== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    3)==2284== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
    4)==2284== Command: ./a.out
    5)==2284== 
    6)==2284== 
    7)==2284== HEAP SUMMARY:
    8)==2284==     in use at exit: 0 bytes in 0 blocks
    9)==2284==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
    10)==2284== 
    11)==2284== All heap blocks were freed -- no leaks are possible
    12)==2284== 
    13)==2284== For counts of detected and suppressed errors, rerun with: -v
    14)==2284== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

 * If we look at line 9 we can see that our change worked and for 1 allocation we have 1 free.

 * We just looked at a very simple example that only has 6 lines of code, of course there will be more complicated programs and now I will demonstrate valgrind and memcheck with more complex programs.

More complex example
--------------------


```
    1 #include <iostream>
    2 #include <cstring>
    3 
    4 using namespace std;
    5 
    6 void doSomething(char *ptr)
    7 {
    8     char *var2 = new char[1024]; // create a new char*
    9     strcpy(var2,ptr); // copy old char* into new char*
    10     cout << var2 << endl; // output new char*
    11     //delete [] var2;
    12 }
    13 
    14 int main()
    15 {   
    16     char *var = new char[1024]; //create char*
    17     string str = "hello world"; //create string to go into char*
    18     strcpy(var,str.c_str()); //copy string into char*
    19     cout << var << endl; // output char*
    20     doSomething(var); // call function with char*
    21     //delete [] var;
    22     return 0; 
    23 }  
```


 * If we have program like the one above, we can see that the program calls a function that  allocates some memory in the main and also in a function. now if we run this program in valgrind with memcheck we will the get the following message:

```
    1  memory error detector
    2  ==3311== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward e    t al.
    3  ==3311== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for co    pyright info
    4  ==3311== Command: ./a.out
    5  ==3311== 
    6  hello world
    7  hello world
    8  ==3311== 
    9  ==3311== HEAP SUMMARY:
    10  ==3311==     in use at exit: 2,048 bytes in 2 blocks
    11  ==3311==   total heap usage: 3 allocs, 1 frees, 2,084 bytes allocat    ed
    12  ==3311== 
    13  ==3311== LEAK SUMMARY:
    14  ==3311==    definitely lost: 2,048 bytes in 2 blocks
    15  ==3311==    indirectly lost: 0 bytes in 0 blocks
    16  ==3311==      possibly lost: 0 bytes in 0 blocks
    17  ==3311==    still reachable: 0 bytes in 0 blocks
    18  ==3311==         suppressed: 0 bytes in 0 blocks
    19  ==3311== Rerun with --leak-check=full to see details of leaked memo    ry
    20  ==3311== 
    21  ==3311== For counts of detected and suppressed errors, rerun with:     -v
    22  ==3311== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 fro    m 0))')
```


 * As we can see the program runs normal, printing out "hello world" twice, but when we lok at the HEAP SUMMARY we see that there were 3 allocations and 1 free. This means that we have a memory leak again.
 * If we look back at our progam we can see that we used new but never called delete.
 * To fix our problem we ned to add in deletes for the VAR pointer and the PTR pointer like such:

```
    1 #include <iostream>
    2 #include <cstring>
    3 
    4 using namespace std;
    5 
    6 void doSomething(char *ptr)
    7 {
    8     char *var2 = new char[1024]; // create a new char*
    9     strcpy(var2,ptr); // copy old char* into new char*
    10     cout << var2 << endl; // output new char*
    11     delete [] var2;
    12 }
    13 
    14 int main()
    15 {   
    16     char *var = new char[1024]; //create char*
    17     string str = "hello world"; //create string to go into char*
    18     strcpy(var,str.c_str()); //copy string into char*
    19     cout << var << endl; // output char*
    20     doSomething(var); // call function with char*
    21     delete [] var;
    22     return 0; 
    23 } 
```


 * And now when we put this through valgrind, we should not have any memory leaks.

```
    1  ==3413== HEAP SUMMARY:
    2  ==3413==     in use at exit: 0 bytes in 0 blocks
    3  ==3413==   total heap usage: 3 allocs, 3 frees, 2,084 bytes allocat    ed
    4  ==3413==
    5  ==3413== All heap blocks were freed -- no leaks are possible
    6  ==3413== 
    7  ==3413== For counts of detected and suppressed errors, rerun with:     -v
    8  ==3413== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 fro    m 0))')
```

 * There you have it! Now you can test your programs uing valgrind to catch the pesky memory leaks that are almost impossible to find with the naked eye.
 * Happy programming!!!
