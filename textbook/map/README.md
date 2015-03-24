# STL Map

In this guide you will learn about maps and how to use them.

## What are Maps?

Maps are a container class from the [Standard Template Library](http://www.cplusplus.com/reference/stl/) (AKA the STL).
Despite their name, the way maps function have little to do with cartography.

A simple way to think about maps is like a snazzy array.
You can define what goes in between the ```[]``` and the types of elements that you access.

To create a map we write:
```c++
map<const key, T> var_name;
```

```const key``` is the key type, ```T``` is the element type, and ```var_name``` is the name of our map.
For example, if we want to create a map with keys of type ```string``` and elements of type ```int```, we get
```c++
map<string, int> example_map;
```

Let's look at an example of a map in use:

```c++
#include <iostream>
#include <map>

using namespace std;

int main() {
    //create a map
    map<string, int> books;
    //add an element
    books["fahrenheit"] = 451;
    //access an element and output it
    cout << books["fahrenheit"] << endl;
    return 0;
}
```

In the above code, a map ```books``` is created with ```string```s for keys and ```int```s as elements.
We then add an element ```451``` with the key ```"fahrenheit"```.
we then output the element associated with the key ```"fahrenheit"```.

## Maps with function pointers
Let's picture a nightmare scenario
Suppose that your evil professor assigns you the task of replicating the ```ls``` terminal program.
```ls``` has a **lot** of optional flags, some of them doing exactly the same thing (ex. ```-a``` and ```--all```).

We *could* use a bunch of if-else statements:

```c++
#include <iostream>

using namespace std;
int main(int argc, char* argv[]) {
    for (int i = 1 ; i < argc ; i++)
    {
        if(0 == strcmp(argv[i], "--all"))               printAll();
        else if(0 == strcmp(argv[i], "-a"))             printAll();
        else if(0 == strcmp(argv[i], "--long"))         printLong();
        else if(0 == strcmp(argv[i], "-l"))             printLong()
        else if(0 == strcmp(argv[i], "--Recursive"))    printRecursive();
        else if(0 == strcmp(argv[i], "-r"))             printRecursive();
        //...
        //...
        else cout << "invalid flag: " << argv[i] << endl;
    }
}
```

That could get pretty lengthy.
If we have 26 shorthand flags and 26 longhand flags, 
we would have to make 52 if-else statements PLUS CODE.
This is where we bring out our inner mad (computer) scientist.
What if we created a map with [function pointers](http://www.cprogramming.com/tutorial/function-pointers.html) as elements?

```c++
#include <iostream>
#include <map>

using namespace std;

void printAll();
void printLong();
void printRecursive();

int main(int argc, char* argv[]) {

    //create and initialize map
    map<string, void(*)()> flag_functions;
    flag_functions["--all"]         = printAll;
    flag_functions["-a"]            = printAll;
    flag_functions["--long"]        = printLong;
    flag_functions["-l"]            = printLong;
    flag_functions["--recursive"]   = printRecursive;
    flag_functions["-R"]            = printRecursive;
    //...
    //...
    
    for(int i = 1 ; i < argc ; i++) {
        void (*fp)() = flag_functions[string(argv[i])];
        //ALWAYS CHECK FOR NULL!
        //If fp is a NULL pointer, running fp() will seg fault!
        if(fp != NULL) fp();
        else cout << "invalid flag: " << argv[i] << endl;
    }
}

```

By using function pointers, we made the code more readable and made it easy to add more flags.

For more examples of maps being used, check the files included with this tutorial.
Don't limit your imagination to those examples though!

For more information, you can look at the relevant pages on 
[CPlusPlus.com](http://www.cplusplus.com/reference/map/map/), 
[cppreferrence](http://en.cppreference.com/w/cpp/container/map),
and [Wikipedia](http://en.wikipedia.org/wiki/Associative_containers#Overview_of_functions).
