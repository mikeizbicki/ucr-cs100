#Macro

###What is a macro?
A macro (short for macroinstruction) is a fragment of code that is given a name. The C preoprocessor examines the code before it is compiled, and manipulates it in various ways. For example, the preprocesser replaces the line `#include <stdio.h>` with the text of the file 'stdio.h'. In the same way, whenever the name of the macro is used, it is replaced by the contents of that macro. 

In general there are two types of macros, object-like and function-like.

##Object-like Macros

The simplest use of macros is to define constant values with meaningful names. For example: 

`#define PHONE_NO 3331234`

This means that whenever the programmer enters 'PHONE_NO' in his code, it will automatically be replaced by the number. Although the name of the constant is longer than the number, it is more meaningful and helps the program readability. 

##Function-like Macros

You can define macros that operate much like normal functions. To define a function-like macro, you still use the `#define` directive, but you put a pair of parentheses after the macro name.
It is usually of the following form:

`#define MACRO_NAME(arg1, arg2,...) [code to expand]

A simple example would be

`#define MULT(x, y) x * y`

You could use this macro with a statement like

`int z = MULT(3 + 2, 4 + 2);`

You might think the value of z would be 30, but z would actually be 13. While it looks a lot like a function call, you have to remember that the exact text of the argument is pasted in to the macro. When this macro expands, it looks like this

`int z = 3 + 2 * 4 + 2;     // 2 * 4 will be evaluated first`


