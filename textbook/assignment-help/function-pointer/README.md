##Function Pointer
###What is a function pointer
Basically a function pointer is still a type of pointer similar to the pointers we are already familiar with just like `int *ptr_int` and `char *ptr_c`.
But instead of referring to data values, a function pointer points to executable code within memory, i.e. a function.

This may sound odd at first glance.
But recall what we've learned in CS12 that our program memory is organized into four parts - [data segment, heap, stack](http://en.wikipedia.org/wiki/Data_segment)  and [code segment](http://en.wikipedia.org/wiki/Code_segment).
While our program is running, our functions are stored in  code segment and the entrance of each function will have a correspondent address in memory the same as various data structure like _int_, _string_.

Therefore when dereferenced, a function pointer can be used to invoke the function it points to and pass it arguments just like a normal function call.

###How to use function pointer


###Why to use function pointer

###Function pointer and function

###Reference
[Wikipedia](http://en.wikipedia.org/wiki/Function_pointer)
