#Templates and You

Templates are indeed quite difficult to learn at first, but if you put the time and effort into them, you can increase your programming efficiency. The pros outweigh the cons!

##Taking Functions One Step Further
Functions are already useful on their own. They allow you to reuse the same code without writing it again. However, they have some limitations such as dealing with multiple data types.

Have no fear, templates are here!

##What's a template?
Let's write a function that doubles a number, **double_num**, with a template:
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
tells the compiler: _Hey, this is a template!_

```
cout << double_num(3) << endl;
cout << double_num(3.17) << endl;
```
The compiler will see that you are calling a function-template and would create two functions:
```
int double_num(int x)
double double_num(double x)
```
This process is called specialization.
When you run the program, you will get exactly what you wanted:
```
6
6.34
```
We have just successfully used a template! It wasn't that hard was it?

Before, we would have needed to write two functions (with the same code in it!), but for different data types.

```
int double_num(int x){
    return 2*x;
}
double double_num(double x){
    return 2*x;
}
```

##Case Study: Vectors
As stated before, templates are only as complicated as you make them. Templates can be used for simple functions (like the one we just made) to classes with member functions.

You may have been using templates without even noticing it! The Standard Template Library provides many containers. For example, **vectors** can be used to store any type of data type. This is because they use templates!

Let's take a look at vectors:
```
template < class T, class Alloc = allocator<T> > class vector;
```
First off, you may have noticed something different about this template. Here, `class` is used instead of `typename`. There is no difference. Usually people use `class` because it is shorter and others use `typename` because it sounds more generic.

If you're familiar with vectors, then the first parameter should be understandable. `class T` is the type of data you are storing in the vector (such as `int` or `string`).

If you wanted a vector of doubles, then you would declare it like so:
```
vector<double> numList;
```
Vectors actually have a second parameter that isn't talked about often.
```
class Alloc = allocator<T>
```
The second parameter is an allocator class that defines how memory will be allocated if the vector needs more memory. 

An allocator is a class with member functions **allocate** and **deallocate**. It also has helper functions for manipulating the memory that it allocated and typedefs that describe how to refer to the memory (names for pointer and reference types). If an STL container allocates all of its memory through a user-provided allocator (which the predefined STL containers all do), you can control its memory management by providing your own allocator.

For example when using `push_back`, eventually the vector would need more space. This is where the allocator works to make space for the new values. The allocators are used to handle memory allocation and deallocation. Depending on the kind you use, you can see greatly improved performance. In most cases, you wouldn't need to worry about it because it is set by the default allocator class template. This is because it is a part of a **default template argument**.

Default template arguments are specified in the parameter lists after the `=` sign. Defaults can be specified for any kind of template parameter (type, non-type, or template), but not to parameter packs.

If the default is specified for a template parameter of a primary class template, each subsequent template parameter must have a default argument, except the very last one may be a template parameter pack. In a function template, a parameter pack may be followed by more type parameters only if they have defaults or can be deduced from the function arguments.

However, in certain situations, you would want the vector to use a different type of method of allocating memory, such as programming for machines that have small memory.

Wow! Templates sure are convenient! So now we can use any type in our functions and it’ll be fine right?

Wrong. Let's say we wanted to implement our own stack class and compare two of them:
```
template <class T>
class myStack
{
	private:
		vector<T> data;
	public:
		myStack();
		~myStack();
		void push(T value);
		T top();
		void pop();
		bool empty();
};
//stack function implementation goes here.
template <typename T>
bool isSame(T data1, T data2)
{
    return (data1==data2);
}
int main()
{
    myStack<int> a;
    myStack<int> b;
    a.push(3);
    b.push(4);
    bool yes=isSame(a, b);
}
```
You’ll get a whole host of nasty compilation errors. Near the top of the error list it will say something like this:
```
tests.cpp:11:14: error: no match for ‘operator==’ (operand types are ‘myStack<int>’ and ‘myStack<int>’)         return (data1==data2);
                 ^
```
This is because there's no relational operators for `myStack`. Similar things happen with other missing constructors. Normally this would not be much of a problem when using STL containers because STL's implementations have account for relational operators. This becomes a problem when using custom objects or your own implementations. You can fix this by writing constructors for these operators in your implementations or by using specialization in the templated function.

Let’s try something different. We’ll have a function called `setNothing` where the data type will be set to NULL. 
```
template <typename T>
void setNothing(T& data)
{
    data = ’\0’;
}
template <typename T>
void setNothing<string>(string& data)
{
    data = "";
}
```
As we know, setting a string to ’\0’ will give an error. So what we can do instead is specialize the function for the string type and avoid the logic error.  Isn’t that useful?

In summary, the Standard Template Library uses templates to allow programmers to use the containers with flexibility. But one of the things you have to watch out for is if there are missing constructors in certain data types when using them in a template.

###Class Templates

So far we’ve gone over how to use templates in normal functions, but what about when we want to define an abstract container that is adaptable? In one example above, we briefly cover class templates with multiple parameters.

Usually classes are used to represent data as abstract objects and have functions that can manipulate that data. Class templates come in handy when you need similar functions for another kind of data type.

To turn a class into a template, we simply replace all occurrences of `int` with the template name and add the template parameter at the top just like you would for a function.
```
template <class type>
class Object
{
     type data;
public:
    Object() : type()        //don’t hardcode the 0 and set type to default value
    {}
    void data(type x)
    {
        data = x;
    }
    type getdata() const
    {
        return data;
    }
    void print()
    {
        cout << data;
    }
};
```
Unlike function templates, class templates don’t use arguments to figure out the template type. Instead, you would have to pass in the template type inside the angular brackets during instantiation like this:
```
Object <int> myobject;
```
As we can see, class templates allow us to create abstract objects with unique behavior that are reusable for multiple types.
These attributes are very useful for creating abstract data structures with specific functions such as queues, stacks, and maps.

