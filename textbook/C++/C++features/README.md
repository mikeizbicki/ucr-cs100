#Convenient C++ Features in C++11 and C++14 for Student Programmers
C++11 and C++14 are recent standards that have extended the language's functionality and readability.
While learning the basics of C++, students may not have the opportunity to explore these new standards and the features they add.
This writeup is aimed at explaining some features that may reduce tedium and increase readability of the code.

##Highlighted C++11 Features  

* initialization lists  
* range-based for statement  
* auto type  

##Highlighted C++14 Features

* Return Type Deduction ([example](./returntypedeductionexample.cpp))
* Variable Templates ([example](./variabletemplatesexample.cpp))
* Tuple Addressing by Type ([example](./tupleaddressingexample.cpp))

#C++11 Features

## Initialization Lists  

An initialization list is exactly what it sounds like--an explicitly stated list of values to initialize a containing object with.
Initialization lists were accepted prior to C++11 when initializing arrays, but now they can be used for other data structures.
The mechanism for accepting curly-bracket-enclosed lists is a function, often a constructor, accepting an argument of a new template class type `std::initializer_list<T>`, where `T` is a simple data type. 
`T` represents the same simple data type that makes up the data type of each element within the curly brackets.
The elements that make up the initializer list are separated by commas.
The initializer list can also be empty. 
In C++11, the STL containers and string class contain initializer-list constructors and support initialization lists.
So, with the convenience of C++11 initialization lists, we can now initialize vectors without repetitive calls to the `push_back` member function.
The following code is now accepted in C++11:  

```  
#include <iostream> 
#include <string> 
#include <vector> 

using namespace std; 

 int main() 
 {  
		vector<string> a = {"my", "init", "list"}; 
		vector<int> b = {1, 2, 3, 4, 5};

		//More code...

 	    return 0; 
 }  
 ```  

## Range-Based `for` Loops   

When learning the C++ language, a common, dangerous pitfall for many novice programmers when using a conditional `for` loop occurs when the program tries to access a block of memory that is "out of bounds".
This usually leads to a frustrating segfault or compiler error, but may lead to more devious behavior by the program that may be difficult to debug.
C++11 is kind to neglectful (or lazy) programmers by providing new support of the `for` statement with the boundary protecting range-based `for` loops.  

###When do I use a range-based for statement?  

You should consider using a range-based for statement whenever your for loop relies on iterating through each element of a valid range expression.
Continue reading for accepted range expressions.  

###Syntax for a Range-For Statement  

A range-for statement can come in one of two forms:    
`for ( for-range-declaration : range-expression ) loop-statement`  
and    
`for ( for-range-declaration : braced-init-list ) loop-statement`  

In both forms, the for-range-declaration consists of a declaration of a variable of the same data type or of a reference of the same data type as the data type of each element in the range-expression (and can also be specified as `const` if desired).  
For example, if the for statement involves iterating through a vector of `int`s, then, if each element of the vector is to be read but not changed, the for-range-declaration could be a declaration of a variable of type `int`, such as `int elem`, or of a constant reference of type `int`, such as `const int &elem`  
In this same example, if the purpose of the `for` statement is to manipulate the data of the `int` elements, the for-range-declaration would be declared as a reference to an `int`, such as `int& elem`.  
If you want to provide an explicit list of elements to index consecutively, use the second form of the range-for statement by providing the explicit list in curly brackets, much like the syntax for initialized lists.  
Here is an example of a for-range statement with a braced-init-list:  

``` 
#include <iostream>  
using namespace std;  
int main()  
{  
		for (const int &elem : {0,2,4,8,16,32})  
		{
				cout << elem*2 << ' ';  
		}
		cout << endl;  
		return 0;  
}  
```  

will produce the following output:  
`0 4 8 16 32 64`  

Otherwise, if dealing with a range expression, ensure the range expression is valid, in that it has a defined range for the compiler to interpret.
Valid range expressions include iterable data structures, such as STL containers (e.g. vectors and lists), strings (class string), and arrays.
If the range expression does not have a well-defined range, the program is ill-informed and the range-based for statement will not implement as expected.  
Let us look at the previous example code, but with a valid range expression instead of a braced-init-list:  

```  
#include <iostream>  
#include <vector>  
using namespace std;  
int main()  
{  
		vector<int> container = {0,2,4,8,16,32};
		for (const int &elem : container){ 
				cout << elem*2 << ' '; 
		}
		cout << endl;  
		return 0;  
}  
```  

will produce the same output:  
`0 4 8 16 32 64`  

##Auto    

