<!---
Fix examples, only put in the part of the examples in the writeup which are relevent to that part
Split up examples (ex: split up any into multiple example files)
--->
#Boost Libraries- Optional, Any, Variant
The point of the libraries `boost/optional`, `boost/any`,and `boost/variant` is to take the statically typed language C++ and make it similar to dynamically typed languages.
These libraries are useful because they allow for a variable to have varying types.

Statically Typed: The type of a variable is known at runtime.
The programmer must specify the type in the code.
Languages C, C++, and Java are statically typed.

Dynamically Typed: The type of a variable is interpretted at runtime, thus not specified by the programmer.
Languages JavaScript, Objective-C, and Python are dynamically typed.
<!---
Why should people care
--->
##How to Use
We first need to look at our [optional_temp.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/optional_temp.cpp) file which includes the boost libraries and uses the boost namespace.
```
#include <boost/optional.hpp>
#include <iostream>

using namespace std;
using namespace boost;
```
For the above just replace `<boost/optional.hpp>` with whatever boost type you're using.

##Boost.Optional
<!---
Begin with an example then explain it
--->
Uses library `<boost/optional.hpp>` and allows for optional return types.
This is done because Boost.Optional initializes a variable as empty but allows for a possible type change later.
This can be useful to use if you want to check if a function returns a valid value.

<!---
Change the below to an example
--->

Let's look at [optional_temp.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/optional_temp.cpp)

<!---
Replace this example with something else
--->
```
double deg;
optional<double> degrees()
{
	if(deg)
		return deg;
	else
		return optional<double>{};
}
```
Boost.Optional allows you to initialize your variable in the temperature function to empty, and if nothing is returned, then you know that temperature is empty.
The main function calls `degrees()` first without initializing `deg`, then after initializing `deg` with `-1`.
This will output:

```
$ g++ -std=c++11 optional_temp.cpp -o optional_temp
$ ./optional_temp
There is no temperature reported.
The temperature is -1 degrees.
```
`-1` is sometimes considered valid (such as when measuring temperature), but `-1` is also typically used to say when a function has failed. 
In the temperature example, we want `-1` to be a possible passing return value, so we'll use Boost.Optional to know when there is no temperature to measure.
<!---
Show commands to compile and run code
--->
<!---
is_initialized() -> will check to see if the boost::optional variable has been initialized. Can use it to know if it is possible to output.

Constructor takes two params. First is a conditional statement, second is a value. Ex/ return optional<int>{i%2 == 0, i}; if false will return optional<int>{}

make_optional() makes a new optional var. Similar to new

boost::optional get_value_or( , )    boost::get_optional_value_or( , ) if first param is initialized then will return that value else will return a default value specified as the second param
--->
##Boost.Any
<!---
You need to talk about the difference between dynamic and static typing. In particular, you should never use Any when it is possible to use auto.
--->
Uses library `<boost/any.hpp>` and allows for a variable that can be changed to any type in any portion of its scope.
<!---
Explain what variables it cannot use
-->
<!---
This is useful to use in place of `auto` because `auto` will assign a type to that variable from that point on, and Boost.Any will not. 
This takes up less memory (but the variable itself will take up more memory) because it enables you to reuse variables as different types instead of having to initialize new variables.
--->
<!--
and why
-->
###`any_cast`
`any_cast` is a `boost` function that applies a cast to a variable.
One thing `any_cast` is needed for is to output Boost.Any variables.
Boost.Any does not support `<<`, so you cannot use `cout` with anything involving `Any`.

<!--
(explain how var is currently set to a string and that it cannot `cout << boost::any_cast<int>(var) << endl;`)
-->

You can output multiple Boost.Any variables using `any_cast`.
These variables will output a value based on their type.
This can be seen in [any_mult.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/any_mult.cpp)
<!--
(explain different types)
(explain better, change wording)
-->
```
any var = 4;
cout << any_cast<int>(var) << endl;
var = string("hello world");
cout << any_cast<string>(var) << endl;
```
This will output:
```
$ g++ -std=c++11 any_mult.cpp -o any_mult
$ ./any_mult
4
hello world
```
Note: You will have to change the cast type depending on what type `var` is currently set to.
The cast assigns a type to `var` so the computer knows how to handle the variable.
The cast is necessary because Boost.Any assigns values to `var` at runtime so the code needs to be told what type it is dealing with beforehand since values can be interpreted in different ways.
<!--
Link to something explaining cast type
-->

For example, we can modify the previous example to become [any_add.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/any_add.cpp):
```
any var = 4;
cout << any_cast<int>(var) + any_cast<int>(var) << endl;
var = string("ho");
cout << any_cast<string>(var) + any_cast<string>(var) + any_cast<string>(var) << endl;
```
This will now output:

