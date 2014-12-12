#Templates and You

Most beginning programmers have little to no experience with templates. This is because of their complex nature. Most beginning programmers stay away from templates because: 

  - Programmers have been successfully programming without them
  - Templates are difficult to learn
  - The effort it takes to learn is not rewarding enough to some programmers

Templates are indeed quite difficult to learn at first, but if you put the time and effort into them, you can increase your programming efficiency. The pros outweigh the cons!

## Taking Functions One Step Further

Man, aren't functions useful? Through using a simple function, we can simplify long, redundant code into something more compact and efficient.

However, as useful as functions are, they can't do everything!

The idea behind using functions is **_writing code once._** But how would we write a function that can be used by **ints** and **doubles**? For example, in this function we will be doubling a number:
```
int double_num(int x){
    return 2*x;
}
```
Perfect! We can double any number, right? 
Well, sorry to break it to you, but you can't double every number with that function...

What would happen if we called the function like so:
```
    cout << double_num(2.7);
```
First off, you wouldn't get a compiler warning that you're trying to use a double in place of an int (this could lead to some painful debugging later on!). The output of this would actually be:
```
4
```
This is because the double used, **2.7**, would be _rounded down_ to **2** because it would be casted as an **int** in the function.

So how would you fix this? Well, if you're just using functions, you're going to have to write another function but for doubles this time:
```
int double_num(int x){
    return 2*x;
}
double double_num(double x){
    return 2*x;
}
```
There, it's fixed! But that method just defeated the purpose of functions because we just wrote the same code **twice**!

But have no fear, there's a way to write the function once and have it be used by any type of value: **Templates**!

##What's a template?
Let's rewrite the **double_num** function into something more efficient with a template:
```
template <typename TYPE>
TYPE double_num(TYPE x){
    return 2*x;
}
```
I know, I'm throwing a lot of new material at you right now, but let's break the code down into pieces to see what's going on.

The first line of code
```
template <typename TYPE>
```
tells the compiler: _Hey, this is a template!_ The word **TYPE** is just like any other variable. You can actually name it whatever you want! This will be demonstrated later. It allows the compiler and programmer to choose what the function/variable type will be. If you were to call this function, you would call it like normal:
```
cout << double_num(3) << endl;
cout << double_num(3.5) << endl;
```
The compiler will see that you are calling a function-template and would create two functions:
```
int double_num(int x)
double double_num(double x)
```
and use the appropriate function for the appropriate value type. When you run the program, you will get exactly what you wanted:
```
6
7
```
We have just successfully used a template! It wasn't that hard was it? Templates are as complicated as you want to make them. If you want to use a template for a more sophisticated function, then the writing the template for the function might get a little messy.

##Case Study: Vectors
As stated before, templates are only as complicated as you make them. Templates can be used for many things ranging from simple functions (like the one we just made) to classes with member functions.

You may have been using templates without even noticing it! The Standard Template Library provides many containers. For example, **vectors** can be used to store any type of data type. This is because they use templates!

Let's take a look at vectors:
```
template < class T, class Alloc = allocator<T> > class vector;
```
If you're familiar with vectors, then the first paramater should be understandable. `class T` is the type of data you are storing in the vector (such as `int` or `string`).

If you wanted a vector of doubles, then you would call it like so:
```
vector<double> numList;
```
Vectors actually have a second parameter that isn't talked about often. 
```
class Alloc = allocator<T>
```
The second parameter is an allocator class that defines how memory will be allocated if the vector needs more memory. In most cases, you wouldn't need to worry about it because it is set by default. 

However, in certain situations, you would want the vector to use a different type of method of allocating memory, such as programming for machines that have small memory.

In summary, the Standard Template Library uses templates to allow programmers to use the containers with flexability.

##Ok, so why should I use them?

Well, you see... templates are usually just used to avoid repeating code while accounting for different types(Turing Complete), but they are also used to create type-safe containers.

Let's say we want to implement a generic stack push function:
```
template <class T> // here we declare the template
void mystack<T>::push(const T& data) // we use the template any time we want to store data in the container.
{
	top=...
}	

```

As you can see, using templates are crucial when implementing containers because normal functions would not be able to handle multiple types.

If we were to try to create a stack with a bunch of regular functions, then it would only be able to handle one type.

###What about macros?

Another code generation tool are Macros. Unlike templates that run at compile time, macros are a more primitive type and are parsed by the preprocessor which only replaces text.

