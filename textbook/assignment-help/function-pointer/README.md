##Function Pointer
###What is a function pointer
Basically a function pointer is still a type of pointer similar to the pointers we are already familiar with just like `int *ptr_int` and `char *ptr_c`.
But instead of referring to data values, a function pointer points to executable code within memory, i.e. a function.

This may seem odd at first glance.
But recall what we've learned in CS12 that our program memory is organized into four parts - [data segment, heap, stack](http://en.wikipedia.org/wiki/Data_segment) and [code segment](http://en.wikipedia.org/wiki/Code_segment).
While our program is running, our functions are stored in code segment and the entrance of each function will have a correspondent address in memory.
Just the same as you've been creating various data structure like _array_, _string_ and _char[]_.

Therefore when dereferenced, a function pointer can be used to invoke the function it points to and pass it arguments just like a normal function call.

###How to use function pointer
Theory is always tricky.
Let's learn from some real codes.
That's the way we geeky CS students like to learn.

The format of a function pointer goes like this:
```
int (*POINTER_NAME)(int a, int b)
```
In this case, POINTER_NAME is a pointer to a function taking two arguments int a and int b, and that returns int.

Analyze three cases:
```
int *pfunc(int, int);
```
```
int *(pfunc(int, int));
```
```
int (*pfunc)(int, int);
```

Tricky case: a function pointer as the return value of a function pointer
```
int (*ff(int))(int *, int);
```
The same as:
```
int (*(ff(int)))(int *, int);
```

* A Simple Function and Function Pointer Case
```
#include <stdio.h>;

// function implementation
void hello() {
    printf("hello world!");
}

// calling from main
int main() {
    void (*funcPtr)() = &hello;
    //void (*funcPtr)() = hello; can also be used here
    (*funcPtr)();
}
```
Don’t forget the parentheses.

* A Function Pointer with Parameters and Return Value
```
#include <stdio.h>

// function implementation
int subtract(int x, int y) {
    return x - y;
}

int add(int x, int y){
    return x + y;
}

// calling from main
int main() {
    int (*funcPtr)(int, int) = NULL;

    funcPtr = &subtract;
    int y = (*funcPtr)(20, 10);
    printf("Subtract gives: %d\n", y);

    funcPtr = &add;
    int z = funcPtr(20, 10);
    printf("Add gives: %d\n", z);
}
```

* Passing a Function Pointer as a Parameter
```
#include <stdio.h>

// add x + y
int add(int x, int y) {
    return x + y;
}

// subtract x - y
int subtract(int x, int y) {
    return x - y;
}

// run the function pointer with inputs
int domath(int (*mathop)(int, int), int x, int y) {
    return (*mathop)(x, y);
}

// calling from main
int main() {
    // call math function with add
    int a = domath(add, 10, 2);
    printf("Add gives: %d\n", a);

    // call math function with subtract
    int b = domath(subtract, 10, 2);
    printf("Subtract gives: %d\n", b);
}
```

###Why to use function pointer
*Can be use to callback and call functions in a class.*
*More efficient than switch case*

###Example of typedef
I know there must be some guys confused with the `typedef` thing combined with a function pointer in the [signal lecture](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/lecture-notes/signals.cpp) cause I am the one ;).
Let's make it clearer together.

If you don't know what `typedef` does, refer to [this site](http://www.cplusplus.com/doc/tutorial/other_data_types/).
We will pay attention to the case where function pointer involving typedef.

First, take a look at a simple example using typedef.
`typedef char * pChar;`

Then take a look at the following code.
```
#include <signal.h>
void (*signal(int sig, void (*func)(int)))(int);
```
This is the original function declaration for UNIX function `signal()` in `signal.h`, which, said by many programmers, the most complex definition among all UNIX methods.
It's the declaration of a function taking an `int` and a pointer to a function (taking `int` returning void) and returning a pointer to a function (taking `int` and returning void).

We can interpret by treating everything in parentheses as a single entity and then working inwards using the "declaration follows usage" rule.
```
void `` ~~(*signal(int sig, void (*func)(int)))~~ ``(int);
```
The entity in the brackets looks like a function taking `int` and returning `void`.
Stripping away the outer part:

`*signal(int sig, void (*func)(int))`

So, `signal` takes some parameters and returns something that can be dereferenced (due to the leading `*`) to form a function taking `int` and returning `void`.
This means `signal` is a function returning a pointer to a function (taking `int` and returning `void`).
Looking at the parameters it takes an `int` (i.e. `sig`) and `void (*func)(int)` which is a pointer to a function (taking `int` and returning `void`).

But it can be much clear if use `typedef` as follow.
```
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signo, sighandler_t func);
```
`sighandler_t` is a pointer to a function that takes an `int` parameter and returns `void`(nothing). The `signal` function takes such a function pointer as its second parameter. It also returns a function pointer of that type.

####The difference between `typedef` and `define`


###Reference
[Wikipedia – func ptr](http://en.wikipedia.org/wiki/Function_pointer)

[typedef1](http://www.cplusplus.com/doc/tutorial/other_data_types/)

[typedef2](http://en.wikipedia.org/wiki/Typedef)

[Meaning of signal declaration](http://stackoverflow.com/questions/3706704/whats-the-meaning-of-this-piece-of-code-void-signalint-sig-void-funcin)
