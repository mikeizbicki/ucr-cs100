#Macro

###What is a macro?
A macro (short for macroinstruction) is a fragment of code that is given a name. The C preoprocessor examines the code before it is compiled, and manipulates it in various ways. For example, the preprocesser replaces the line `#include <stdio.h>` with the text of the file 'stdio.h'. In the same way, whenever the name of the macro is used, it is replaced by the contents of that macro. 

In general there are two types of macros, object-like and function-like. By convention, macro names are typically written in uppercase. Programs are easier to read if macros can be identified at a glance.

##Object-like Macros

An object-like macro replaces a single identifier with the specified replacement code.
They are most commonly used to give symbolic names to numeric constants. For example: 

`#define PHONE_NO 3331234`

This means that whenever the programmer enters 'PHONE_NO' in his code, it will automatically be replaced by the number. Although the name of the constant is longer than the number, it is more meaningful and helps the program readability. Also it is easier to change the number later, in this case if you want to try a different phone number, changing it at the macro definition will replace it everywhere in your code.

##Function-like Macros

You can define macros that operate much like normal functions. To define a function-like macro, you still use the `#define` directive, but you put a pair of parentheses after the macro name.
It is usually of the following form:

`#define MACRO_NAME(arg1, arg2,...) [code to expand]`

A simple example would be

`#define MULT(x, y) x * y`

You could use this macro with a statement like

`int z = MULT(2, 4); // z = 8`


###Stringifying Tokens

One potentially useful macro option is to turn a token into a string. The syntax is to prefix the token with a pound sign '#'. This can be used to print out the token. For example

 `#define PRINT_NAME(token) cout << "My name is " << #token << endl

 PRINT_NAME(Kenneth Huang);`

 The output would be as expected:`My name is Kenneth Huang`

###Multi-line Macros

Macro definitions end at the end of the `#define` line, so to continue the definition onto multiple lines, you have to use a backslash-newline. However, when the macro expands it all appears on one line. For example,

`#define CHARS  'a', \
                'b', \
                'c' 
char a[] = { CHARS }; // is equivalent to
// int a[] = { 'a', 'b', 'c' };`

###Combining Macros

Macros definitions can include previously defined macros. For example, if you had a macro that returns the larger of two numbers, and you also wanted to find the largerst of 3 numbers.

`#define MAX(a,b)           ((a < b) ? (b) : (a))
 #define LARGEST(a,b,c)     ((MAX(a,b) < c) ? (c) : (MAX(a,b)))

 cout << "Largest of 1, 2, and 3 is " << LARGEST(1,2,3);
 
 //Output: Largest of 1, 2, and 3 is 3`

##Common Macro Errors

###Operator Precedence

Earlier we defined a simple multiplication macro that doesn't work the way we expect when we pass other arguments. For example,

`int z = MULT(3 + 2, 4 + 2);`

You might think the value of z would be 30, but z would actually be 13. While it looks a lot like a function call, you have to remember that the exact text of the argument is pasted in to the macro. When this macro expands, it looks like this.

`int z = 3 + 2 * 4 + 2;     // 2 * 4 will be evaluated first`

The way to avoid this problem is to force the arguments to be evaluated first, by surrounding them with parentheses. This is a good way to ensure the correct evaluation of replacement text.

`#define MULT(x, y) (x) * (y)   // Now expands to (3 + 2) * (4 + 2)`

###Semicolon Issues

Consider the following macro.

`#define MACRO(x,y) {\
    cout << "1st arg is: " << (x) << endl; \
    cout << "2nd arg is: " << (y) << endl; \
    cout << "Sum is: " << ((x) + (y)) << endl; \
}`

A call to this macro might be `MACRO(2,4)` This call expands to a complete compound statement that doesn't require a semicolon to end it. However, since it looks like a function call, it makes it less confusing if you can use it like one, and write a semicolon afterward, as in `MACRO(2,4);`

In this case the semicolon is redundant, and creates a null statement. This becomes an issue in if else statements.

`if ( x!= y )
    MACRO(x,y);
else ... `

Since there are two statements between the `if` and the `else`, this becomes invalid C code. A way to fix this problem is to change the macro definition with a do ... while statement.

`#define MACRO(x,y) \
do { cout << "1st arg is: " << (x) << endl; \
    cout << "2nd arg is: " << (y) << endl; \
    cout << "Sum is: " << ((x) + (y)) << endl; \
} while (0)`

Now `MACRO(2,4);` expands into `do {...} while (0);` This is one statement, and the loop executes exactly once.

###Duplication of Side Effects

Another problem is that macros don't evaluate their arguments, and instead paste them into the text. This becomes an issue with the previous MAX macro if you pass in x++, y++.

`#define MAX(a,b) ((a) < (b) : (a))
int x = 5, y = 10;
int z = MAX(x++, y++);

//This becomes
// int z = (x++ < y++ ? y++ : x++)`

The problem is that in this case y++ is evaluated twice, and y will have a value of 12 instead of what we expected, 11.

###Macros and namespace

Macros have no namespace and you can easily accidentally redefine a macro, that was defined in included system header files. For example,

`#define begin() x=0` 

Later if you try to use `myvector.begin()` you will have strange errors that aren't obvious where they came from in your code.

##Conclusion
Preprocessor macros add powerful features and flexibility, and they can help reduce the amount of code you write. They're also faster to execute than functions, since no calling/returning is required. However, they also have many drawbacks, as we have seen. They are difficult to debug, can have strange side effects, and have no namespace. But while there now are alternatives like inline functions, macros can still be an incredibly useful tool if you are careful.
