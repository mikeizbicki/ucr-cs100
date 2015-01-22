#Boost
Boost is one of many c++ libraries which adds additional features to the STL. As such, this tutorial will focus on demonstrating the potential of two of its libraries: Container and Tribool, which can often be applied in place of their STL equivalents.
##Containers - Stable vector
Within Boost, there are dozens of containers, one of which is the stable vector, a safer alternative to the STL vector. Its safety comes from an often-overlooked aspect of vectors, which is their tendency to invalidate iterators upon erasing data in the middle of a vector. Therefore, stable vectors account for this weakness, and allow a user to erase data from the middle of a vector without it ever invalidating the iterators.

Before illustrating the application of this added stability, it's important to understand how vectors become invalidated,
take the following snippet of code:
```
#include <vector>

int main(){
    vector<int> v;
    
    for(unsigned i = 0; i < 5; i++){
        v.push_back(i);
    }

    v.erase(v.begin()+2); //Erases v.at(2), slot 3

    return 0;
}
```
When this code is run on an STL vector, it has the potential to invalidate all of vector v's iterators which follow the location being removed, in this case the 3rd slot. However, it's NOT guaranteed to invalidate them, and in many scenarios may work properly leaving the iterators undamaged. This is due to a number of reasons, such as the compiler being used on the source file, making it a difficult error to find and correct in a larger program. Therefore, it's much safer to use stable vectors in situations where data may be erased from the middle of a vector. The safe method for writing the above code is:
```
#include <boost/container/stable_vector.hpp>

int main(){
    boost::container::stable_vector<int> v;
    
    for(unsigned i = 0; i < 5; i++){
        v.push_back(i);
    }
    
    v.erase(v.begin()+2);
    
    return 0;
```
Notice how similar it is to the previous example? This demonstrates how easy it is to use stable vectors, and should feel familiar for those already associated with STL vectors. However, this example lacks enough depth to demonstrate the practicality and potential of stable vectors, so let's apply it to a real world example.

For instance, imagine writing the payroll software for a company which experiences a high turnover-rate in its employees. Since it's incredibly important that payroll is always on time, the software can only afford minimal downtime, and must be able to add and remove employees at a moment’s notice. Therefore, an STL vector would create problems as soon as too many employees were removed from the system, but a stable vector would have no problem with the deletion and could function with minimal interruptions. It would look something like this:
```
#include <boost/container/stable_vector.hpp>
#include <string>

class Employee{
    public:
        string name, job;
    private:
        int salary;
}

//...Employee constructors/destructors

int main(){
    //Simplified creation of Employees
    Employee joe; //Joe, janitor, 35000
    Employee bob; //Bob, accountant, 50000
    Employee rick; //Rick, CEO, 275000 
    
    //Creation of the payroll vector
    boost::container::stable_vector<Employee> payRoll;

    //Hiring employees
    payRoll.push_back(joe);
    payRoll.push_back(bob);
    payRoll.push_back(rick);

    //Firing employees
    payroll.erase(v.begin()+1); //Clean out your desk by 5pm, Bob.
    payroll.erase(v.begin()); //Good-bye, Joe!

    return 0;
}
```
Notice how utilizing a stable vector early on in the creation of the program allows it to be more flexible in the future. Although this is a simplified example, it demonstrates the practicality of stable vectors, as in this scenario, it would have saved a real company thousands of dollars by not having prolonged downtime. This is the type of forethought that you as a programmer need to make when deciding between standard vectors and stable ones.
##Disadvantages of Stable Vectors
Speaking of which vector to select, it's important to note the disadvantages of stable vectors. Namely, it has setbacks in two ways: through its organization of elements, and its memory allocation. Unlike STL's vector, stable vectors don't have element contiguity, meaning that its elements are not located directly after each other in memory. Furthermore, due to stable vector being something of a hybrid between list and vector, it has overhead in performance and memory allocation, making it run slower. Overall, there are clearly best times to use both, and it’s important to apply the proper vector to each program you build. 
##Tribools
The next boost library is Tribool, which, as its name implies, is a tri-state boolean. Being that programmers work primarily in binary concepts, at first it may seem difficult to understand the application of a tri-state device, because many problems can be solved with a simple true or false check. However, tribools introduce a third state, indeterminate, which works well in many real-time applications.

Assume for a moment that you've been tasked with creating a simple file-share service on a local network. Every time a file is sent to your local machine, you want to ensure that it has been fully received, otherwise you signal to the user that an error has occurred. Using a Tribool in this situation provides a simple way to check if a file has been received, failed to be received, or is pending, without needing a work-around. A common approach is to create two individual booleans in order to allow for a third state, but this is wasteful and not necessary with the addition of Tribool.

Returning to our payroll system from before, here's another application:
```
/In header: #include <boost/logic/tribool.hpp>

//Updated Employee class now holds overtime
class Employee{
    public:
        string name, job;
        tribool overtime; //Have they worked overtime this week?
    
    private:
        int salary;
};

```
In the employee class, we can add a parameter for overtime which utilizes Tribool. Say that at the company there are two big programs which work simultaneously on the stable vector holding all the Employee data. The first is, of course, our payroll system, and the second is a program records the hours each employee has worked. This second program is constantly reading and writing to the vector throughout the week, updating it every few minutes. As such, our payroll program may know when someone has worked overtime until they've already clocked out for the day, which is conveniently when they're expecting their paycheck. By using a Tribool rather than a standard two state boolean, we can keep track of the employees who have possibly worked overtime, by flagging them as indeterminate (or pending) rather than simply writing them off as false. In fact, we can even rename this third state to something more descriptive:
```
//In header: #include <boost/logic/tribool/hpp>
class Employee{
    //...etc, etc, etc
};

int main(){
    BOOST_TRIBOOL_THIRD_STATE(potentialOverTime);
    //...etc, etc, etc

    return 0;
}
```
##Three-valued Logic
In addition to their tri-state attributes, Tribools also serve as a medium for three-valued logic, meaning they can be combined with boolean operators && and || in order to create more complex comparisons. Below is a trinary table for AND and OR logic, which can be applied to Tribool:

A && B| B
------|------
      | - F U T
A     | F F F F
A     | U F U U
A     | T F U T

A or B| B
------|------
      |- F U T
A     | F F U T
A     | U U U T
A     | T T T T

Since Tribool works with the && and || operators, it's easy to implement these comparisons into c++ code. Not only does this create more depth in the programs, but it also serves to preserve the unknown state after comparison, allowing Tribool to easily replace booleans in older code you've written. Overall, Tribools have great potential for creating safer programs, which can react more gently to thrown errors and exceptions.

