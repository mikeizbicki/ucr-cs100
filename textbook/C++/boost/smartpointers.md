#Smart Pointers C++

##Overview
This tutorial covers smart pointers from the 
[boost library](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/smart_ptr.htm).
Smart pointers help with memory management, helping prevent memory leaks.
They're self-managed, automatically deleting themselves when they're no longer needed.
In this tutorial we will focus on `scoped_ptr` and `shared_ptr`. 
Using these pointers is similar to using regular pointers (raw pointers). 
Include the boost library: `#include <boost/shared_ptr.hpp>` or `#include <boost/scoped_ptr.hpp>`.
Declare your pointer. *Scoped pointer*: `boost::scoped_ptr<int> my_scoped_pointer;`,    *Shared pointer*: `boost::shared_ptr<int> my_shared_pointer;`. 
And use it as you would a raw pointer.
Specifics will be shown in the appropriate section.
We'll cover *why*, *where*, and *how* to use these pointers.

##Before Getting Started
Smart pointers are a part of the boost library.
In total, boost contains six different smart pointers.  
These include 
[scoped_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/scoped_ptr.htm),
[shared_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/shared_ptr.htm), 
[scoped_array](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/scoped_array.htm), 
[shared_array](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/shared_array.htm), 
[weak_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/weak_ptr.htm), 
and [intrusive_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/intrusive_ptr.html). 
We will focus mainly on scoped and shared pointers here.   
To use them you must include the boost library in your code, and prepend `boost::` in front of your pointer declaration, as shown above.
Being part of C++ 11, when compiling your code you must include the C++ 11 flag.  
If using UCR’s servers, you must enter the following command to enable the C++ 11 settings for the compiler:   
`source	     /opt/rh/devtoolset-2/enable`   
You only need to enter this once and it will work for the remainder of your login session.   
After this (or if using another system that supports compiling with C++ 11), compile using the following format:   
`g++ -std=c++11 yourfile.cpp`

##Why Use Smart Pointers?
Raw pointers must be self-managed. 
When you create them, you must delete them explicitly in the program. 
Forgetting to do so can cause major memory leaks! 
Deleting them yourself may not seem like a big deal, but doing so incorrectly can ruin the rest of your program. 
With smart pointers, the cleanup is done for you, meaning you don’t have to delete them! 
Each smart pointer has a unique set of instructions that determine when it will be deleted.  

###When To Use
Smart pointers should be used when there is ownership involved.
To give an idea of ownership, say you have a program that has many functions.
You declare your pointer in one of them, but two functions use a pointer to that same memory location.
Gasp! Which function actually owns it and is responsible for it?
Ownership means a specific function “owns” the pointer and must delete it when appropriate.
If there is no instance of ownership, you should use raw pointers instead.  
For more detail and examples of ownership, 
[click here!](http://ericlavesson.blogspot.com/2013/03/c-ownership-semantics.html)

##Scoped_ptr

###How it's managed:
As inferred by the name, a scoped pointer will be deleted when it goes out of scope. 
Simply put, a scope can be viewed as everything in between at set of curly braces.
For instance, everything inside a function has its own scope. 
Inside of a function (or class), any declared scoped pointers will be deleted when the function is destructed. 
What sets it apart from normal variables declared in a scope is it is non-copyable. 

###General Rules:
To maintain proper functionality, there are a few rules that come along with *scoped pointers*. 

1. 	They **CANNOT** be copied.   
	Trying to set another pointer (or anything) equal to your scoped pointer is not allowed.
	If you tried something like this:

	```
		boost::scoped_ptr<int> myPointer(new int);
		boost::scoped_ptr<int> myPointerDuplicate = myPointer;
	```
	
	You will receive an error saying:
	
	```
	/usr/include/boost/smart_ptr/scoped_ptr.hpp:47:5: error: ‘boost::scoped_ptr<T>::scoped_ptr(const boost::scoped_ptr<T>&) [with T = int]’ is private scoped_ptr(scoped_ptr const &);
	```
	
	This feature prevents the pointer from being deleted multiple times (and incorrectly).
	
2. 	They **CANNOT** be used inside containers.    
	Declaration inside a container, such as a vector, `vector< boost::scoped_ptr<int> > testPointer;`, typically will **not** generate a compiler error.
	The compiler doesn't complain since the declaration seems to be syntactically correct.
	A problem arises because containers may copy and delete their elements behind the scenes (i.e. resizing themselves). 
	Since the *scoped pointer* **cannot** be copied, when you try to perform a copying action, 
	such as pushing it into a vector `boost::scoped_ptr<int> problematic; testPointer.push_back(problematic);`,
	you will generate a large compiler error.
	If you wish to use a *smart pointer* in a container, check out the *shared pointers* section.

3. 	They **CAN** be swapped with other scoped pointers.   
	There is a built in swap function that allows you to swap scoped pointers.   
	```
		boost::scoped_ptr<int> FirstPointer(new int);
		boost::scoped_ptr<int> SecondPointer(new int);
		FirstPointer.swap(Second Pointer);
	```
	It swaps the implicit (FirstPointer) with the explicit (SecondPointer) parameter.
	
4. 	They **CAN** be reset.   
	There is a built in reset function. It allows you to reset the pointer in one of two ways:

	1. 	Reset to a pointer declared with the `new` expression,
	    
		```
			int *ptr = new int;
			FirstPointer.reset(ptr);
		``` 
		  	
		which deletes the existing pointer, replacing it with the newly declared one.
		It appears that we will have a memory leak after declaring `ptr`, but by using it in the `reset()` function, we give its ownership to `FirstPointer`.
		Since `FirstPointer` is a smart pointer, it will be automatically deleted.
		
	2. 	Reset to a null pointer `FirstPointer.reset();` or `FirstPointer.reset(0);`.

	Resetting the pointer provides a way to reset or replace the pointer if need be.

##Shared Pointer
###How It's Managed
Unlike the scoped pointer, the shared pointer is not deleted when an instance of the pointer goes out of scope.  
Why? Say you have a class which contains a pointer as a member variable.
In another function you create several objects of this class, all of which need access to that pointer.
If it were to get deleted when one of the objects goes out of scope, your other objects would have no pointer to use, causing a problem!
The shared pointer will be deleted when there are no remaining objects that own it (when the last object owning the pointer is destroyed).

###General Rules:
There are a few rules that go along with the shared pointer. 

1.	They **CAN** be copied.   
	Setting another shared pointer equal to your shared pointer is allowed.

	```
		boost::shared_ptr<int> t;
		boost::shared_ptr<int> v = t;
	```
	If you wish to have multiple pointers pointing to the same memory, the *shared pointer* lets you.
	
2.	They **CAN** be used inside containers.   
	They may be used inside a container such as a vector.
	```
		typedef vector< boost::shared_ptr<int> > pointerVector;
	```
	A container of pointers is useful when referencing an object.
	It elimates the [slicing problem](http://stackoverflow.com/questions/274626/what-is-object-slicing).
	
3. 	They **CAN** be swapped with other scoped pointers.  
	The swap for *shared pointer* acts the same for the *scoped pointer*.
	See the *scoped pointer* section for more info.

4. 	They **CAN** be reset.   
	The reset for *shared pointer* acts the same for the *scoped pointer*.
	See the *scoped pointer* section for more info.
	One additional example of `reset()` for the *shared pointer* is if you were creating a linked list and wanted to remove or replace a node, you'd simply call reset on it.

###Quick Notes: 
* For the address of the pointer, call the function `get()`.    
* Add other side notes here

