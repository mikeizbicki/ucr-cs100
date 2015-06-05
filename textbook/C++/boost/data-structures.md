#Boost Libraries- Optional, Any, Variant
The boost libraries are a set of C++ source libraries that are designed to
be used across a lot of different applications.
This tutorial will focus on boost/optional, boost/any,and boost/variant. 
Note: It is necessary to have using boost::<type_name> at the top of your code or else, it is required to have boost::<type_name> for every boost function.

Both instances will be shown below for optional, any, and variant.
Note: It is necessary to have `using boost::<type_name>` or else, it is required to have `boost::<type_name>` for every boost function, both will be shown below.

`<type_name> = optional, any, variant`

##Boost.Optional
Uses library `<boost/optional.hpp>`
Allows for optional return types.
This is done because Boost.optional initializes a variable as empty but allows for a possible type change later.
This can be useful to use if you want to check if a function returns a valid value.

For example -1 is normally considered valid (say if you are measuring temperature), but -1 is also used to say when a function has failed. 
In the temperature example, we want -1 to be a possible passing return value, so we'll use boost::optional to know when the function hasn't done the task we want it to.

boost::optional allows you to initialize your variable in the temperature function to empty, and if nothing is returned, then you know that you have an error.

```
#include <boost/optional.hpp>
#include <iostream>

using namespace std;
using boost::optional;

double deg;
boost::optional<double> degrees()
{
	if(deg)
	{
		cout << "There is a temperature reported." << endl;
		return deg;
	}
	else
	{
		cout << "There is no temperature reported" << endl;
		return optional<double>{};
	}
}

int main()
{
	degrees();
	deg = 43;
	degrees();
	return 0;
}
```
This will return:

```
There is no temperature reported.
There is a temperature reported.
```
<!---
is_initialized() -> will check to see if the boost::optional variable has been initialized. Can use it to know if it is possible to output.

Constructor takes two params. First is a conditional statement, second is a value. Ex/ return optional<int>{i%2 == 0, i}; if false will return optional<int>{}

make_optional() makes a new optional var. Similar to new

boost::optional get_value_or( , )    boost::get_optional_value_or( , ) if first param is initialized then will return that value else will return a default value specified as the second param
--->
##Boost.Any
Uses library `<boost/any.hpp>`
It allows for a variable that can be changed to any type in any portion of its scope.
<!---
Explain what variables it cannot use
-->
This is useful to use in place of `auto` because auto will assign a type to that variable from that point on, and boost.any will not. 
This takes up less memory (but the variable itself will take up more memory) because it enables you to reuse variables as different types instead of having to initialize new variables.
<!--
and why
-->
For example:
```
#include <boost/any.hpp>
#include <iostream>

using namespace std;

int main()
{
	boost::any var = 4;
	
	var = false;
	var = 3.25678;
	var = string("hello world");
	return 0;
}
```
But if you tried to do this:
```
int main()
{
	boost::any var = 4;
	
	var = false;
	var = 3.25678;
	var = string("hello world");	
	cout << var << endl;
	return 0;
}
```
You would get an error because boost::any does not support `<<`, so you cannot use `cout` with anything involving any.

So what do you need to do to output a boost::any variable?
You would need to use `boost::any_cast` 
<!--
(explain how var is currently set to a string and that it cannot `cout << boost::any_cast<int>(var) << endl;`)
-->
```
int main()
{
	boost::any var = 4;
	
	var = false;
	var = 3.25678;
	var = string("hello world");
	cout << boost::any_cast<string>(var) << endl;
	return 0;
}
```
This outputs `hello world`

You can even output multiple 'boost::any variables'. These variables will output a value based on their type.
<!--
(explain different types)
(explain better, change wording)
-->
```
int main()
{
	boost::any var = 4;
	cout << boost::any_cast<int>(var) << endl;
	var = false;
	cout << boost::any_cast<bool>(var) << endl;
	var = 3.25678;
	cout << boost::any_cast<double>(var) << endl;
	var = string("hello world");
	cout << boost::any_cast<string>(var) << endl;
	return 0;
}
```
This will output:
```
4
0
3.25678
hello world
```
Note: You will have to change the cast type depending on what type var is currently set to.
The cast assigns a type to var so the computer knows how to handle the variable.
The cast is necessary because 'boost::any' assigns values to var at runtime so the code needs to be told what type it is dealing with beforehand, since values can be interpreted in different ways.
<!--
Link to something explaining cast type
-->

