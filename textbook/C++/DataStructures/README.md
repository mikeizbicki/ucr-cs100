## Table of Contents

1. [Purpose](#purpose)

    * [TL;DR](#tldr)

2. [Map](#map)

3. [List](#lists)

4. [Stack](#stack)

5. [Queue](#queue)

6. [Vector](#vector)

## Purpose
This tutorial is meant to be a refresher for the data structures taught in CS14, covering the basic usage of a few `stl` data structures. Considering you just finished a quarter of implementing data structures based off of the `stl` implementations you should know the majority of what is presented here. The most important part of this tutorial is the reminder that these structures exist and have practical uses ([Uses of data structures](http://stackoverflow.com/questions/1539069/practical-uses-of-different-data-structures)).

If you are searching for a specific data structure or algorithm to suit your needs:
[Dictionary of algorithms and data structures](http://xlinux.nist.gov/dads//).
 There also exist some lesser-known data structures that might interest you: 
[Interesting lesser-known data structures](http://stackoverflow.com/questions/500607/what-are-the-lesser-known-but-useful-data-structures?rq=1).

Within this folder there exists folders including examples of basic usage for the covered data structures. If you would like to see more about Trees and Hash functions which are used in the Map and Priority_Queue classes respectively: 
[Nice basic tutorial, solid example programs included](http://www.cs.fsu.edu/~jestes/cop3330/notes/datastruct.html). Scroll down to the textbook examples section and there are examples of Trees and Hash functions.

Many of these data structures exist in the Boost library and I would highly recommend getting used to some of the Boost features. Boost has some rather obscure data structures that might be exactly what you need one day. If you only have access to the lab computers then you will have to ask systems to install the boost libraries you need as only 10 or so Boost libraries are installed on Linux by default.

####TL;DR

*Maps are REALLY useful and your professor will attest to their use. Stacks and Queues are less common, but in certain situations they can make your job immensely easier and, therefore, reign supreme. Yes, lists can be a pain to deal with if you hate pointers, but if you get comfortable with using pointers and the rules associated with them, you will find lists can be useful as well. Do not rely only on arrays and vectors just because you're used to them; sometimes they aren't the answer you're looking for. And yes, you will use data structures in your life beyond schooling:* 
 [Use of data structures in your life?](http://stackoverflow.com/questions/389216/advanced-data-structures-in-practice)

### Map

A map is a container filled with Pairs made out of a Key, used to reference/retrieve data, and the actual data itself. An important piece of information to remember about maps are that they are implemented as a binary tree so when iterating through a map the iterator traverses the tree in order based on your comparison operator. To create a map you must decide what you want to store, and how you wish to reference that data. If your
 `pair<const Key, data_type data>` was `pair<int, string>`, you would have a
  map of int values which referenced some data of type string. Basically, at each index of the `map (m[int])` you would have a string value.

```
#include <map>
using namespace std;
int main(){
    map<int, string> m;    
    m[1] = "Shawn Lee";   
    m[2] = "Andy Luu";   
    m[3] = "Jan Sto. Domingo";
    /*There is a more thorough example for maps in the map directory, this 
        just shows basic usage. */ 
    for(map<int, string>::iterator it = m.begin(); it != m.end(); ++it)
        cout << "Key: " << it->first << " Data: " << it->second << endl;
    return 0;
}
```

That's a pretty boring idea as there is nothing actually DONE with the information, but it at least shows assignment and access of data.

Now maps, by default, are ordered. There also exists the unordered version which has a faster access time if the key is known. Unordered maps are implemented through the use of hash tables to allow said fast access time. Creating your own `hash<Key>` function is also allowed if you so desire. The interesting part of unordered maps is that they implement the bucket style hash table where each hashed value is allowed to contain more than one piece of data.

### Lists

Linked lists are made up of nodes containing the data and a pointer to the next position in the list. This gives lists an advantage over vectors when inserting and deleting since it only requires changing the pointers as opposed to shifting the entire vector over. It should be mentioned as well that a list maintains an advantage over vectors in that vector expansion is costly while lists only need to dynamically allocate a new node. What you lose for this advantage is run-time for iterating through the list (Reference: [List iteration](http://stackoverflow.com/questions/1402483/why-is-it-so-slow-iterating-over-a-big-stdlist) ).

```
#include <list>
using namespace std;
int main(){
    list<int> l; //list from 0-99
    for(int i = 0; i < 100; i++) l.push_back(i);
    //same style of insertion as vector, you deal with 
    //pushing and popping element
    for(list<int>::const_iterator it = l.begin; it != l.end(); ++it)
        // *it 
        // ^ do what you want with the value in it
        cout << endl;
        return 0;
}
```

The default linked list is a doubly linked list (it contains pointers to the previous node as well as the next). If you want a singly linked list, then use STL `<forward_list>`.

### Stack

(First In Last Out)

Stacks are interesting in that access involves only the topmost element. Either you push to the top or pop off the top. One way to use a stack is to use it to reverse the order of something. When you push, say a set of strings, to the stack after popping all of the elements off of the stack, the sentence of strings would be in reverse.

```
#include <stack>
using namespace std;
int main(){
    stack<int> rev;
    unsigned i;
    int arr[10];
    for(i = 0; i < 10; ++i) rev.push(i);
        i = 0; 
    while(!rev.empty()){
        arr[i] = rev.top(); //just to show the FILO property
        rev.pop();
        ++i;
    }

    return 0;
}
```

Stacks are used mostly in compilers and operating systems. If that type of thing is your interest, then stacks are your friends.

### Queue

(First In First Out)

Queues can be thought of as a tunnel. What goes into the tunnel first is going to be the first thing to come out of the tunnel. The most common use of this is for job scheduling (just think of a login queue for a game. Those who enter the queue first are those who get logged in first). Just like a stack, the main two operations for a queue are push and pop. You could use this in the case where you had a set of operations you wanted to execute sequentially. By putting them into a queue and just operating on the item popped off the queue you could iterate through said operations.

```
#include <queue>
using namespace std;
int main(){
    queue<int> q;
    for(unsigned i = 0; i < 10; ++i){
    q.push(i); //really simple example for pushing integers to a queue
    //but instead think of the integers as commands you wish
    //to execute and the queue becomes much more useful
    }
    while(!q.empty()){
        //execute starting with the first entry pushed
        /*execute( */ q.front() /* ) */ ;
        q.pop();
    }
    return 0;
}
```

There also exist priority queues (still `#include <queue>` but declared as `priority_queue<Typename> pq;`) which instead of just pushing to the back, `push()` calls the function `push_back()` of the object being pushed then calls `push_heap` (all inside of the original `push()` function) to reorder the priority queue. So instead of popping the very first thing pushed, what is popped is the item with the highest priority based on the container. So for an example where the container is an `int` the object with the highest priority would be the highest number. Much like stacks, queues are used in operating systems. Except queues are used more with process scheduling.

### Vector

Vectors are the go-to answer whenever a simple array is needed but the size is not known at initialization. Internally, a vector is a dynamically allocated array that reallocates more memory when a new element is pushed but requires more space. As stated above in the "List" section, vectors perform efficiently with random access but inefficiently when inserting or removing items. One thing to note with vectors are their ability to change their size or capacity. Capacity refers to the amount of memory allocated to the array; size refers to the number of elements in the vector. Vectors are nice in their simplicity and that they cover the basic needs of many situations.

```
#include <vector>    //vector example is a bit too easy, just treat it as
using namespace std; //an array you can resize and check if you reference
int main(){          //an out of bounds item
    vector<int> v;
    v.push_back(100);
    v.at(0);
    //v.at(1) would give you an out of bounds error rather than a seg fault
    //while running, making it much easier to identify the problem.
    return 0;
}
```

However, vectors can be overused when you rely on them too heavily. For example, I have been in the situation where I thought I needed a `vector<vector<string> >`. What I really wanted to do, however, was map `int` values to said `vector<string>`. Getting too caught up with vectors, I confused myself and overcomplicated things by trying to force something simple into something complex. Simple solutions should be preferred over complex solutions.