```
$ g++ -std=c++11 any_add.cpp -o any_add
$ ./any_add
8
hohoho
```
<!---
As you can see, the cast is very important in how the code ends up being executed.
--->
###`type_info`
Another important part of `Any` is `type_info` which can show what the type of a variable is which can be seen in the [any1.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/any1.cpp) example.

```
const type_info &ti = a.type();
cout << "type: " << ti.name() << endl;
if(a.type() == typeid(int))
	cout << any_cast<int>(a) << endl;
else if(a.type() == typeid(double))
	cout << any_cast<double>(a) << endl;
else
	cout << "The type of a is not an int or a double" << endl;
```
Main calls the above function where `a = 1` then `a = 3.65`  and this outputs:
```
$ g++ -std=c++11 any1.cpp -o any1
$ ./any1
type: i
1
type: d
3.65
```

The examples above show us how to use `boost::any`, but now we need to find a way to make `boost::any` useful.

###Vectors
At this point, you might be thinking that it would be easier to create separate variables so you don't have to worry about casting the types, so let's use Boost.Any with vectors.

As shown in [any2.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/any2.cpp) one Boost.Any `vector` can hold multiple variables of different types.
<!--
Should change wording
-->
```
for(unsigned i = 0; i < vect.size(); i++)
{
	if(vect.at(i).type() == typeid(int))
		cout << any_cast<int>(vect.at(i)) << endl;
	else if(vect.at(i).type() == typeid(double))
		cout << any_cast<double>(vect.at(i)) << endl;
	else if(vect.at(i).type() == typeid(char))
		cout << any_cast<char>(vect.at(i)) << endl;
}
```
`vect` now holds two `ints`, `doubles`, and `chars` all assigned by the user.
When the above is run:
```
$ g++ -std=c++11 any2.cpp -o any2
$ ./any2
Insert an integer: 8
Insert a double: 3.3 
Insert a char: b
8
3.3
b
```
###All Together
A useful application combining the above examples can be seen in [any3.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/any3.cpp):
```
for(unsigned i = 0; i < v.size(); i++)
{
	cout << "Username: " << any_cast<string>(v.at(i)) << " ";
	i++;
	cout << "SID: " << any_cast<int>(v.at(i)) << " ";
	i++;
	cout << "GPA: " << any_cast<double>(v.at(i)) << endl;
}
```
Here the `vector<any> v` is filled by the user (as seen in the above file) and this is the output:
```
$ g++ -std=c++11 any3.cpp -o any3
$ ./any3
How many students do you have? 1
Student 1's username: jsmit089
Student 1's SID: 861035962
Student 1's GPA: 2.1
List of students:
Username: jsmit089 SID: 861035962 GPA: 2.1
```

##Boost.Variant
Uses library `<boost/variant.hpp>`

With a Boost.Variant variable, you can create a list of possible types (ex: `int`, `double`, etc.) that the variable can be assigned to.