##Multiple Types with Class Templates
You can declare templates with as many types as you would like.
```
template<class Type1, class Type2>
struct Pair
{
    // In public area, since we want the client to use them directly.
    Type1 first;
    Type2 second;
};
```
This template allows you to use different types for different parts of the class.
```
Pair<int, double> Total;

Total.first = 488;
Total.second = 9.4868329;
```
Templates are as complicated as you want to make them.
If you want to use a template for a more sophisticated function, then the writing the template for the function might get a little messy.

For example:
As we have said before, templates require specialization to account for missing constructors when dealing with certain data types. One data structure that tends to use another template class in its implementation is the map.

The STL implementation of maps takes a key type as a first parameter and a data type as the second. Usually what happens is that the key is used to access the value in a map just like how an array uses an index to reference a value.

The problem is that the key doesn’t always have to be of type `int` so we would have to write another constructor to access the values. The solution for STL maps is that they have use a Pair class template to group the key type and the value type together like this:
```
template <class key, class T>
class map
{
    typedef pair<const Key, T> value_type;
    public:
    /* miscellaneous code*/
private:
    /*more code*/
};
int main()
{
    map<string, int> employee_number;
    employee_number[“Michael”]=5023;
```
The instantiation of the map in the code above includes a key type of string and a value type of int. In the second line, the number for index **Michael** is set to **5023**. These two types are paired together in the Pair class template.

As we can see, templates tend to make certain implementations easier to write and understand because there is less clutter to look at.

##Ok, so why should I use them?


As mentioned above, class templates can be used for creating objects with unique behavior that are adaptable.
Let's say we want to implement a generic stack class:
```
template <class T>
class Stack{

private:
    vector<T> data;

public:
    bool Empty();
    void Push(const T& data);
    const T& Top();
    void Pop();

};

```
A stack is an abstract container that only manipulates the last value whether it is adding or removing values. Without templates, the stack class wouldn’t be able to apply this behavior to different types.
As you can see, using templates is crucial when implementing containers because normal functions would not be able to handle multiple types.

Templates are easier to write and understand because you are implementing the code once for various types instead of writing almost identical code multiple times.

Overall, templates tend to keep things neater and easier to understand while giving functions and classes flexibility.

###What about macros?

Another code generation tool are Macros. Macros come from C while templates are from C++. Unlike templates that run at compile time, macros are a more primitive type and are parsed by the preprocessor which only replaces text.

Since templates run at compile time, they take more time to build but are safer (more on this later).

There are two types of macros: “Object-like” macros that take no arguments, and “function-like” macros that can be defined to accept arguments. To specify an Object-like macro, you would write #define followed by an identifier name and a string or numeric. When the preprocessor sees this it will substitute each occurrence of that macro in source code.

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

Note how the identifier name are always all upper case. It is not required but it is convention. Also note how the NAME macro has quotations around Greg.

Every time `NAME` appears in the program, the preprocessor will substitute it with "Greg". If the quotes were not there then that would lead to a syntax error.

Here is what the compiler error looks like when you forget the quotes on Greg in the macro definition:

macros.cpp:8:27: error: use of undeclared identifier 'Greg'
        cout << "My name is " << NAME << " and i am " << AGE << endl;
                                 ^
macros.cpp:1:14: note: expanded from macro 'NAME'
#define NAME Greg
             ^
1 error generated.



You can use #define to make function-like macros as well. Since macros do not generate actual function calls, you can sometimes make programs run faster by replacing function calls with macros.
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

The format for a preprocessor function declaration consists of an identifier name followed by parentheses containing the function's argument.

Important: Do not leave any space between the name and the parentheses.

The function definition is then embedded within another set of parentheses.

The drawback of using macro functions is that it does not perform any type checking. In C++, an inline function is a safer and often preferred method.

Here is how you would call the min as an inline function:
```
inline int min(int a, int b){  return ((a>b)?b:a); }
```

Man macros sure have a lot of dangers! You may be wondering, why even use them? You could have made a safer min function using templates and it would be safer and type checking would never be a problem.

Although templates are safer, there is a time and place where macros can come in handy.

Another place to use macros is you can define a `foreach` macro to make your code look more readable.

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

For macros, during debugging, the messages will refer to the expanded macro instead of the definition. Since macros are expanded in the preprocessor, the compiler tends to not see them.

Let’s say that a macro is defined on line 14 but is called upon in line 400. When using a debugger the problem will be shown on line 400 in expanded form.
**This can make the debugging process much harder because the function cannot be seen in the debugging process**
Templates, however, will point to the exact location of the problem!

The last thing about macros is that they cannot be stepped into with a debugger like gdb. Since they are based on text substitution, there isn't a way for them to be stepped into because they are not quite functions.



##Conclusion
By now, I hope that you have a good enough understanding of templates to use it on your own. Even though you may end up never using it, it is important to understand the structure of templates as you may see them in other programs.

Just like programming, take templates one step at a time. Try not to dive in too deep and make a complicated program with templates. Doing so while you're still inexperienced may lead to seeing those hard to understand compiler errors. Even with simple templates, you may still run into compiler errors. However, fixing those errors will allow you to be more comfortable with templates.


