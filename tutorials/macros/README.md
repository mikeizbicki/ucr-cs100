#Macros

###What is a macro?
A macro (short for macroinstruction) is a fragment of code that is given a name. The C preprocessor examines the code before it is compiled, and manipulates it in various ways. We might not have known it, but we have encountered this procedure before in include statements. The preprocessor sees and replaces the line `#include <iostream>` with the text of the file 'iostream'. In the same way, whenever the name of the macro is used, it is replaced by the contents of that macro. 

There are two types of macros, object-like and function-like. By convention, macro names are typically written in uppercase because programs are easier to read if macros can be identified at a glance.

##Object-like Macros

An object-like macro replaces a single identifier with the specified replacement code.
They are most commonly used to give symbolic names to numeric constants. For example: 

`#define PHONE_NO 3331234`

This means that whenever the programmer enters `PHONE_NO` in his code, it will automatically be replaced by the number. Although the name of the constant is longer than the number, it is more meaningful and helps the program readability. Also it is easier to change the number later, in this case if you want to try a different phone number, changing it at the macro definition will replace it everywhere in your code.

###Similarity to Constants

Consider the statement `const int PHONE_NO = 3331234`. It functions nearly the same way as an object macro. However there are many significant differences. Consts are properly scoped, and can be used in situations that require a pointer to be passed. They also don't have issues with conflicting usages that might cause unexpected runtime results.

The main advantage to using a macro is that no memory is used to store it in your program, since it's only replacing text with a literal value. That means there's no way to change this value by any means other than altering the macro definition. With consts, some compilers just allocate memory identified by the name, and you might be able to modify the memory with pointers. For example

```
const int constant = 10;

int * change_value = (int*) &constant;

*change_value = 5; //constant may be 10 or 5 depending on compiler
```

##Function-like Macros

You can define macros that operate much like normal functions. To define a function-like macro, you still use the `#define` directive, but you put a pair of parentheses after the macro name.
It is usually of the following form:

`#define MACRO_NAME(arguments, separated by commas) [code to expand]`

A simple commonly used example would be a macro that determines which argument is smaller.

`#define MIN(x, y) ((x < y) ? x : y)`

You could use this macro with a statement like

`int z = MIN(4, 10); // z = 4`

###Multi-line Macros

Macro definitions end at the end of the `#define` line, so to continue the definition onto multiple lines, you have to use a backslash-newline. However, when the macro expands it all appears on one line. For example,

```
#define CHARS   'a', \
                'b', \
                'c' 
char a[] = { CHARS }; // is equivalent to
// int a[] = { 'a', 'b', 'c' };
```

While in this example, defining CHARS this way makes it less readable, being able to split up a macro definition into multiple lines can come in handy with more complex macros.

###Stringifying Tokens

One potentially useful macro option is to turn a token into a string. The syntax is to prefix the token with a pound sign '#'. This can be used to print out the token. For example

``` 
#define PRINT_GRADE(token) cout << "The grade for " << #token << " is " << token << endl

int Kenneth_Huang = 85;
PRINT_GRADE(Kenneth_Huang);
//Output:The grade for Kenneth_Huang is 85
```

This can be useful when debugging, and if you wanted to know exactly the arguments being passed to the macro.

###Combining Macros

Macros definitions can include previously defined macros. For example, if you had a macro that returns the larger of two numbers, and you also wanted to find the largest of 3 numbers.

```
#define MAX(a,b)           ((a < b) ? (b) : (a))
#define MAX3(a,b,c)     ((MAX(a,b) < c) ? (c) : (MAX(a,b)))

cout << "Largest of 1, 2, and 3 is " << MAX3(1,2,3);
 
//Output: Largest of 1, 2, and 3 is 3
```

##Common Macro Errors

###Operator Precedence

This is a fairly common error that isn't immediately obvious. Consider the following macro.

```
#define DIVIDE(a, b) a / b

int z = DIVIDE(20, 3 + 2);
```

You might think the value of z would be 4, but z would actually be 8. While this macro looks a lot like a function call, you have to remember that the exact text of the argument is put in. The preprocessor will expand it like this.

```
int z = 20 / 3 + 2;        
// 20 / 3 evaluates first, and then + 2
```

The way to avoid this problem is to force the arguments to be evaluated first, by surrounding them with parentheses. This is a good way to ensure the correct evaluation of replacement text and it makes it safer.

```
#define DIVIDE(a, b) (a) / (b)         
// Now expands to (20) / (3 + 2)
```

###Semicolon Issues

Consider the following macro.

```
#define MACRO(x,y) {\
    cout << "1st arg is: " << (x) << endl; \
    cout << "2nd arg is: " << (y) << endl; \
    cout << "Sum is: " << ((x) + (y)) << endl; \
}
```

A call to this macro might be `MACRO(2,4)` This call expands to a complete compound statement that doesn't require a semicolon to end it. However, since it looks like a function call, it makes it less confusing if you can use it like one, and write a semicolon afterward, as in `MACRO(2,4);`

In this case the semicolon is redundant, and creates a null statement. This becomes an issue in if else statements.

```
if ( x!= y )
    MACRO(x,y);
else ... 
```

Since there are two statements between the `if` and the `else`, this becomes invalid C code. A way to fix this problem is to change the macro definition with a `do ... while` statement.

```
#define MACRO(x,y) \
do { cout << "1st arg is: " << (x) << endl; \
    cout << "2nd arg is: " << (y) << endl; \
    cout << "Sum is: " << ((x) + (y)) << endl; \
} while (0)
```

Now `MACRO(2,4);` expands into `do {...} while (0);` This is one statement, and the loop executes exactly once.

###Duplication of Side Effects

Another problem is that macros don't evaluate their arguments, and instead paste them into the text. This becomes an issue with the previous MAX macro if you pass in x++, y++.

```
#define MAX(a,b) ((a) < (b) : (a))
int x = 5, y = 10;
int z = MAX(x++, y++);

//This becomes
// int z = (x++ < y++ ? y++ : x++)
```

The problem is that in this case y++ is evaluated twice, and y will have a value of 12 instead of what we expected, 11.

###Macros and namespace

Macros have no namespace and you can easily accidentally redefine a macro, that was defined in included system header files. For example,

```
#define begin() end()

... (some code)

for (vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    cout << ' ' << *it;

```

There won't be any compile errors, but the for loop won't output anything. Runtime errors like this are difficult to debug, because without looking at the macro definition, the code seems perfectly fine.

##Conclusion
Preprocessor macros add powerful features and flexibility, and they can help reduce the amount of code you write. They're also faster to execute than functions, since no calling/returning is required. However, they also have many drawbacks, as we have seen, and can be very difficult to debug. But while there now are alternatives like inline functions, macros can still be an incredibly useful tool if you are careful.