For example, we can modify the previous example to:
```
int main()
{
	boost::any var = 4;
	cout << boost::any_cast<int>(var) + boost::any_cast<int>(var) << endl;
	cout << boost::any_cast<string>(var) + boost::any_cast<string>(var) << endl;
	return 0;
}
```
This will now output:

```
8 44
```
As you can see, the cast is very important in how the code ends up being executed.
Now, you might be thinking that it might just be easier to create separate variables so you don't have to worry about casting the types, so let's use `boost::any` with vectors.

This means that you can use one vector to hold multiple variables of different types.
<!--
Should change wording
-->

For example:
```
vector<boost::any> vect;
vect.push_back('a');
vect.push_back(8);
vect.push_back(9.09);

```
Vector vect now holds the values `'a', 8, 9.09`.

##Boost.Variant
Uses library `<boost/variant.hpp>`
With a boost::variant variable, you can create a list of possible types (ex: int, double, etc.) that the variable can be assigned to.

Remember: At least one parameter must be specified.
<!--
Link to a site that explains
-->

One reason to use “variant” rather than “any” is that when outputting a variant value, you do not have to specify the type since the computer already has a list of possible types the value can be.

For example:
```
#include <boost/variant.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	boost::variant<int, double, char, string> var;
	var = 4;
	cout << var << endl;
	var = 3.98;
	cout << var << endl;
	var = 'V';
	cout << var << endl;
	var = "hello world"
	cout << var << endl;
	return 0;
}
```
This will output:
```
4
3.98
V
hello world
```
If you wanted to use other operators on the values other than just stream, then you'd have to do something similar to the cast used in `boost::any`.
The way to do that is to use `boost::get<type>(var)` where type is the variable type you want var to be interpreted as. 
So to add two ints or to concatenate two strings, you'd have to change the code to:
```
#include <boost/variant.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	boost::variant<int, double, char, string> var, var2;
	var = 4;
	cout << boost::get<int>(var) + boost::get<int>(var) << endl;
	var = "hello";
	var2 = " world";
	cout << boost::get<string>(var) + boost::get<string>(var2) << endl;
	return 0;
}
```
This will output:
```
8
hello world
```
If you had attempted to do var + var in the previous example without using `boost::get<type>` then the computer wouldn't know which of the types in the original variable declaration you would want the variable to be interpreted as.

Another thing that “variant” can do is send a variable to a function.
<!--
to a function, or...
-->
When the variable is sent to a function, it can have different actions done to the variable depending on its type.
This is used with `boost::apply_visitor()` that takes two arguments within the parenthesis..
<!--
(link to something explaining how to use boost::apply_visitor())
-->
The first argument is called a visitor functional object and the second parameter is a `boost::variant` variable.
The visitor functional object is a struct that must overload the operator() for each possible type defined for your variant variable.

For example:
```
struct func : public boost::static_visitor<>
{
	void operator()(int i) const
		cout << "integer " <<  i << endl;
	void operator()(double d) const
		cout << "double " <<  d << endl;
	void operator()(char c) const
		cout << "character " <<  c << endl;
	void operator()(string s) const
		cout << "string " << s << endl;
};
int main()
{
	boost::variant<int, double, char, string> var;
	var = 4;
	boost::apply_visitor(func{}, v);
	var = 3.98;
	boost::apply_visitor(func{}, v);
	var = 'V';
	boost::apply_visitor(func{}, v);
	var = "hello world"
	boost::apply_visitor(func{}, v);
	return 0;
}
```
This will output:
```
integer 4
double 3.98
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
If we wanted to choose to add two ints or concatenate two strings, then we could use `apply_visitor` to do that for us.

```
struct func : public boost::static_visitor<>
{	
	void operator()(int i) const
		cout << "integer " <<  i + i << endl;
	void operator()(string s) const 
		cout << "string " << s + s << endl;
};
int main()
{    
	boost::variant<int, string> var;
	var = 4;
	boost::apply_visitor(func{}, var);
	var = "hello ";
	boost::apply_visitor(func{}, var);
	return 0;
}
```
This will output:
```
integer 8
string hello hello
```
Note: If you wanted to have a boost::variant variable and cast it to another type to use in the `apply_visitor` function to make the int act like a string as we did with `boost::any`, then you'd have to use the [boost::lexical_cast](http://theboostcpplibraries.com/boost.lexical_cast) library to do so.
The main function of the previous example would need to become:
```
int main()
{
	boost::variant<int, string> var;
	var = 4;
	boost::apply_visitor(func{}, var);
	var = boost::lexical_cast<string>(var);
	boost::apply_visitor(func{}, var);
	return 0;
}
```
This will now output:
```
integer 8
string 44
```
