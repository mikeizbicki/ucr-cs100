# C++14 New Language Features
The C++14 standard is intended to be a minor revision of the C++ Standard adding minor improvements to the standard.
This tutorial highlights the changes that will have the most significant impact on your programming along with working examples of when and why you would employ the features.
These features include:

* Return Type Deduction ([example](./returntypedeductionexample.cpp))
* Variable Templates ([example](./variabletemplatesexample.cpp))
* Tuple Addressing by Type ([example](./tupleaddressingexample.cpp))

### Return type deduction
Introduced back in C++11, the auto keyword for variables specifies that the type of the variable that is being declared will be automatically deduced from it's initializer.<br />
This means you can do things like:
```c++
double a = 2.5;
auto x = 2 * a; // x is initialized to type double
```
Here, the expression `2 * a`, which is used to initialize the variable `x`, returns a value of type `double`.
`auto` is then able to specify that the type of the variable is `double`.

A similar form of type deduction can be used in the declaration of `for` loops.<br />
For example:
```c++
std::vector<int> v = { 2 , 3 , 5 , 7 }
for(std::vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter) {
	std::cout << *iter << std::endl;
}
```
The auto type specifier can be used in the initialization statement of the `for` loop.
This prevents you from having to repeat yourself when writing your code.
```c++
std::vector<int> v = { 2 , 3 , 5 , 7 }
for(auto iter = v.begin(); iter != v.end(); ++iter) {
	std::cout << *iter << std::endl;
}
```
Here `auto` is able to infer, from the return type of `v.begin()`, that the
variable `iter` is of type `std::vector<int>::iterator`.

C++11 extended the auto type specifier to functions, allowing the return type of the function to be deduced from its return statements.
A function of the form `auto function -> return type` could take advantage of the `auto` keyword but the function still had to have the trailing return type at the end of the function declaration in order for type deduction to take place.
```c++
auto add(double a, int b) -> decltype(a + b) // the return type is the type of operator+(double, int)
{
	return a + b;
}
```

##### The auto keyword for all functions
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
For Example:
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
		return(n * factorial(n-1)); // calling this now will not cause error
	}
}
```
This function will execute returning a value of type int.

### Variable templates
C++14 also generalizes another previously introduced feature of the language.
Expanding on the use  of templates from functions and classes to `constexpr` variables allows for the declaration of templated variables.

For Example, declaring the variable pi using templates allows for the accuracy to depend on the type passed in to pi.
```c++
template<class T>
constexpr T pi = T(3.1415926535897932385);  // variable template
```
With this declaration of the variable `pi`, a statement like `pi<int>` would return the integer `3`.
Similarly passing in a `double` to the variable `pi` will result in `pi` returning its value to double precision.
This acts as a "cast" to the type of the argument passed in.

### Tuple Addressing by type
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

### Conclusion
C++14 was intended to be a minor update to the standard improving mainly on readability and practicality.
More in depth examples are available in the example folder.
All of the code can be compiled with the `-std=c++1y` option.