Since templates run at compile time, they take more build time but are more safe(more on that later). 

To specify a macro, you would write #define follwed by an identifer name and a string or numerics. When the preprocessor sees this it will substitute each occurence of that macro in source code.

Here is a basic example program using macros:

```
#define NAME "Greg"
#define AGE 14
#include <iostream>
using namespace std;

int main()
{
    cout << "My name is " << NAME << " and i am " << AGE << endl;
    return 0;
}
```

Note how the identifier name are always all upper case. Also note how the NAME macro has quotations around Greg. 

Everytime `NAME` appears in the program, the preprocessor will substitute it with "Greg". If the qoutes were not there then that would lead to a sytax error. 

The problem with marcros is that since they are expanded by the preprocessor, the compiler will produce an error message identifieng the line of code which the error occured in and not the marcro definition. Also the macro will show up in expanded form. This can make debugging a pain. 

You can use #define to make macro functions as well
Lets start with an example:

```
#define MIN(a,b) (a < b ? a : b)
#include <iostream>

using namespace std;

int main()
{
    int x = 10, y = 20;
    cout << "Min = " << MIN(x,y) << endl;

    return 0;
}
```

The format for a preprocessor function declaration consists of a the identifier name followed by parentheses containing the function's argument.

###Important: Do not leave any space between the name and the parentheses. 

The function definition is then embedded  within another set of parentheses.

The drawback of using macro functions is that it does not perform any typechecking.

Man macros sure have a lot of dangers! You may be wandering, why even use them? You could have made a safer min function using templates and it would be safer and typechecking would never be a problem.

Althought templates are more safe, there is a time and place where macros can come in handy.

Another place to use macros is you can define a foreach macro to make your code look more readable.

```
#define foreach(list, index) for(index = 0; index < list.size(); index++)
```

```
foreach(cookies, i)
    printf("Cookie: %s", cookies[i]);
```

##Templates vs. Macros

Aren't templates the same as macros besides being cleaner and easier to look at? They literally do the same thing! 

######*Macros substitute text definition into the code. They are strings that the compiler replaces with the defined value.

Well, first of all, macros literally just copy and paste the text into your code. 
One problem that arises when that happens is that if you want to post-increment a variable in the parameters, then the value is incremented however many times the variable is present in the macro. With templates, that problem is not apparent.

For example:
```
#include <iostream>

using namespace std;

#define max1(a, b) (((a)>(b)) ? (a):(b))
int main()
{
	int x=5;
	int y=max1(x++,4);
	cout << x << endl;
}
```
The code above would put `x++` and `4` in place of `a` and `b`:
```
((x++)>(4)) ? (x++):(4))
```
Because `x++` is in the function twice, it would be incremented twice, leading the output to be
```
7
```

With templates:
```
#include <iostream>

using namespace std;
template <typename TYPE>
TYPE max1(TYPE a, TYPE b){
    return (((a)>(b))?(a):(b));
}
int main()
{
        int x=5;
        int y=max1(x++, 4);
        cout << x << endl;
}
```
This time the code prints out
```
6
```

If we were to look at the value of **y** in these functions, the template function would still return a 5 because the **x** value is incremented AFTER the function executes.

With the macro, the **y** value would be 6 because **x++** replaces **a** once before it is returned to **y**.

##Templates are easier to debug with!

First off, there is no way for macros to check parameter types. That could already be the source of a number of bugs in your program. As explained above, templates don't have this problem.

For macros, during debugging, the messages will refer to the expanded macro instead of the definition. Since macros are expanded in the preprocessor, the compiler tends to not see them. **This can make the debugging process much harder because the function cannot be seen in the debugging process**
Templates, however, will point to the exact location of the problem!

The last thing about macros is that they cannot be stepped into with a debugger like gdb. Since they are based on text substitution, there isn't a way for them to be stepped into because they are not quite functions.



##Conclusion
By now, I hope that you have a good enough understanding of templates to use it on your own. Even though you may end up never using it, it is important to understand the structure of templates as you may see them in other programs.

Just like programming, take templates one step at a time. Try not to dive in too deep and make a complicated program with templates. Doing so while you're still inexperienced may lead to seeing those hard to understand compiler errors. Even with simple templates, you may still run into compiler errors. However, fixing those errors will allow you to be more comfortable with templates.
