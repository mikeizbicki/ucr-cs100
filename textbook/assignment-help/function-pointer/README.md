##Function Pointer
###What is a function pointer

Basically a function pointer is still a type of pointer similar to the pointers we are already familiar with just like `int *ptr_int` and `char *ptr_c`.
But instead of referring to data values, a function pointer points to executable code within memory, i.e. a function.

This may sound odd at first glance.
But recall what we've learned in CS12 that our program memory is organized into four parts - [data segment, heap, stack](http://en.wikipedia.org/wiki/Data_segment) and [code segment](http://en.wikipedia.org/wiki/Code_segment).

While our program is running, our functions are stored in code segment and the entrance of each function will have a correspondent address in memory.

Just the same as you've been creating various data structure like _array_, _string_ and _char[]_.

Therefore when dereferenced, a function pointer can be used to invoke the function it points to and pass it arguments just like a normal function call.

###How to use function pointer
Theory is always tricky. Let's take a look at some real code.

The format of a function pointer goes like this:
`int (*POINTER_NAME)(int a, int b)`

###Why to use function pointer

###Function pointer and function


###Example of typedef

I know there must be some guys confused with the `typedef` thing combined with a function pointer in the [signal lecture](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/lecture-notes/signals.cpp) cause I am the one ;).
Let's make it clearer together.

If you don't know what `typedef` does, refer to [this site](http://www.cplusplus.com/doc/tutorial/other_data_types/). We will pay attention to the case where function pointer involving typedef.



First, take a look at
`typedef char * pChar;`

Then take a look at the following code.
```
#include <signal.h>
void (*signal(int sig, void (*func)(int)))(int);
```
This is the original function declaration for UNIX function `signal()` in `signal.h`, which, said by many programmers, the most complex definition among all UNIX methods.

C/C++ declarations need to be read from the inside out. The tricky part with complex function declarations is figuring out which is the innermost declarator (where to start). Its generally the first identifier that is not a type identifier. So in this case, the declarator is signal. Within the parenthesis, suffixes are higher precedence than prefixes, so signal is a function taking two args (the `(int sig, void *(func)(int))` part), that returns a pointer (the prefix `*`) to a function taking a single int arg (the `(int)` on the end), and returning `void`.

But it can be much clear if use `typedef` as follow.
```
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signo, sighandler_t func);
```
`sighandler_t` is a pointer to a function that takes an `int` parameter and returns `void`(nothing). The `signal` function takes such a function pointer as its second parameter. It also returns a function pointer of that type.

###Reference
[Wikipedia – func ptr](http://en.wikipedia.org/wiki/Function_pointer)

[Typedef1](http://www.cplusplus.com/doc/tutorial/other_data_types/)

[Typedef2](http://en.wikipedia.org/wiki/Typedef)

[Meaning of signal declaration](http://stackoverflow.com/questions/3706704/whats-the-meaning-of-this-piece-of-code-void-signalint-sig-void-funcin)