Remember: At least one parameter must be specified.
<!--
Link to a site that explains
-->
<!---
Why should he care
--->
###Why Boost.Variant
One reason to use Boost.Variant rather than Boost.Any is that when outputting a variant value, you do not have to specify the type since you define the possible types the value can be when initializing the value.
For more information see [Boost.Variant vs Boost.Any](http://www.boost.org/doc/libs/1_58_0/doc/html/variant/misc.html#variant.versus-any).

Here is the [variant_simple.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/variant_simple.cpp) file:
```
variant<char, string> var;
var = 'V';
cout << var << endl;
var = "hello world"
cout << var << endl;
```
This will output:
```
$ g++ -std=c++11 variant_simple.cpp -o variant_simple
$ ./variant_simple
V
hello world
```
<!---
Why should he care (add variant.cpp example here)
--->
###`get<type>`
If you wanted to use other operators on the values other than just stream, then you'd have to do something similar to the cast used in Boost.Any.
The way to do that is to use `get<type>(var)` where `<type>` is the variable type you want `var` to be interpreted as. 
So to add two `ints` or to concatenate two `strings`, you'd have to change the code to what's in [variant_get.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/variant_get.cpp):
```
variant<int, string> var, var2;
var = 4;
cout << get<int>(var) + get<int>(var) << endl;
var = "hello";
var2 = " world";
cout << get<string>(var) + get<string>(var2) << endl;
```
This will output:
```
$ g++ -std=c++11 variant_get.cpp -o variant_get
$ ./variant_get
8
hello world
```
If you had attempted to do `var + var` in the previous example without using `get<type>` then the computer wouldn't know which of the types in the original variable declaration you would want the variable to be interpreted as.

###`apply_visitor`
Another thing that Boost.Variant can do is send a variable to a function.
<!--
to a function, or...
-->
When the variable is sent to a function, it can have different actions done to the variable depending on its type.
This is used with `apply_visitor()` that takes two arguments within its parenthesis.
<!--
(link to something explaining how to use boost::apply_visitor())
-->

The first argument expects a struct that is derived from `static_visitor`.
This struct must overload the `operator()` for each possible type defined for your variant variable.
The second parameter is a Boost.Variant variable.

For example in [variant_apply.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/variant_apply.cpp):
```
struct func : public static_visitor<>
{
	void operator()(char c) const { cout << "character " <<  c << endl; }
	void operator()(string s) const { cout << "string " << s << endl; }
};
```
This is the function for apply_visitor.
It is called in main like this:
```
var = 'V';
apply_visitor(func{}, var);
var = "hello world"
apply_visitor(func{}, var);
```
This will output:
```
$ g++ -std=c++11 variant_apply.cpp -o variant_apply
$ ./variant_apply
character V
string hello world
```

`apply_visitor` works like a switch statement.
The variant variable is the test case evaluated for the switch, and each overloaded `operator()` is a different case.
When the variant variable type is the same as the `operator()(type)` then that portion of the code is executed. 
<!--
(explain how apply_visitor works)
--->
Since there are multiple possible results based on the visitor functional object that are passed into `apply_visitor`, we are able to do different types of outputs without needing to know specifically which type of variable we are dealing with.
If we wanted to choose to add two `ints` or concatenate two `strings`, then we could use `apply_visitor` to do that for us as shown in [variant_apply_add.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/variant_apply_add.cpp).

```
void operator()(int i) const { cout << "integer " <<  i + i << endl; }
void operator()(string s) const { cout << "string " << s + s << endl; }
```
The above code would be in the `struct func : public static_visitor<>` function.
It is called in main like this:
```
var = 4;
apply_visitor(func{}, v);
var = "hello"
apply_visitor(func{}, v);
```
You then get:
```
$ g++ -std=c++11 variant_apply_add.cpp -o variant_apply_add
$ ./variant_apply_add
integer 8
string hellohello
```
###`lexical_cast`
If you wanted to have a Boost.Variant variable and cast it to another type to use in the `static_visitor` function to make the `int` act like a `string` as we did with Boost.Any, then you'd have to use the [lexical_cast](http://theboostcpplibraries.com/boost.lexical_cast) library to do so.
The main function of the previous example would need to become what's in [variant_lexical.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/variant_lexical.cpp):
```
variant<int, string> var;
var = 4;
apply_visitor(func{}, var);
var = lexical_cast<string>(var);
apply_visitor(func{}, var);
```
This will now output:
```
$ g++ -std=c++11 variant_lexical.cpp -o variant_lexical
$ ./variant_lexical
integer 8
string 44
```
###All Together
A useful way to use all of these Boost.Variant features is with parsing.
Let's look at our [variant.cpp](https://github.com/baileyherms/rshell/blob/master/src/hw4/variant.cpp) example.

In this file, we want to look at `vect`.
```
vect = {"cat", '<', "in.txt", '|', "tr", "A-Z", "a-z", '>', "out.txt"};
```
`vect` contains different commands and connectors and we want to output the commands and the connectors separately.
The best way we can do this is by using `apply_visitor` to determine what is considered a command or a connector.
```
vector<char> connectors;
vector<string> commands;
struct output : public boost::static_visitor<>
{
		void operator()(char c) const { connectors.push_back(c); }
			void operator()(string s) const { commands.push_back(s); }
};
```
Once we fill `connectors` and `commands`, then we can output each item in the correct category.
By running the `variant.cpp` file, we will get:
```
$ g++ -std=c++11 variant.cpp -o variant
$ ./variant
Original: cat < in.txt | tr A-Z a-z > out.txt 
Commands: cat in.txt tr A-Z a-z out.txt 
Connectors: < | > 
```

##References
[Boost.Optional Directory](http://www.boost.org/doc/libs/1_58_0/libs/optional/doc/html/index.html)

[Boost.Any Directory](http://www.boost.org/doc/libs/1_58_0/doc/html/any.html)

[Boost.Variant Directory](http://www.boost.org/doc/libs/1_58_0/doc/html/variant.html)

[Boost.Optional Library](http://theboostcpplibraries.com/boost.optional)

[Boost.Any Library](http://theboostcpplibraries.com/boost.any)

[Boost.Variant Library](http://theboostcpplibraries.com/boost.variant)

[Boost.Variant vs Boost.Any](http://www.boost.org/doc/libs/1_58_0/doc/html/variant/misc.html#variant.versus-any)

[lexical_cast Library](http://theboostcpplibraries.com/boost.lexical_cast)

