# STL Maps 

In this guide you will learn about maps and how to implement them.

##  What is a Map?

Maps are a container class from the [Standard Template Library](http://www.cplusplus.com/reference/stl/) (AKA the STL).
Despite their name, the way maps function have little to do with cartography.

Lets pretend that a map is a hotel.
Hotels use keys in order to gain access to rooms.
Depending on which key you are given, you get a different room.

Similarly, maps take keys, and depending on which key you give it, you will receive different values. 

Another way to think about maps is like a snazzy array.
You can define what goes in between the ```[]```'s and the types of elements

Let's look at an example of a map in use:

```c++
map<string, int> books;

books["fahrenheit"] = 451;

cout << books["fahrenheit"] << endl;
```

You may guess that the output of the above code is ```451``` and you are correct!
A map ```books``` with strings for keys and ints as elemtents is declared.
We then add an element ```451``` with the key ```"fahrenheit"```.
we then output the element with the key ```"fahrenheit"```. 

If you are lost, no worries!
This guide will go through everything in detail.

## Creating a Map
Let's go through the steps of building a map.

### Declaration

The template for ```map``` is:

```c++
map<const key, T> var_name;
```

The variable types that you want to use for the keys and elements go in between the brackets.
For example, if we want strings as keys and ints for elements we get:

```c++
map<string, int> example_map;
```

### Adding and Accessing Elements

Let's say that you have declared ```example_map``` from above.
Adding a new element to ```example_map``` is easy.

```c++
example_map["Deep Thought"] = 42;
```

Here, our key is "Deep Thought" and we assigned that space to the number 42.
Lets access it shall we?

```c++
int the_ultimate_answer;
the_ultimate_answer = example_map["Deep Thought"];
```

Here, we gave ```example_map``` the key "Deep Thought".
A bunch of rats then looked through ```example_map``` and got the results.
We now know for sure that ```the_ultimate_answer``` is ```42```, but everyone knows that.

## Using a Map

Let's picture a nightmare scenario
Suppose that your evil professor assigned you with the task of replicating the ```ls``` program from bash.
```ls``` has a **lot** of optional flags.
Some flags even do exactly the same thing (such as ```-a``` and ```--all```).

We *could* use a bunch of if-else statements as such:

```c++
int main(int argc, char* argv[]) {
	for (int i = 1 ; i < argc ; i++)
	{
		if(0 == strcmp(argv[i], "--all"))		printAll();
		else if(0 == strcmp(argv[i], "-a"))		printAll();
		else if(0 == strcmp(argv[i], "--long"))		printLong();
		else if(0 == strcmp(argv[i], "-l"))		printLong()
		else if(0 == strcmp(argv[i], "--Recursive"))	printRecursive();
		else if(0 == strcmp(argv[i], "-r"))		printRecursive();
		//...
		//...
		else cout << "invalid flag: " << argv[i] << endl;
	}
}
```

Those if-else statements could get lengthy.
If you had to implement 26 shorthand flags and 26 longhand flags, that makes 52 if-else statements, many of which are just repeats.
Let's try jamming in a map.

```c++
int main(int argc, char* argv[]) {
	map<string, string> flag_map;
	flag_map["--all"]		= "all";
	flag_map["-a"]			= "all";
	flag_map["--long"]		= "long";
	flag_map["-l"]			= "long";
	flag_map["--Recursive"]		= "Recursive";
	flag_map["-R"]			= "Recursive";
	//flags,
	//flags,
	//and more flags
	
	for(int i = 1 ; i < argc ; i++)
	{
		if(flag_map[argv[i]] == "all") 		printAll();
		else if (flag_map[argv[i]] == "long") 	printLong();
		else if (flag_map[argv[i]] == "Recursive")	printRecursive();
		//...
		//...
		else cout << "invalid flag: " << argv[i] << endl;
	}
}
```

So what is the gain from this?
Well, now have a place to see all the available flags neatly displayed in our code.
We have also condensed our if-else statement from 52 statements down to 26.
Despite making the code look slimmer, we still have not reduced the number of lines in the code.
The slimmer look is due to it becoming less trashy.

This is where we bring out our inner mad (computer) scientist.
What if we used function pointers?

```c++
typedef void (*fun_ptr)();

int main(int argc, char* argv[]) {
	
	//creating and initializing map
	map<string, fun_ptr> flag_functions;
	
	flag_functions["--all"] 	= printAll;
	flag_functions["-a"] 		= printAll;
	flag_functions["--long"] 	= printLong;
	flag_functions["-l"] 		= printLong;
	flag_functions["--recursive"] 	= printRecursive;
	flag_functions["-r"] 		= printRecursive;
	//...
	//...
	
	for(int i = 1 ; i < argc ; i++) {
		fun_ptr fp = flag_functions[string(argv[i])]
		//ALWAYS CHECK FOR NULL!
		//If fp is a null pointer, running fp() will seg fault!
		if(fp != NULL) fp();
		else cout << "invalid flag: " << argv[i] << endl;
	}
}	
```

For more information, you can look at the relevant pages on [CPlusPlus.com](http://www.cplusplus.com/reference/map/map/), [cppreferrence](http://en.cppreference.com/w/cpp/container/map), and [Wikipedia](http://en.wikipedia.org/wiki/Associative_containers#Overview_of_functions)
