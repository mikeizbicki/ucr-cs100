# Function Pointer
While our program is running, our functions are stored in code segment and the entrance of each function will have a correspondent address.
A [function pointer](http://en.wikipedia.org/wiki/Function_pointer) is a variable that stores the address of a function that can later be called through that function pointer.

##### A Simple Function and Function Pointer
Let's learn the syntax from an example in [ex1.cpp](https://github.com/hzhu007/ucr-cs100/blob/squash/textbook/assignment-help/function-pointer/src/ex1.cpp).

Here we have a function `hello()`.
This function returns `void` and doesn't have any parameter.
```
void hello() {
    printf("hello world!");
}
```
We create a function pointer `funcPtr` pointing to `hello()`.
```
void (*funcPtr)() = &hello;
/* void (*funcPtr)() = hello; can also be used here */
```
Basically this is similar to creating any other pointers.
However there are several differences.

1. The type before the pointer name must be the return type of the function pointed by this function pointer.
2. We must have parentheses around the pointer `funcPtr`.
If we don’t have parentheses it is seen as `void *funcPtr` which is a void pointer instead of a pointer to a void function.
This is a key point - function pointers should always have parentheses around them.
3. A function pointer must have the same parameter list as that of the function it points to, even if it doesn't have any parameter.
In this case there is no parameter so it's just an empty parentheses `()` following the function pointer.
4. Recall that the name of a function is actually the address of this function and it can be directly assigned to a function pointer.
Thus, we can assign the `hello()` function to the function pointer like `void (*funcPtr)() = hello`.
However, `void (*funcPtr)() = &hello` also works.

Then we dereference our function pointer by using the dereference operator `*` and get `*funcPtr`.
Ah-oh, never forget the parentheses and the parameter list.
Thus, we dereference and call our function pointer like `(*funcPtr)()`.
However, a function pointer can also be called via implicit dereference `funcPtr()`.

##### A Function Pointer with Parameters and a Return Value
Then we come to the second example [ex2.cpp](https://github.com/hzhu007/ucr-cs100/blob/squash/textbook/assignment-help/function-pointer/src/ex2.cpp).
Here we have a function taking two parameters and returning `int`.
```
int add(int x, int y){
    return x + y;
}
```
The assignment and calling are like below.
```
int (*funcPtr)(int, int) = NULL;
/* funcPtr = add; */
funcPtr = &add;
/* int z = funcPtr(20, 10); */
int z = (*funcPtr)(20, 10);
```
There are a few slight differences.

1. When creating our pointer, instead of empty parentheses we have `(int, int)` at the end which matches the parameter list of the `add` function.
2. We now have a `int` return value.
It matches the return value of our `add` function.
3. When we dereferece the function pointer, everything is the same except now we have `(20, 10)` on the end passing parameters.

##### Passing a Function Pointer as a Parameter
Function pointers are useful if we are writing a function to perform a task, but we want the user to be able to define how a particular part of that task will be performed. 

For example, if you are to write a sort routine, you might want to allow the function's caller to sort the data in a way not quite like simple ascending and descending.
A nice way is to pass in a function to the [sort function](http://www.cplusplus.com/reference/algorithm/sort/?kw=sort).
This function might take two pieces of data and perform a comparison on them.
We'll look at the syntax for this from code in [ex3.cpp](https://github.com/hzhu007/ucr-cs100/blob/squash/textbook/assignment-help/function-pointer/src/ex3.cpp).

Suppose we want to sort a string array `string data[6] = {"Sad", "haha", "adore", "dog", "few", "Zoo"};`
The default config of `sort` is ascending by ASCII.
So if we directly apply `sort` on this array, we will get
```
Sad 
Zoo 
adore 
dog 
few 
haha
```
Note that the ASCII of an uppercase is always smaller than a lowercase.
What if we want to sort it by the alphabetical order?
We can define our own comparison method.
```
bool alphabet(string s1, string s2) 
{
    char str1[10], str2[10];
    strcpy(str1, s1.c_str());
    strcpy(str2, s2.c_str());
    for(int i = 0; str1[i] != '\0'; i++){
        str1[i] = tolower(str1[i]);
    }
    for(int i = 0; str2[i] != '\0'; i++){
        str2[i] = tolower(str2[i]);
    }
    return strcmp(str1, str2) < 0;
}
```
Then store all strings in a vector named `myvector` and apply this method to `sort` like `sort(myvector.begin(), myvector.end(), alphabet);`.
Then we can get 
```
adore 
dog 
few 
haha 
Sad 
Zoo 
```
We can define several more comparison methods and use a function pointer `compare` to point to different functions.
Then we can compare different data with different methods using the same function `sort(beginAddr, endAddr, compare);`.

##### Callback Functions
Another use for function pointers is setting up [callback routines](http://en.wikipedia.org/wiki/Callback_%28computer_programming%29) that are invoked when a particular event happens. 
The function is called, and this notifies your program that something of interest has taken place. 

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
See, each line no longer contains multiple parentheses that made us confused.
