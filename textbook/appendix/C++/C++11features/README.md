#Convenient C++11 Features for Student Programmers

##Highlighted C++11 Features  

* initialization lists  
* range-based for statement  
* auto type  
* trailing return type and decltype  

##How to Use C++11 Features  

Since its standardization in 2011, standard shipping compilers have included support for various C++11 features, depending on the compiler and version. For instance, GCC 4.3 and later support C++11 features by including a flag `-std=c++0x` to your `g++` command line. GCC 4.7 and later support use of the `-std=c++11` flag, as well.  

###C++0x? I thought this write up was about C++11.  

Actually, the terms C++0x and C++11 can be used interchangeably, and as the flag suggests, they represent the same standard C++. During development of C++11 the year of release had yet to be determined, so C++0x was the temporary name given to C++11.  

## Initialization Lists  

###How can I use initialization lists?  

If a compiler supports C++11 features, it likely supports initialization lists. GCC 4.4 and later versions support this feature.  

###What is an initialization list?  

An initialization list is exactly what it sounds like--an explicitly stated list of values to initialize a containing object with. Initialization lists were accepted prior to C++11 when initializing arrays, but now, the mechanism for accepting curly-bracket-enclosed lists is a function, often a constructor, accepting an argument of a new template class type `std::initializer_list<T>`, where `T` is a simple data type. `T` represents the same simple data type that makes up the data type of each element within the curly brackets, and the elements that make up the initializer list are separated by commas. The initializer list can be empty. 
In C++11, the STL containers and string class contain initializer-list constructors and support initialization lists. So, with the convenience of C++11 initialization lists, we can now initialize a vector of strings without repetitive calls to the vector `push_back` member function. This code is accepted in C++11:  

```  
#include <iostream> 
#include <string> 
#include <vector> 

using namespace std; 

 int main() 
{  
        vector<string> a = {"my", "init", "list"}; 
        int size = a.size(); 

        for(int i = 0; i < size; i++) 
        { 
                cout << a[i] << " "; 
        } 
        cout << endl; 
        return 0; 
}  
```  

## Range-Based For Statement   

When learning the C++ language, a common, dangerous pitfall for many novice programmers when using a conditional `for` statement occurs when a target block of memory is over-indexed and the program attempts to manipulate or read data outside the boundaries of the target block. C++11 is kind to neglectful (or lazy) programmers by providing new support of the `for` statement with the boundary protecting range-based for statements.  

###How can I use a range-based for statement?  

Unfortunately, range-based for loops have delayed support in standard compilers. For instance, only GCC 4.6 and later versions support range-based for loops and your code will result in compilation errors and undesired results if used on incompatible versions.  

###When do I use a range-based for statement?  

You should consider using a range-based for statement whenever your for statement relies on iterating through each element of a valid range expression. Continue reading for accepted range expressions.  

###Syntax for a Range-For Statement  

A range-for statement can come in one of two forms:    
`for ( for-range-declaration : range-expression ) loop-statement`  
and    
`for ( for-range-declaration : braced-init-list ) loop-statement`  

In both forms, the for-range-declaration consists of a declaration of a variable of the same data type or of a reference of the same data type as the data type of each element in the range-expression (and can also be specified as `const` if desired).  
For example, if the for statement involves iterating through a vector of `int`s, then, if each element of the vector is to be read but not changed, the for-range-declaration could be a declaration of a variable of type `int`, such as `int elem`, or of a constant reference of type `int`, such as `const int &elem`  
In this same example, if the purpose of the `for` statement is to manipulate the data of the `int` elements, the for-range-declaration would be declared as a reference to an `int`, such as `int& elem`.  
If providing an explicit list of elements to index consecutively, use the second form of the range-for statement by providing the explicit list in curly brackets, much like the syntax for initialized lists.  
An example of a for-range statement with a braced-init-list:  

``` 
#include <iostream>  
using namespace std;  
int main()  
{  
	for (const int &elem : {0,2,4,8,16,32})  
		cout << elem*2 << ' ';  
	cout << endl;  
	return 0;  
}  
```  

will produce the following output:  
`0 4 8 16 32 64`  

Otherwise, if dealing with a range expression, ensure the range expression is valid, in that it has a defined range for the compiler to interpret. Valid range expressions include iterable data structures, such as STL containers (e.g. vectors and lists), strings (class string), and arrays. If the range expression does not have a well-defined range, the program is ill-informed and the range-based for statement will not implement as expected.  
Let us look at the previous example code, but with a valid range expression instead of a braced-init-list:  

```  
#include <iostream>  
#include <vector>  
using namespace std;  
int main()  
{  
	vector<int> container = {0,2,4,8,16,32};
	for (const int &elem : container)  
		cout << elem*2 << ' ';  
	cout << endl;  
	return 0;  
}  
```  

will produce the same output:  
`0 4 8 16 32 64`  

Notice how our example from initialization lists incorporates for statement relying on a vector, which is an STL container with a defined range.  Let us change the example from the section on initialization lists to use a range-based for loop:  

```  
int main()  
{  
	vector<string> container = {"my", "init", "list"};  
	for (string elem : container)
		cout << elem << ' ';
	cout << endl;  
	return 0;  
}  
```  

This will produce the output:  

`my init list`  

Now notice a call to the vector member `size` was not necessary when using the range-based for statement in this example.  

##Auto  

###Huh?  

