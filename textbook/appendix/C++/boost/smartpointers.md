#Smart Pointers C++

[Smart Pointers](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/smart_ptr.htm)
 help prevent memory errors.
They're self-managed. 
This means they automatically delete themselves when they're no longer needed.
This tutorial focuses on `scoped_ptr` and `shared_ptr`. 

##Scoped_ptr
```
     #include <boost/scoped_ptr.hpp>     //include the boost library
     
     boost::scoped_ptr<int> paycheckAmount(new int);     //declare a scoped pointer for a paycheck
     boost::scoped_ptr<int> taxes(new int(55));     //a new scoped pointer initialized to the value 55
     *paycheckAmount = 415;     //sets a value to the scoped pointer
     cout << paycheckAmount.get();     //shows the memory address of the pointer
     cout << *paycheckAmount;     //shows the value of paycheckAmount, outputs 415
     paycheckAmount.reset(new int(15)); //safely deletes memory for paycheckAmount and reallocates the pointer with the value 15
     cout << paycheckAmount.get();     //now outputs a different memory location than before since it was reset
```

While the declaration of a smart pointer is slightly longer than that of a raw pointer, smart pointers do not have to be explicitly deleted.
As inferred by the name, a scoped pointer will be deleted when it goes out of scope. 
Simply put, a scope can be viewed as everything in between at set of curly braces.
For instance, everything inside a function has its own scope. 
Inside of a function (or class), any declared scoped pointers will be deleted when the function is destructed.
In the above code example, using a raw pointer instead of a smart pointer results in a memory leak.
Why? The memory was never explicitly deallocated. 
There are no leaks when using smart pointers, it's taken care of for us.    
Smart pointer use is similar to that of raw pointers. 
The dereference operator (`*`) is used in front of the pointer to access the value `*paycheckAmount = 415`.
The memory address is reachable; instead of using an ampersand(&), call the `get()` function, `paycheckAmount.get()`.
The main differences lie in the rules of each smart pointer. 

###General Rules:
To maintain proper functionality, there are a few rules that come along with scoped pointers. 

1. 	They **CANNOT** be copied.   
	You cannot use the assignment operator on smart pointers.
	Given the following code:

	```
	     boost::scoped_ptr<int> myPointer(new int);
	     boost::scoped_ptr<int> myPointerDuplicate = myPointer;
	```
	
	compiling results in the error:
	
	```
	     /usr/include/boost/smart_ptr/scoped_ptr.hpp:47:5: error: ‘boost::scoped_ptr<T>::scoped_ptr(const boost::scoped_ptr<T>&) [with T = int]’ is private scoped_ptr(scoped_ptr const &);
	```
	
	This restriction prevents the pointer from being deleted multiple times (and incorrectly).
	
2. 	They **CANNOT** be used inside containers.    
	Declaration inside a container, such as a vector, `vector< boost::scoped_ptr<int> > testPointer;`, typically will not generate a compiler error.
	The compiler doesn't complain since the declaration seems to be syntactically correct.
	A problem arises because containers may copy and delete their elements behind the scenes (i.e. resizing themselves). 
	Since the scoped pointer cannot be copied, when you try to perform a copying action, 
	such as pushing it into a vector `boost::scoped_ptr<int> problematic; testPointer.push_back(problematic);`,
	you will generate a large compiler error.
	If you wish to use a smart pointer in a container, check out the shared pointers section.

3. 	They **CAN** be swapped with other scoped pointers.   
	There is a built in swap function that allows you to swap scoped pointers.   
	```
	     boost::scoped_ptr<int> FirstPointer(new int);
	     boost::scoped_ptr<int> SecondPointer(new int);
	     FirstPointer.swap(Second Pointer);
	```
	It swaps the implicit (FirstPointer) with the explicit (SecondPointer) parameter.
	
4. 	They **CAN** be reset.   
	There is a built in reset function.
        This allows you to delete or replace the contents of your pointer.
	You can reset the pointer in one of two ways:

	1. 	Reset to a pointer declared with the `new` expression,
	    
		```
		     int *ptr = new int;
		     FirstPointer.reset(ptr);
		``` 
		  	
		which deletes the existing pointer, replacing it with the newly declared one.
		It appears that we will have a memory leak after declaring `ptr`, but by using it in the `reset()` function, we give its ownership to `FirstPointer`.
		Since `FirstPointer` is a smart pointer, it will be automatically deleted.
		An alternative to this is : `FirstPointer.reset(new int(10))`, which replaces the existing value of the pointer with 10. 
		
	2. 	Reset to a null pointer `FirstPointer.reset();` or `FirstPointer.reset(0);`.

