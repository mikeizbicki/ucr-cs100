##Macro Basics

####What is a macro?
A macro (short for macroinstruction) is a fragment of code that is given a name. The C preprocessor examines the code before it is compiled, and manipulates it in various ways. We might not have known it, but we have encountered this procedure before in include statements. The preprocessor sees and replaces the line `#include <iostream>` with the text of the file 'iostream'. In the same way, whenever the name of the macro is used, it is replaced by the contents of that macro. 

There are two types of macros, object-like and function-like. By convention, macro names are typically written in uppercase because programs are easier to read if macros can be identified at a glance.

####Object-like Macros

An object-like macro replaces a single identifier with the specified replacement code.
They are most commonly used to give symbolic names to numeric constants. For example: 

`#define ARRAY_SIZE 100`

This means that whenever the programmer enters `ARRAY_SIZE` in his code, it will automatically be replaced by the number. Although the macro name is longer than the actual number, it is more meaningful and helps the program readability. Also it is easier to change the number later, in this example if they want a different array size, changing it at the macro definition will replace it everywhere in your code.

####Similarity to Constants

Consider the statement `const int ARRAY_SIZE = 100`. It functions nearly the same way as an object macro. However, there are many significant differences. `const`s are properly scoped, and can be used in situations that require a pointer to be passed. Macros aren't error checked, and the compiler checks the code only after they are replaced. This occasionally results in errors that might cause unexpected runtime results, which is a problem `const`s do not have.

The main advantage to using a macro is that they are compatible with C, so any C standard library will use them. Also, no memory is used to store it in your program, since it's only replacing text with a literal value. That means there's no way to change this value by any means other than altering the macro definition. With `const`s, some compilers just allocate memory identified by the name, and you might be able to modify the memory with pointers. For example:

```
const int constant = 10;

int * change_value = (int*) &constant;

*change_value = 5; //constant may be 10 or 5 or might cause a segfault depending on compiler
```

On my x86_64 machine, constant had a value of 5 when compiled with gcc, and a value of 10 when compiled with g++.

####Function-like Macros

You can define macros that operate much like normal functions. To define a function-like macro, you still use the `#define` directive, but you put a pair of parentheses after the macro name.
They follow this form:

`#define MACRO_NAME(arguments, separated by commas) [code to expand]`

A simple commonly used example would be a macro that determines which argument is smaller:

`#define MIN(x, y) ((x < y) ? x : y)`

You could use this macro with a statement like:

`int z = MIN(4, 10); // z = 4`

####Multi-line Macros

Macro definitions end at the end of the `#define` line, so to continue the definition onto multiple lines, you have to use a backslash-newline. However, when the macro expands, it all appears on one line. This makes longer macros easier to read. For example:

```
#define ODDEVEN(x) cout << "The number is "; \
                        if (x % 2 == 0) cout << "EVEN\n";\
                        else cout << "ODD\n";
int i = 5;
ODDEVEN(i);
//OUTPUT:The number is ODD
```

####Stringifying Tokens

One potentially useful macro option is to turn a token into a string. The syntax is to prefix the token with a pound sign '#'. This can be used to print out the token. For example:

``` 
#define PRINT_GRADE(token) cout << "The grade for " << #token << " is " << token << endl

int Kenneth_Huang = 85;
PRINT_GRADE(Kenneth_Huang);
//Output:The grade for Kenneth_Huang is 85
```

This can be useful when debugging, and if you wanted to know the exact arguments being passed to the macro.

####Combining Macros

Macros definitions can include previously defined macros. For example, if you had a macro that returns the larger of two numbers and another to find the largest of 3 numbers, as shown here:

```
#define MAX(a,b)           ((a < b) ? (b) : (a))
#define MAX3(a,b,c)     ((MAX(a,b) < c) ? (c) : (MAX(a,b)))

cout << "Largest of 1, 2, and 3 is " << MAX3(1,2,3);
 
//Output: Largest of 1, 2, and 3 is 3
```

