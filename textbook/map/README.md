# STL Maps

In this guide you will learn about maps and how to use them.

## What are Maps?

Maps are a container class from the [Standard Template Library](http://www.cplusplus.com/reference/stl/) (AKA the STL).
Despite their name, the way maps function have little to do with cartography.

A simple way to think about maps is like a snazzy array.
You can define what goes in between the ```[]``` and the types of elements that you access.
(note: maps do not have the O(1) runtime that arrays do.
Their runtime is O(log(n)).)

To create a map we write:
```c++
map<const key, T> var_name;
```

```const key``` is the key type, ```T``` is the element type, and ```var_name``` is the name of our map.
For example, if we want to create a map with ```string```s for keys and ```int```s for elements, we get
```c++
map<string, int> example_map;
```

Let's look at an example of a map in use:

```c++
#include <iostream>
#include <map>

using namespace std;

ing main() {
    //creating a map
    map<string, int> books;
    //adding an element
    books["fahrenheit"] = 451;
    //accessing an element and outputting it
    cout << books["fahrenheit"] << endl;
    return 0;
}
```

In the above code, a map ```books``` is created with ```string```s for keys and ```int```s as elements.
We then add an element ```451``` with the key ```"fahrenheit"```.
we then output the element associated with the key ```"fahrenheit"```.

## Using a Map
Maps have many uses and it would be impossible to go through all of them,
but we can start with an example.

Let's picture a nightmare scenario
Suppose that your evil professor assigned you with the task of replicating the ```ls``` program from bash.
```ls``` has a **lot** of optional flags.
Some flags even do exactly the same thing (such as ```-a``` and ```--all```).

We *could* use a bunch of if-else statements as such:

```c++
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
    for (int i = 1 ; i < argc ; i++)
    {
        if(0 == strcmp(argv[i], "--all")) printAll();
        else if(0 == strcmp(argv[i], "-a")) printAll();
        else if(0 == strcmp(argv[i], "--long")) printLong();
        else if(0 == strcmp(argv[i], "-l")) printLong()
        else if(0 == strcmp(argv[i], "--Recursive")) printRecursive();
        else if(0 == strcmp(argv[i], "-r")) printRecursive();
        //...
        //...
        else cout << "invalid flag: " << argv[i] << endl;
    }
}
```

That could get pretty lengthy.
If we have 26 shorthand flags and 26 longhand flags, 
we would have to make 52 if-else statements.
This is where we bring out our inner mad (computer) scientist.
What if we created a map with function pointers as elements?

```c++
#include <iostream>
#include <map>

using namespace std;

typedef void (*fun_ptr)();

void printAll();
void printLong();
void printRecursive();

int main(int argc, char* argv[]) {

    //creating and initializing map
    map<string, fun_ptr> flag_functions;
    
    flag_functions["--all"] = printAll;
    flag_functions["-a"] = printAll;
    flag_functions["--long"] = printLong;
    flag_functions["-l"] = printLong;
    flag_functions["--recursive"] = printRecursive;
    flag_functions["-R"] = printRecursive;
    //...
    //...
    
    for(int i = 1 ; i < argc ; i++) {
        fun_ptr fp = flag_functions[string(argv[i])];
        //ALWAYS CHECK FOR NULL!
        //If fp is a null pointer, running fp() will seg fault!
        if(fp != NULL) fp();
        else cout << "invalid flag: " << argv[i] << endl;
    }
}

void printAll() { cout << "printed All" << endl;}
void printLong() {cout << "printed Long" << endl;}
void printRecursive() {cout << "printed Recursive" << endl;}
```

By using function pointers, we made the code more readable 
and made it easy to add more flags.

For more examples of maps being used, check the files included with this tutorial.
Don't limit your imagination to those examples though!

For more information, you can look at the relevant pages on 
[CPlusPlus.com](http://www.cplusplus.com/reference/map/map/), 
[cppreferrence](http://en.cppreference.com/w/cpp/container/map),
and [Wikipedia](http://en.wikipedia.org/wiki/Associative_containers#Overview_of_functions).
