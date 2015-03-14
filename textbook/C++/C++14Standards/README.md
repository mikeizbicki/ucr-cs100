# C++14 New Language Features

Known formally as the International standard ISO/IEC 14882:2014 Programming Language C++, C++14 is only a minor revision of the C++ Standard adding small improvements to the standard.
Of those improvements emphasis will be placed on:

* Return Type Deduction
* Binary Literals
* Digit Separators
* Variable Templates
* tuple addressing via type

Various minor updates have been added to the standard that make for cleaner code but more importantly also cut programming time.

### Return type deduction
Remember that thing that was introduced back in C++11?
That thing no one really understood?
Remember when everyone kept asking questions like "Whats auto?" and "How is that useful?".
Do you ever find yourself having to declare functions with return types like
`std::map<char,int>::iterator`, or something even more absurd like `vector<vector<pair<int,double> > >::forward_iterator`well those days are over.
I bring you...

##### The Auto.
Proposed by lazy good-for-nothing C++ programmers who thought shaving a bit of time and key-pressing  was more important than readability and clearness of code.
Thanks to them people like us get to enjoy time saving one-word answers to questions we might not even understand when writing our C++ functions.
What do I mean?

C++ extended the auto type to functions allowing them to deduce the return type based on the expression given to the return variable.

Example:
```
// simple function using return type deduction
auto foo() { // deduced to return int
	return 47;
}
```
This function would return an int since the expression given to the return statement `return 47;` is an int.

```
// a more omplicated return type since the initial types are unknown until
// function is used
template <typename T, typename U>
auto multiply(T t, U u) { // deduced to return type of (t * u)
    return t * u;
}
```
this function deduces the return type of two values multiplied together.

And finally the most convincing example:

```
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
The return type of this function is `vector<vector<vector<T> > >` though this example only slightly shows the power of the auto.
You can imagine what it can do with a function with a larger return type.

### Binary Literals
Previously C++ had support for Decimal, Hexidecimal, and Octal

##### Until Now...

Binary literals specified using the prefixes 0b or 0B are now supported in the language.

For example:
```
int AM = 0b11111001010;     // the number 1994 in binary using the 0b prefix
int CB = 0B11111000111;     // the number 1991 in binary using the 0B prefix
```
not specifying the prefix will result in the compiler defaulting to decimal.
This applies to all numeral systems

Binary literals can be used wherever an constant integral type is expected.

Example 1) comparison
The following code compares two binary numbers
```
cout << "100101 = " << 0b100101 << endl;
cout << "11001 = " << 0b11001 << endl;
if(0b100101 < 0b11001) {
	cout << "TRUE" << endl;
}
else {
	cout << "FALSE" << endl;
}
```
It prints to screen TRUE if the first is larger and false otherwise

### Digit Separators
The `'` Digit separator has been added to improve readability.
A single-quote character can be used arbitrarily as a digit separator in numeric literals.
Separators can be used to separate digits into thousands.
For example:
```
auto int_lit = 1000000;             // this is an example of an integer literal
									// with bo digit separators
auto int_lit_digseps = 1'000'000;   // this is the same number ad the one
```
Both int_lit_digseps and int_lit contain the same exact number: one-million

Digit separators can be extended to work for floating point literals as well and in general work for all number literal types including binary literals.

Below is an example of how digit separators can be used in floating point representations of numerals:

```
auto float_lit = 0.000153;
auto float_lit_digseps = 0.000'153;
```
and on binary representations of numbers
```
auto bin_lit = 0b010011000110;
auto bin_lit_digseps = 0b0100'1100'0110;
```
Digit separators are intended to improve code readability as they generally make numbers easier for human eyes to read since we are all used to seeing digits separated by thousands but they can be used arbitrarily and in no specific pattern.

For example
```
auto tenmilli = 10000000;
auto tenmilli_digseps = 1'0'0'000'00; // no specific pattern for digit
									  //separation
```

why we use digit separators?
The question is easily answered using another question:
which of the following is easier to read 478628904483 or 478'628'904'483?

Again, digit separators are meant to improve aesthetic readability.
They does not affect the numeric value.


### Variable Templates
C++14 Allows for the creation of templated variables.

Declaring the variable pi using templates allows for the accuracy to depend on the type passed in to pi.
For Example:

```
template<class T>
constexpr T pi = T(3.1415926535897932385);  // variable template
```

`pi<int>` would return the number Three.
Similarly passing in a double to pi would result in pi returning the value in double precision.

### Tuple Addressing via type
C++14 extends indexing an `std::tuple` introduced in C++14 by allowing a value in a tuple to be fetched by its type as well as its index.
Though if the tuple has more than one element of the type, a compile-time error will result.
This can be seen in the example below:
```
// A quick example on tuple addressing by type

// I - declaration to tuple using initializer list
std::tuple<int, int, string> myTuple(1,2,"I am a String");

// II - getting tuple element value by argument number (like in C++11)
cout << "First tuple int: " << std::get<0>(myTuple) << endl;
cout << "Second tuple int: " << std::get<1>(myTuple) << endl;
cout << "Tuple string: " << std::get<2>(myTuple) << endl;

// III - getting tuple element via type name (new in C++14)
cout << "Get tuple string element by type: " << std::get<string>(myTuple) << endl;

// VI - unable to get tuple int element by type because it is ambiguous
// comment out the line and the program will compile
cout << "First tuple int by type: " << std::get<int>(myTuple) << endl;

```

The statement was ambiguous since there were two int types in the tuple.
Also if the declaration of the tuple were instead
```
std::tuple<bool, int, string> myTuple(1,2,"myString");
```
A statement like
```
cout << "First tuple int by type: " << std::get<int>(myTuple) << endl;
```
Would print the number 2 to stdout

### Conclusion
C++14 was intended to be a minor update to the standard improving mainly on readability and practicality.
More in depth examples are available in the example folder.
All of the code was compiled with the `-std=c++1y` option for g++ compilers.
The original repository containing all of the examples with an example makefile can be found [here](https://github.com/Anthony1234567/Cplusplus14-standard).