####Standard Predefined Macros
GNU C provides many standard predefined macros that are available regardless of the machine and operating system you use. Their names all begin and end with double underscores, and we'll look at two of them.

`__FILE__`
This macro contains the name of the current input file as a C string constant.

`__LINE__`
This macro contains the current input line number as a decimal integer constant.

These can be useful in debugging. One way to use them is:
```
#define FILE_LINE cout << "At " __FILE__ ":" << __LINE__ << endl;

FILE_LINE
//Sample output:At test.cpp:27
```
More predefined macros can be found at the [GCC website](https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html)

##Common Macro Errors

####Operator Precedence

This is a fairly common error that isn't immediately obvious. Consider the following macro:

```
#define DIVIDE(a, b) a / b

int z = DIVIDE(20, 3 + 2);
```

You might think the value of z would be 4, but z would actually be 8. While this macro looks a lot like a function call, you have to remember that the exact text of the argument is put in. The preprocessor will expand it like this:

```
int z = 20 / 3 + 2;        
// 20 / 3 evaluates first, and then + 2
```

The way to avoid this problem is to force the arguments to be evaluated first, by surrounding them with parentheses. This is a good way to ensure the correct evaluation of replacement text and to make it safer, as shown here:

```
#define DIVIDE(a, b) ((a) / (b))         
// Now expands to ((20) / (3 + 2))
```

####Semicolon Issues

Consider the following macro:

```
#define MACRO(x,y) {\
    cout << "1st arg is: " << (x) << endl; \
    cout << "2nd arg is: " << (y) << endl; \
    cout << "Sum is: " << ((x) + (y)) << endl; \
}
```

A call to this macro might be `MACRO(2,4)` This call expands to a complete compound statement that doesn't require a semicolon to end it. However, since it looks like a function call, it makes it less confusing if you can use it like one and write a semicolon afterward, as in `MACRO(2,4);`

In this case, the semicolon is redundant and creates a null statement. This becomes an issue in if else statements, as shown here:

```
if ( x!= y )
    MACRO(x,y);
else ... 
```

Since there are two statements between the `if` and the `else`, this becomes invalid C code. A way to fix this problem is to change the macro definition with a `do ... while` statement, as shown here:

```
#define MACRO(x,y) \
do { cout << "1st arg is: " << (x) << endl; \
    cout << "2nd arg is: " << (y) << endl; \
    cout << "Sum is: " << ((x) + (y)) << endl; \
} while (0)
```

Now `MACRO(2,4);` expands into `do {...} while (0);`. This counts as one statement as the loop executes exactly once.

####Duplication of Side Effects

Another problem is that macros don't evaluate their arguments and, instead, pastes them into the text. This becomes an issue with the previous `MAX` macro if you pass in `x++` and `y++`. For example:

```
#define MAX(a,b) ((a) < (b) : (a))
int x = 5, y = 10;
int z = MAX(x++, y++);

//This becomes
// int z = (x++ < y++ ? y++ : x++)
```

The problem in this case is that `y++` is evaluated twice, which assigns `y` the value of 12 instead of what we expected, 11.

####Unusual Errors

Macros do not have a namespace and aren't error checked, as the compiler only checks the code after the macro names are replaced. Because of this, it is easy to create errors that can be difficult to find. For example:

```
#define begin() end()

... (some code)

for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    cout << ' ' << *it;

```

There won't be any compile errors, but the for loop won't output anything. Runtime errors like this are difficult to debug, because without looking at the macro definition, the code seems perfectly fine.

###Conclusion

Preprocessor macros add powerful features and flexibility, and can help to reduce the amount of code you write. They can also increase performance by reducing the function call overhead, since they're always expanded inline. However, they come with many drawbacks, as we have seen, and can be very difficult to debug. But while there are now alternatives like the inline functions, which weren't standard prior to C99, macros can still be an incredibly useful tool if you are careful.