Before the C90 standard, `auto` was used to declare a variable with automatic storage duration (i.e. "on the stack").
Since then, automatic storage duration has been the default for a local variable, rendering the old `auto` useless.
Now C++11 has given `auto` a whole new meaning.

###So, what is `auto` in C++11?  

In C++11, `auto` is a type-inferred data type, in that the data type of the variable is deduced by the compiler upon initialization or upon later inspection (e.g., when used as a function return type, which we will address soon.)  
A general definition of `auto` can be explained as:  
`auto x = expression;`  
Here, `auto` infers the resulting data type from `expression` and initializes the variable `x` with the same value and data type returned by `expression`.  

Let us look at some simple uses for auto to better understand how this type works. 
Looking at the next few examples, we can see cases where auto is used correctly and incorrectly:  

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

First, the name of the variable being declared with `auto` cannot appear anywhere in the initializer expression--a type cannot be deduced from a variable with no yet-assigned type.
Also, auto is limited to being used when declaring variables in namespace scope, in block scope, and in for-init-statements, as talked about in range-based for statements.
Also, as seen in the example code above, auto cannot be used for class member variables.  

###What are the advantages of using auto?  

So, why and when should you prefer `auto` to explicit data types?  
First, one should be ensured that `auto` is a secure data type, in that `auto` can be trusted to be just as strongly typed as other data types
Once a variable is initialized with `auto`, the type is deduced, and the variable cannot be used as another type from then on.  
A common use for `auto` is writing code that is easy to read, and therefore, easy to maintain. This is especially true when declaring variables with long, complicated data types--an occurrence often encountered when using maps and iterators. 
For example, iterating through a vector of vectors of `ints` in a `for` loop creates code that is sure to bring about headaches:  

```
vector<vector<int> > container;

//Fill the container...

for (vector<vector<int> >::iterator it = container.begin(); ...)
{ ... }
```  

By incorporating `auto`, let us see how this cringe-worthy code can be much more reader-friendly:  

```  
vector<vector<int> > container;
for (auto it = container.begin; ...)
{ ... }
```  

The result is code that is easier to read and easier to write.

Another instance for when using `auto` may be advantageous is when declaring a variable with a type to be determined by a call to a function. 

```  
auto x = foo(parameter1, parameter2);
```  

Here, the variable `x` accepts its data type from the return type of the function `foo`.
This is particularly useful in that even if the function is altered to return a different data type, the data type for variable `x` does not need to be explicitly changed.  

##Sum it Up  

Ok, so maybe C++11 features take a little getting used to, but it would not be C++ otherwise!
You can save yourself quite a few headaches down the road if you rely on good practice of utilizing safe C++11 features when coding.
With repetitive use of these features, they can become almost second nature, as any other well-practiced coding style.
A computer scientist must always be looking to learn and adapt to maintain their level of excellence as a programmer, and taking on new C++11 features is not a bad start. 

##Variadic Templates
A variadic template is a template, which can take an arbitrary number of template arguments of any type.
This can be used with classes as well as functions.
Here's an example of a variadic class template:

```
template<typename... Parameters>
class VariadicTemplate;
```
This template can be used to create an instance of this class in the following ways:

```
VariadicTemplate<int, double> instance;
VariadicTemplate<long, bool, string> instance;
VariadicTemplate<vector<double>, string, char, bool, vector<int>>;
```

This feature can become a bit involved and most of the technical details are out of the scope of this tutorial.
However, you are encouraged to read up more on the topic.

# C++14 New Language Features
The C++14 standard is intended to be a minor revision of the C++ Standard adding minor improvements to the standard.
This portion of the writeup highlights the changes that will have the most significant impact on your programming along with working examples of when and why you would employ the features.
These features include:

* Return Type Deduction ([example](./returntypedeductionexample.cpp))
* Variable Templates ([example](./variabletemplatesexample.cpp))
* Tuple Addressing by Type ([example](./tupleaddressingexample.cpp))

## Return type deduction

C++11 extended the auto type specifier to functions, allowing the return type of the function to be deduced from its return statements.
A function of the form `auto function -> return type` could take advantage of the `auto` keyword but the function still had to have the trailing return type at the end of the function declaration in order for type deduction to take place.
```c++
auto add(double a, int b) -> decltype(a + b) // the return type is the type of operator+(double, int)
{
		return a + b;
}
```

