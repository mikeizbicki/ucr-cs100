# Using Maps from the standard template library

In this guide you will learn about maps and how to implement them.

##  What is a Map and how do they work?

Maps are a container class from the Standard Template Library (AKA the STL).
Despite their name, the way maps function have little to do with cartography.

Lets pretend that a map is a hotel.
Hotels use keys in order to gain access to rooms.
Depending on which key you are given, you get a different room.
Similarly, maps take keys, and depending on which key you give it, you will receive different values. 

## Creating a Map

Okay, so now you have a general grasp of how they work, but how do we even use them???
Fear not!
This guide will walk you through the process.

### Declaration

The generic declaration for ```map``` is as such:

```c++
map<const key, T> var_name;
```

You declare the types of variables that you want to use between the brackets.
For example, if we wanted strings as keys and ints as return values, we declare

```c++
map<string, int> example_map;
```

### Adding and Accessing Elements

Added and accessing elements are very similar in process.
Let's say that you have declared ```example_map``` from above.
Adding a new element is easy.

```c++
example_map["Hello"] = 42;
```

Here, our key is "Hello" and we assigned that space to the number 3.
Lets access it shall we?

```c++
int the_ultimate_answer;
the_ultimate_answer = example_map["Hello"];
```

Here, we gave ```example_map``` the key "Hello".
A bunch of monkeys then looked through your map and found the room holding the answer.
They opened the room with the key and brought you back your answer.
We now know for sure that ```the_ultimate_answer``` is ```42```, but everyone knows that.

## Using a Map

All this information is nice and all, but where is it useful?
First, let's picture a scenario.
Suppose that your evil professor assigned you with the task of replicating the ```ls``` program from bash.
```ls``` has a **lot** of flags to consider.
Some flags even do exactly the same thing (such as ```-a``` and ```--all```).

We could use a bunch of ```if-else``` statements as such:

```c++
int main() {
	//of course a real ls program won't have prompts
	//or be this simple,
	//but lets pretend for the sake of the example
	string flag;
	cout << "enter a flag: ";
	cin >> flag;
	cout << endl;
	
	if(flag == "--all") //do stuff
	else if(flag == "-a") // do the same thing
	else if (flag == "--long")//do things
	else if (flag == "-l") //even more things
	//...
	//...
	else cout << "invalid flag" << endl;
}
```

Those ```if-else``` statements could get lengthy.
If you had to implement 26 shorthand flags and 26 longhand flags, that makes 52 ```if-else``` statements, many of which are just repeats.
Let's try jamming in a map.

```c++
int main() {
	//of course a real ls program won't have prompts
	//or be this simple,
	//but lets pretend for the sake of the example
	string flag;
	cout << "enter a flag: ";
	cin >> flag;
	cout << endl;
	
	map<string, string> flag_map;
	flag_map["--all"]		= "all";
	flag_map["-a"]			= "all";
	flag_map["--long"]		= "long";
	flag_map["-l"]			= "long";
	//flags,
	//flags,
	//and more flags
	
	if(flag_map[flag] == "all") // do something
	else if (flag_map[flag] == "long") // do something else
	//...
	//...
	else cout << "invalid flag" << endl;
}
```

So what is the gain from this?
Well, now have a place to see all the available flags neatly displayed in our code.
We have also condensed our if-else statement from 52 statements down to 26.

The ```if-else``` conditionals are still very wordy.
This is where we introduce ```map```'s best friend: ```switch```.
Now instead of the lengthy ```if-else``` statements from above, we can have the nice and clean ```switch``` statement below.

```c++
int main() {
	//of course a real ls program won't have prompts
	//or be this simple,
	//but lets pretend for the sake of the example
	string flag;
	cout << "enter a flag: ";
	cin >> flag;
	cout << endl;
	
	map<string, char> flag_map; // Notice that we are returning chars now
	flag_map["--all"]		= 'a';
	flag_map["-a"]			= 'a';
	flag_map["--long"]		= 'l';
	flag_map["-l"]			= 'l';
	//flags,
	//flags,
	//and more flags
	
	switch(flag_map[flag]) {
		case 'a' :
			//do stuff
		case 'l' :
			//do other stuff
		//another case
		//more cases
		//...
		default :
			cout << "invalid flag" << endl; break; 
	}
}
```

For more information, you can look at the [relevant page on CPlusPlus.com](http://www.cplusplus.com/reference/map/map/).
