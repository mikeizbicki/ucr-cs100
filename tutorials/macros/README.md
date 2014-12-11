#Macro

###What is a macro?
A macro (short for macroinstruction) is a fragment of code that is given a name. The C preoprocessor examines the code before it is compiled, and manipulates it in various ways. For example, the preprocesser replaces the line `#include <stdio.h>` with the text of the file 'stdio.h'. In the same way, whenever the name of the macro is used, it is replaced by the contents of that macro. 

In general there are two types of macros, object-like and function-like. By convention, macro names are typically written in uppercase. Programs are easier to read if macros identified at a glance.

##Object-like Macros

An object-like macro replaces a single identifier with the specified replacement tokens.
They are most commonly used to give symbolic names to numeric constants. For example: 

`#define PHONE_NO 3331234`

This means that whenever the programmer enters 'PHONE_NO' in his code, it will automatically be replaced by the number. Although the name of the constant is longer than the number, it is more meaningful and helps the program readability. 

##Function-like Macros

You can define macros that operate much like normal functions. To define a function-like macro, you still use the `#define` directive, but you put a pair of parentheses after the macro name.
It is usually of the following form:

`#define MACRO_NAME(arg1, arg2,...) [code to expand]`

A simple example would be

`#define MULT(x, y) x * y`

You could use this macro with a statement like

`int z = MULT(3 + 2, 4 + 2);`

You might think the value of z would be 30, but z would actually be 13. While it looks a lot like a function call, you have to remember that the exact text of the argument is pasted in to the macro. When this macro expands, it looks like this

`int z = 3 + 2 * 4 + 2;     // 2 * 4 will be evaluated first`

The way to avoid this problem is to force the arguments to be evaluated first, by surrounding them with parentheses. This is a good way to ensure the correct evaluation of replacement text.

`#define MULT(x, y) (x) * (y)   // Now expands to (3 + 2) * (4 + 2)`

###Stringifying Tokens

One potentially useful macro option is to turn a token into a string. The syntax is to prefix the token with a pound sign '#'. This can be used to print out the token. For example

`#define PRINT_NAME(token) cout << "My name is " #token << endl

Print_NAME(Kenneth Huang);`

The output would be as expected:`My name is Kenneth Huang`