Auto? As in the storage class specifier? Am I missing something here? Auto is nothing new...?  
Okay, so `auto` may not be a new term to the C++ language, but with C++11, the previous definition of auto is thrown out, no longer recognized, and if you continue using auto as before, you will be met with compilation errors.  

###How can I use the C++11 auto?  

The auto feature is accessible by standard compilers that accept C++11 features. GCC 4.4 and later versions can handle the auto feature.  

###So, what is auto in C++11?  

In C++11, auto is a type-inferred data type, in that the data type of the variable is deduced by the compiler upon initialization or upon later inspection (e.g., when used as a function return type, which we will address soon.)  
A general definition of `auto` can be explained as:  
`auto x = expression;`  
here, `auto` infers the resulting data type from `expression` and initializes the variable `x` with the same value and data type returned by `expression`.  

Let us look at some simple uses for auto to better understand how this type works. Looking at the sample initializations, we can see cases where auto is used correctly and incorrectly:  

```  
auto a = 10; // auto is an int type
auto b = 30LL; // auto is a long long type  
int& c();
auto d = c(); // auto is an int type  
auto& e = c(); // auto is an &int type  
const auto f = 'a'; //auto is a const char type  
auto g; // error: auto relies on initialization
vector<auto> h = {"my", "strings"}; //error, auto cannot be a member variable
auto i = { 2,3.0,4 }; // error, cannot determine which data type to deduce
```  

###What are some limitations of `auto`?  

First, the name of the variable being declared with `auto` cannot appear anywhere in the initializer expression--a type cannot be deduced from a variable with no yet-assigned type.  Also, auto is limited to being used when declaring variables in namespace scope, in block scope, and in for-init-statements, as talked about in range-based for statements.  Also, as seen in the example code above, auto cannot be used for class member variables.  

###What are the advantages of using auto?  

So, why and when should you prefer `auto` to explicit data types?  
First, one should be ensured that `auto` is a secure data type, in that `auto` can be trusted to be just as strongly typed as other data types--once a variable is initialized with `auto`, the type is deduced, and the variable cannot be used as another type from then on.  
A common use for `auto` is writing code that is easy to read, and therefore, easy to maintain. This is especially true when declaring variables with long, complicated data types--an occurrence often encountered when using maps and iterators. For instance, take a look at this common C++ declaration prior to C++11:  

```
vector<string> container;
vector<string>::iterator iter = container.iterator();
```  

Gross! By incorporating `auto`, let us see how this cringe-worthy code can be much more reader-friendly:  

```  
vector<string> container;
auto iter = container.iterator();
```  

Better, no? Much easier on the eyes, for sure!  
Another instance for when using auto may be advantageous is when declaring a variable with a type to be determined by a call to a function. 

```  
auto x = foo(parameter1, parameter2);
```  

Here, the variable `x` accepts its data type from the return type of the function `foo`. This is particularly useful in that even if the function is altered to return a different data type, the data type for variable `x` does not need to be explicitly changed.  
Speaking of function return types, what if we wanted to determine our return type later by deduction with auto? Is that possible? Well, with C++11, it is!  This brings us to our discussion of trailing return types and `decltype`.  

##Trailing Return Types and Decltype  

**Note:** `decltype` is a recently added C++11 feature and relies on GCC 4.8.1 version and later.  

Our analysis of the C++11 auto type now brings us to the discussion of trailing return types and `decltype`. Prior to C++11, the return type of a function had to be declared right away in the beginning of the function declaration--whatever type is returned from a function must be explicitly stated. This is no longer true with C++11, so long as the function incorporates correct syntax for a trailing return type to be deduced.  
To get a better understanding of the need for trailing return type syntax and `decltype`, let us look at a simple function with no trailing return type syntax and transform the function to allow type deduction of the return type. Consider the following function declaration:  

`double add(double dbl1, int int1);`  

Now say we want to deduce the return type using `auto`:  

`auto add(double dbl1, int int1);`  

Here, we have a problem because the compiler cannot infer the type of auto. If we want to be able to use `auto` here, we have to inform the compiler of our returning type by using trailing return syntax. For our example, this is the syntax for adding a trailing return type our `add` function:  

`auto add(double db1, int int1) -> double;`  
Now, we have specified `double` as our return type. But this does not make good use of our `auto` type, as we are explicitly defining our type to `double`.  
Now, we can introduce `decltype`. Like `auto`, `decltype` is a type specifier that deduces its type by a given expression, and acts very much like auto. Let us now incorporate `decltype` into our example function, this time presenting the function body:  

```  
auto add(double dbl1, int int1) -> decltype(dbl1 + int1)  
{  
	return dbl1 + int1;
}  
```  

Now, this code will work perfectly fine in C++11. Keep in mind that `->decltype(dbl1 + int1)` makes up the trailing return type, and note that when using a trailing return type in a function, the return type of the function must be `auto`, and similarly, if `auto` is the return type of a function, a trailing return type is necessary.  

##Sum it Up  

Ok, so maybe C++11 features take a little getting used to, but it would not be C++ otherwise! I believe one can save themselves quite a few headaches down the road if one relies on good practice of utilizing safe C++11 features when coding, and with repetitive use of these features, they can become almost second nature, as any other well-practiced coding style. A computer scientist must always be looking to learn and adapt to maintain their level of excellence as a programmer, and taking on new C++11 features is not a bad start. 

##Credit  

For technical details support, I referred to the C++11 FAQ by Bjarne Stroustrup and the latest draft of the C++11 standard.  

