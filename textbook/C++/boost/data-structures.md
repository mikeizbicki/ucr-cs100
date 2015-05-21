#Boost Libraries- Optional, Any, Variant
There are many sublibraries of boost.
This tutorial will focus on boost/optional, boost/any, and boost/variant.
Note: It is necessary to have `using boost::<type_name>` or else, it is required to have `boost::<type_name>` for every boost function, both will be shown below.
<type_name> = optional, any, variant
##Boost.Optional
Uses library `<boost/optional.hpp>`
Boost.Optional allows for optional return types by initializing a variable and making it initially empty.

This can be useful to use if you want to check if a function returns a valid value, but -1 is considered valid (say if you are measuring temperature).

boost::optional allows for you to initialize your variable in the temperature function to empty and if nothing is returned then you know that there is an error.
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
##Boost.Any
Uses library `<boost/any.hpp>`
Boost.Any allows for a variable that can be used for any type whatsoever in any portion of its scope.

This is useful to use in place of `auto` due to the fact that auto will assign a type to that variable from that point on and boost.any will not.
This takes up less memory space because it enables you to reuse variables as different types instead of having to initialize new variables.

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
You would get an error because boost::any does not support `<<`.

So what do you need to do to output a boost::any variable?
You would need to use boost::any_cast:
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

You can even output multiple boost::any variables and they will output depending on their type.
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
Note: you will have to change the cast type depending on the current type of var.

You can also use boost::any with vectors.

This means that you can use one vector to hold different types.

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
With a boost::variant variable, you can have a list of possible types that the variable can be assigned to.

Remember: At least one parameter must be specified.

One reason to use varient rather than  any is that when outputting a variant value, you do not have to specify the type, for example:
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

Another thing that variant can do is send a variable to a function and have different actions done inside the function depending on the type that is applied to the variable.
This is used with `boost::apply_visitor()`
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
Note: In the function above it is required to overload each operator in the variant or else the function will not compile.