### The auto keyword for all functions
C++14 extended the auto type specifier to all functions allowing them to deduce the return type based on the expression given to the return statement.
This is accomplished without the need of a trailing return type in the declaration.
Below is a simple example of a function using return type deduction this way:
```c++
auto eulerNo() { // deduced to return type of variable e
	double e = 2.718281;
	return e;
}
```
This function returns a `double` since the expression given to the return statement `e` is of type `double`.
A more involved example is one where `auto` is used instead on a templated function.
```c++
template <typename T, typename U>
auto multiply(T t, U u) { // deduced to return type of operator*(t,u)
  return t * u;
}
```
This results in a more complicated return type since the initial type is unknown until the function is actually used.
Ultimately, the return type of the function is inferred from the result of `t` and `u` multiplied together.

Combining these two types of examples can result in you being able to take advantage of type inference in a slightly more productive way.
```c++
template<typename T>
auto twoDeevec(int rows, int columns, T t) {
		vector<vector<T> > matrix;
		vector<T> vec;
		for(auto i = 0; i < rows; ++i) {
				for(auto j = 0; j < columns; ++j) {
						vec.push_back(j * i * t * t);
				}
				matrix.push_back(vec);
		}

		vector<vector<vector<T> > > matrixvec;
		matrixvec.push_back(matrix);

		return matrixvec;
}
```
The return type of this function is a 3D vector `vector<vector<vector<T> > >`.
A declaration like this one makes code cleaner and easier to read by removing some of the repetitiveness.

Recursion can also be used with a function of this type.
In order for this to work the recursive call must happen after at least one return statement in the definition of the function.
This is because the keyword is able to deduce the type based on the first return statement it comes across.
For example:
```c++
auto improperfactorial(int n)
{
		if (n != 0) {
				return(n * factorial(n-1)); // calling this now will cause error
		} else {
				return 1; // return type deduced as int
		}
}
```
This function will throw an error since there is no prior return statement.
```c++
auto properfactorial(int n)
{
		if (n == 0) {
				return 1; // return type deduced as int
		} else {
				return(n * factorial(n-1)); // calling this now will not cause error				 }
}
```
This function will execute returning a value of type int.

## Variable templates
C++14 also generalizes another previously introduced feature of the language.
Expanding on the use  of templates from functions and classes to `constexpr` variables allows for the declaration of templated variables.

For example, declaring the variable `pi` using templates allows for the accuracy to depend on the type passed in to `pi`.
```c++
template<class T>
constexpr T pi = T(3.1415926535897932385);  // variable template
```
With this declaration of the variable `pi`, a statement like `pi<int>` would return the integer `3`.
Similarly passing in a `double` to the variable `pi` will result in `pi` returning its value to double precision.
This acts as a "cast" to the type of the argument passed in.

## Tuple Addressing by type
C++11 introduced the `std::tuple` class, a fixed size container of values.
The `tuple` class was intended to be a generalization of the `std::pair` class.
Below is an example declaration of a `tuple` using an initializer list.
The examples mentioned in this section will use this declaration.
```c++
std::tuple<int, int, string> myTuple(1,2,"I am a String");
```
Accessing a tuple's element value by argument number has been possible since the introduction of the `tuple` container back in C++11.
```c++
cout << "First tuple int: " << std::get<0>(myTuple) << endl;
cout << "Second tuple int: " << std::get<1>(myTuple) << endl;
cout << "Tuple string: " << std::get<2>(myTuple) << endl;
```
The first statement, `std::get<0>(myTuple)`, returns the first element in `myTuple` which is the integer `1`.
The `tuple` holds elements similar to how `vectors` arrange their elements.
In general, a statement like `std::get<i>(tupleName)` would return the `i+1`th element in the `tuple`.

C++14 extends indexing an `std::tuple` by allowing a value in a tuple to be fetched by its type as well as its index.
Though if the tuple has more than one element of the type, a compile-time error will result.
This can be seen in the example below:
```c++
cout << "First tuple int by type: " << std::get<int>(myTuple) << endl;
```
The statement is ambiguous since there are two elements of type `int` in the `tuple`.
Generally, only attempting to access an element of a tuple that has two or more of that same element type will result in an error.
Below is a statement with less ambiguity:
```c++
cout << "Get tuple string element by type: " << std::get<string>(myTuple) << endl;
```
The statement, `std::get<string>(myTuple)`, returns "I am a string".
Since there is only one `string` in the `tuple`, the statements executes without error.

###Summary
Ok, so maybe these features take a little getting used to, but it would not be C++ otherwise!
You can save yourself quite a few headaches down the road if you rely on good practice of utilizing safe C++ features when coding.
With repetitive use of these features, they can become almost second nature, as any other well-practiced coding style.
A computer scientist must always be looking to learn and adapt to maintain their level of excellence as a programmer, and taking on new C++ features is not a bad start. 
More in depth examples are available in the example folder.
