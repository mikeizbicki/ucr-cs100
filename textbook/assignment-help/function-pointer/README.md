# Function Pointer
### What is a function pointer
Basically a [function pointer](http://en.wikipedia.org/wiki/Function_pointer) is still a kind of pointer. It is similar to the pointers we are already familiar with just like `int *ptr_int` and `char *ptr_c`.
But instead of referring to data values, a function pointer points to a piece of executable code within memory, aka a function.
While our program is running, our functions are stored in code segment and the entrance of each function will have a correspondent address in memory.
Therefore, when dereferenced, a function pointer can be used to invoke the function it points to and pass it arguments just like a normal function call.

Theory is always tricky.
Let's learn from some real codes.

##### *A Simple Function and Function Pointer Case*
```
#include <stdio.h>
s
// function implementation
void hello() {
    printf("hello world!");
}

// calling from main
int main() {
    /* void (*funcPtr)() = hello; can also be used here */
    void (*funcPtr)() = &hello;
    /* funcPtr(); can also be used here */
    (*funcPtr)();
    return 0;
}
```
Here we have a function `hello() `. 
This function returns `void` and doesn't have any parameter.
We create a function pointer `funcPtr` pointing to `hello()` in `main()`.

Basically this is similar to creating any other pointer - it has to have a name and it uses the `*` notation to signify that it is a pointer.
However there are several differences.
First, when declaring a normal pointer, we have to declare the data type of the variable this pointer pointing to, like `int` and `char`, just before the pointer name.
As to a function pointer, the data type before the pointer name is the return type of the function pointed by this function pointer.
In the case above, we are creating a function pointer to function `hello()` that returns `void` so the return type must be `void`.
Second, we must have parentheses around the pointer `funcPtr`.
If we don’t have parentheses it is seen as `void *funcPtr` which is a void pointer instead of a pointer to a void function.
This is a key point - function pointers should always have parentheses around them.
Third, a function pointer must have the same parameter list as that of the function it points to, even if it doesn't have any parameter.
In this case there is no parameter so it's just an empty parentheses following the function pointer.
Putting it all together we get `void (*funcPtr)()`, a pointer to a function that returns `void` and takes no parameters.

After declaration, we can assign the `hello()` function to the function pointer like this `void (*funcPtr)() = hello`.
Recall that a function name is actually the address of this function and it can be assigned to a function pointer.
Only in the case of a function pointer, the address of the function is the function name and we don't need the reference operator `&`.
However `void (*funcPtr)() = &hello` also works.
I personally prefer the later assignment because it is uniform with all other pointers and a uniform and significant habit can always help avoid some silly mistakes.

Then we dereference our pointer the same as we dereference any other pointer, by using the dereference operator `*`. 
This gives us `*hello`.
Ah-oh, never forget the parentheses around and after a function pointer, otherwise it isn't actual a function pointer.
Thus, we dereference and call our function pointer like this `(*funcPtr)()`.
In this case the function has no return value so there is no need to assign its return to any variable. 
The function call can stand alone just the same as `hello()`.

Note that although we lay stress on the parentheses around a function pointer, actually function pointers are often treated and called as regular functions like this `funcPtr()`.
It is the same as calling the function pointer with full syntax `(*funcPtr)()`.
<!--We will get into function names later which will show why this works.-->

##### *A Function Pointer with Parameters and Return Value*
```
#include <stdio.h>

// function implementation
int add(int x, int y){
    return x + y;
}

// calling from main
int main() {
    int (*funcPtr)(int, int) = NULL;

    /* funcPtr = add; */
    funcPtr = &add;
    /* int z = funcPtr(20, 10); */
    int z = (*funcPtr)(20, 10);
    printf("Add gives: %d\n", z);
    return 0;
}
```
Here comes a few slight differences with the simple case above.
1. When creating our pointer, instead of empty parentheses we have `(int, int)` on the end which matches the parameter list of our `add` function.
2. We now have a `int` return value.
It matches the return value of our `add` function.
3. When we dereferece and execute the function, everything is the same except now we have `(20, 10)` on the end passing parameters.

##### *Passing a Function Pointer as a Parameter*
Let's go a step further to look at using a function pointer to execute different functions based on parameters.
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
In this case we have two functions `add` and `subtract` with the same signature `int <function name>(int, int)`. 
Both return an integer and both take two integers as parameters.
Then we have a function `int domath(int (*mathop)(int, int), int x, int y)` taking a function pointer and two integers as parameters.
The first parameter `int (*mathop)(int, int)` is a pointer to a function that takes two integers as input and returns an integer. 
We have explained this thoroughly before, the syntax is no different here. 
The last two parameters `int x` and `int y` are just integers taken by the `domath` function. 
The `domath` function executes the function pointer `mathop` taking the integers `x` and `y`. 
The execution of `domath` are somewhat new. 
We are passing in the function names. 
As mentioned, function names are the address of the function and can be used in place of function pointers.
The main function calls `domath` twice, once for `add` and once for `subtract`.


### Application
Now we have gone through the main part of the very basic of function pointers.
From the example of *Passing a Function Pointer as a Parameter* we know that we can use a function pointer to dynamically execute different functions.
A simple case is like this: You have a sequence of operations(functions) with the same signature to be executed. 
A clean code would have an array of function pointers, and your program will deduce an index to that array from the input and call it.
Here is a sample code:
```
void (*func_arr[5])();

fn_arr[0] = fun1; // fun1 is previously defined
fn_arr[1] = fun2;
...

void callMyFun(string keyWord) {
    int idx = decideWhichFun(keyWord); // returns an int between 0 and 4
    fn_arr[idx]();
}
```
Notice that we are using an array of function pointers here.
The syntax is the same as a single function pointer except we need brackets `[ ]` indicating how many elements this array has, just like a simple integer array does.
If you are still confused about it, you can refer to [this](http://stackoverflow.com/questions/5488608/how-define-an-array-of-function-pointers-in-c).

However, [callback routines](http://en.wikipedia.org/wiki/Callback_%28computer_programming%29) appear to be the most common scenario where we need function pointers.
Here is a sample code:
```
void lengthyOperation(string input, void (*callback)(string status)) {
  // do a lengthy task here
  // and end up with a status, suppose it is "finished" in this case
  string status = "finished"
  callback(status);
}

void funcAfterLengthyTask(string status) {
    cout << status << endl;
}

int main() {
    lengthyOperation(someinput, funcAfterLengthyTask);
}
```
In simple terms, a callback function is one that is not called explicitly by the programmer. 
Callback mechanism supplies a method as an argument to another method, such that when the parent method is called (whatever condition, such as a button click, a timer etc.) and its method body completes, a selected callback method is then invoked, or in other words "called at the back" of the other function, in response to particular events.
The advantage here is that the calling function can pass whatever parameters(`string status` in this case) it wishes to the callback functions based on the running outcome.
So that the function can be more universal.
Recall that the `signal()` function taking a function pointer as a parameter can deal with lots of different signals.
This also allows correct information hiding: the code that passes a callback to a calling function does not need to know the parameter values that will be passed to the function.

### Analyze three cases:
```
int *pfunc(int, int); //equals to "int *(pfun(int, int));".
```
```
int *(pfunc(int, int)); //pfunc is a function returns an int pointer.
```
```
int (*pfunc)(int, int); //pfunc is a pointer which points to a function that returns an int value.
```

Tricky case: a function pointer as the return value of a function pointer.
```
int (*ff(int))(int *, int);
```
is the same as:
```
int (*(ff(int)))(int *, int);
```
`ff()` is a function that returns a pointer to a function.

It is too complicated for us to understand. So here comes the application of `typedef`. 
```
typedef int (*PF)(int *, int);
PF ff(int);
```
`PF` becomes a type of function pointer when `typedef` is used. 
It is then used to define the type of return value of the `ff()` function.

### Example of typedef
I know there must be some guys confused with the `typedef` thing combined with a function pointer in the [signal lecture](https://github.com/mikeizbicki/ucr-cs100/blob/2015spring/lecture-notes/signals.cpp) cause I am the one ;).
Let's make it clearer together.

First, take a look at these three simple examples using typedef.
```
typedef int myinteger;
typedef char *mystring;
typedef void (*myfunc)();
```
Use them like
```
myinteger i;   // is equivalent to    int i;
mystring s;    // is the same as      char *s;
myfunc f;      // compile equally as  void (*f)();
```

`typedef` is used to ease the reading of the code, especially for pointers to functions, or structure names.
If you want to know more details about `typedef`, refer to [this site](http://www.cplusplus.com/doc/tutorial/other_data_types/).
We will pay attention to the case where function pointers involve typedef.

Let's take a look at a more complicated example: the `qsort` algorithm within `cstdlib` library.[reference is here](http://www.cplusplus.com/reference/cstdlib/qsort/).
```
void qsort (void* base, //Pointer to the first object of the array to be sorted, converted to a void*.
            size_t num, //Number of elements in the array pointed by base.
            size_t size, //Size in bytes of each element in the array.
            int (*compar)(const void*,const void*));
```
`compar` is a pointer to a function that compares two elements.
This function is called repeatedly by qsort to compare two elements. 
It shall follow the following prototype:
```
int compar (const void* p1, const void* p2);
```
We can implement the function using `typedef` like below:
```
typedef int (*compfn) (const void*, const void*);

qsort((void *) &array,              // Beginning address of array
      10,                           // Number of elements in array
      sizeof(struct animal),        // Size of each element
      (compfn)compare               // Pointer to compare function
                                    // It is equal to "int (*compfn)(const void*, const void*)"
 );
```
At calling `qsort()`:
In expression `(compfn)compare`, we are typecasting a function `compare` to `(compfn)` type function. 
If we just write `int (*compfn) (const void*, const void*);` without `typedef` then `comfn` will be a pointer to a function that returns `int` and take two arguments of type `const void*`.

Then take a look at the following code which we met in the class:
```
#include <signal.h>
void (*signal(int sig, void (*func)(int)))(int);
```
First we can interpret by treating everything in parentheses as a single entity and then working inwards.
<p><code>void <strike>(*signal(int sig, void (*func)(int)))</strike> (int);</code></p>
The entity in the brackets looks like a function taking `int` and returning `void`.
Stripping away the outer part:

`*signal(int sig, void (*func)(int))`

So, `signal` takes some parameters and returns something that can be dereferenced (due to the leading `*`) to form a function taking `int` and returning `void`.
This means `signal` is a function returning a pointer to a function (taking `int` and returning `void`).
Looking at the parameters it takes an `int` (i.e. `sig`) and `void (*func)(int)` which is a pointer to a function (taking `int` and returning `void`).

But it can be much clearer if use `typedef` as follow.
```
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signo, sighandler_t func);
```

See, each line no longer contains multiple parentheses which made us confused.