##Shared Pointer
```
     #include <boost/shared_ptr.hpp>
     
     boost::shared_ptr<int> clubActivities(new int);     //declare a shared pointer for club activities
     boost::shared_ptr<int> clubApparel(clubActivities);     //shared pointer for club apparel. Created as a pointer to same memory location as clubActivities
     cout << clubActivities.get() << ' ' << clubApparel.get();     //both return the same memory address. They point to the same memory.
     *clubActivities = 160;     //sets the value 160 to budget for the memory location of both clubActivities and clubApparel
     cout << *clubActivities << ' ' << *clubApparel;     //both output 160.
     boost::shared_ptr<int> newClubBudget(new int(220));     //shared pointer of new value 220
     clubActivities = newClubBudget;     //clubActivities now points to newClubBudget
     cout << *clubActivities << ' ' << *clubApparel;     //outputs 160 220. ClubApparel still points to the old memory location
     clubApparel = clubActivities;     //clubApparel now points to newClubBudgets memory as well.
     
```
Unlike the scoped pointer, the shared pointer is not deleted when an instance of the pointer goes out of scope.  
Why? Say you have a class containing a pointer as a member variable.
In another function you create several objects of this class, all requiring access to that pointer.
If it were to get deleted when one of the objects goes out of scope, your other objects would have no pointer to use, causing a problem!
The shared pointer will be deleted when there are no remaining objects that own it (when the last object owning the pointer is destroyed).
In the last line of the code above, when `clubApparel` is set to `clubActivities`, nothing points to the first memory location of the initial budget.
This memory is automatically freed, preventing memory leaks.   

###General Rules:
There are a few rules that go along with the shared pointer. 

1.	They **CAN** be copied.   
	Setting another shared pointer equal to your shared pointer is allowed.

	```
	     boost::shared_ptr<int> t;
	     boost::shared_ptr<int> v = t;
	```
	If you wish to have multiple pointers pointing to the same memory, the shared pointer lets you.
	
2.	They **CAN** be used inside containers.   
	They may be used inside a container such as a vector.
	```
	     typedef vector< boost::shared_ptr<int> > pointerVector;
	```
	A container of pointers is useful when referencing an object.
	It eliminates the [slicing problem](http://stackoverflow.com/questions/274626/what-is-object-slicing).
	
3. 	They **CAN** be swapped with other scoped pointers.  
	The swap for shared pointer acts the same for the scoped pointer.
	See the scoped pointer section for more info.

4. 	They **CAN** be reset.   
	The reset for shared pointer acts the same for the scoped pointer.
	See the scoped pointer section for more info.
	One additional example of `reset()` for the shared pointer is if you were creating a linked list and wanted to remove or replace a node, you'd simply call reset on it.

###When To Use
Smart pointers should be used when there is ownership involved.
To give an idea of ownership, say you have a program that has many functions.
You declare your pointer in one of them, but two functions use a pointer to that same memory location.
Gasp! Which function actually owns it and is responsible for it?
Ownership means a specific function “owns” the pointer and must delete it when appropriate.
If there is no instance of ownership, you should use raw pointers instead.  
For more detail and examples of ownership, 
[click here!](http://ericlavesson.blogspot.com/2013/03/c-ownership-semantics.html)

##More Info
To use smart pointers you must include the boost library in your code, and add `using namespace boost` or prepend `boost::` in front of your pointer declaration.
When compiling your code you must include the C++ 11 flag.  
If using UCR’s servers, you must enter the following command to enable the C++ 11 settings for the compiler:   
`source     /opt/rh/devtoolset-2/enable`   
You only need to enter this once and it will work for the remainder of your login session.   
After this (or if using another system that supports compiling with C++ 11), compile using the following format:   
`g++ -std=c++11 yourfile.cpp`

In total, boost contains six different smart pointers.  
These include:   
1. [scoped_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/scoped_ptr.htm)   
2. [shared_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/shared_ptr.htm)   
3. [scoped_array](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/scoped_array.htm)   
4. [shared_array](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/shared_array.htm)   
5. [weak_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/weak_ptr.htm)   
6. [intrusive_ptr](http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/intrusive_ptr.html)   
Check out the links for info.
