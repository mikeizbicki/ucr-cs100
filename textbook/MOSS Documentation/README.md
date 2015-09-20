# How to cheat in computer science 101

Recently I cheated in one of my core classes. 
Unfortunately I was caught, but thanks to my professor, I learned how the system detects cheaters. 
With this newly found information, I am now able to teach **YOU** how to cheat **WITHOUT** getting caught. 


First, we need to learn exactly **HOW** the system catches us. 
The system used by most universities is called the ”Measure Of Software Similarity” or [MOSS](https://github.com/mikeizbicki/gitlearn/blob/master/scripts/moss/moss.txt) for short and was developed by Stanford. So yeah, it's pretty legit. 
MOSS is a plagiarism detection algorithm that is exceptionally complex. In its raw form, it is an [AI](https://en.wikipedia.org/wiki/Artificial_intelligence) that analyzes code line by line and compares it to other's work. Tricking it will be **VERY** hard. So, let's get started!

####Overview
In order for you to successfully cheat the system, you will need to be **dedicated** and **perseverant**. 
**You might as well just turn in the same file you got from your friend/online if you don't follow these steps**. 
Don't worry though, we will take these steps together and once you finish you will be right on your path to becoming a master cheater.

0. Learn how MOSS works
1. Master the art of changing variable names
2. Master the art of changing the structure of your code
3. Master the art of rewriting already written code
4. Submit, relax and party it up


##Lesson 0: Basics

Before starting, you will need to know a little bit of background about MOSS

* MOSS has [*Whitespace insensitivity*](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/whitespaceInsensitivity.png?token=AGDMXlo6s-UroJWXydTUacT83HGzcr0Lks5WAiGhwA%3D%3D)

	This means whitespaces won't help deceive MOSS. But, if you were smart you would already know that white space doesn't matter in source code.

* MOSS has [*Noise suppression*](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/noiseSuppresion.png?token=AGDMXi2qPFle8OUMypHdNRRHU8AhOuLKks5WAiG7wA%3D%3D)

	This means that trying to confuse the algorithm by declaring random code like `int` or `char` to create 	clutter won't work. 
	Trust me. 

* MOSS has [*Position independence*](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/positionIndependence.png?token=AGDMXpUgKjMF3MJPLgLZczRDUWyZOFyNks5WAiHRwA%3D%3D)

	This means that scrambling the order of your code  will NOT affect the discovered matches. Putting I before E does NOT apply here people. Get with the program. 
	
	*[Here](http://theory.stanford.edu/~aiken/publications/papers/sigmod03.pdf) is the documentation- directly from Stanford.*
	

##Lesson 1: Changing Variable names does NOT work

The first thing most students think of when trying to avoid getting caught is changing every instance of a variable name. In this lesson I will demonstrate why this does not work.
Changing ```int foo = 1``` to ``` int bar = 1``` isn't going to work as MOSS analyzes code by structure. 

###For Example:
```
#include <iostream>							|#include <iostream>
using namespace std;						|using namespace std;
											|
int main()									|int main()
{										 	|{
	string foo;								|    string bar;
	cout << "Please enter your name";		|    cout << "plz type in your birthname";
	cin >> foo;								|    cin >> bar;
	cout << foo << endl;					|    cout << bar << endl;
}											|}
```
In this example, the structure of the code remains constant while only the variable names are changed. 
This will not work in MOSS as minute changes are ignored.



![side by side name age code](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%201.png?token=AGDMXq2Ee9KJs79n1KGroPefHRTWTQ2lks5WBg6JwA%3D%3D)


Click here to view source code. [Example 1A](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example1A.cpp?token=AGDMXv4spGZ7AYFnalOu5IMXJ-GEFDp0ks5WBhuHwA%3D%3D) [Example 1B] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example1B.cpp?token=AGDMXn8WYspPHOnZMI4WNdCTaKuRt4i6ks5WBhuqwA%3D%3D)


![age name percentage results](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%201%20Overview.png?token=AGDMXl9jvVsNaH2WP36K8SfyiFVF6ZqBks5WBg6wwA%3D%3D)

####Conclusion
After MOSS runs, it returns a link that displays the results. 
For the example above, it said that 42 lines were matching and 96% of the code is similar. 
Usually the cheating cutoff is around 25% and below but upon clicking **src/example1A.cpp(96%)**, your TA/Professor will see all the code marked red so you best believe they will catch you.



![age name highlighting](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%201%20results.png?token=AGDMXlYRe-wWB1XXlibjrRADkoGoKmAvks5WBg7EwA%3D%3D) 

##Lesson 2: Combination of changing variable names, structure of code and text within strings

In the previous lesson, we demonstrated that changing variable names is not an adequate solution.
This time, we will change:

1. Variable names 
2. Structure of code
3. Text strings within code

Let's see how results fare this time around.

######Both programs perform the same task, but with different implementation and structure######

###For Example

```
#include <iostream>						              |#include <iostream>
using namespace std;					              |using namespace std;
												      |
void swap(int& a, int& b)		                      |void print_nums(int a, int b)
{												      |{
	int c = a;                                        |    cout << "Number1: " << a << endl;                                         
	a = b;										      |    cout << "Number2: " << b << endl;
	b = a;									          |    return;    
}											          |}    
int main()								              |int main()    
{                                                     |{   
	int a,b;                                          |    char number1;      
	cout << enter in your favorite nums: "            |    cout << "Enter num 1: ";
	cin >> a;                                         |    cin >> number1;
	cin >> b;                                         |    
	change_numbers(a,b);                              |    char number2;
	cout << "First: " << a << endl;		              |    cout << "Enter num 2: ";
   cout << "Second: " << b << endl;                   |    cin >> number2;                       
}                                                     |    
												      |    char temp = number2;
                                                      |    number2 = number1;
                                                      |    number1 = temp;
                                                      |    int num1 = int(number1);
                                                      |    int num2 = int(number2);
                                                      |    print_nums(number1, number2);
                                                      |}                                                                                                      
```

This method will help eliminate some code match with similar variables, code structure and text strings. Let's put the real example to work and see what MOSS outputs.

![register user code] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%204.png?token=AGDMXirLHFuMP7RZ6AzBMNMT3EKmLDt8ks5WBhiYwA%3D%3D)

Click here to view source code [Example 2A](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example4A.cpp?token=AGDMXntJVVRh1hhAdNnl87LjJETSQOUFks5WBhvSwA%3D%3D)
[Example 2B](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example4B.cpp?token=AGDMXszi471jf0MZed67BxyUpXy8LO6kks5WBhvjwA%3D%3D)

![register user result overview] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%204%20Overview.png?token=AGDMXoiPYbbiiWEbFafaD98N6ME9ISHLks5WBhi7wA%3D%3D)


![register user code match blocks] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%204%20Results.png?token=AGDMXrIHhwBoKJgzCNxWBNQvVpr2BKJ4ks5WBhjnwA%3D%3D)

####Conclusion

The [results] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%204%20Results.png?token=AGDMXrIHhwBoKJgzCNxWBNQvVpr2BKJ4ks5WBhjnwA%3D%3D) of our efforts have paid off. 
It only matched the [code](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%204.png?token=AGDMXirLHFuMP7RZ6AzBMNMT3EKmLDt8ks5WBhiYwA%3D%3D) inside our function when we register a user at only 36%. 
This won't be enough to throw off the system. 
A bit more work will be necessary in order to get away.

##Lesson 3: Copying and rewriting a function

When you get stuck and decide to take someone else's function, MOSS has no problem detecting and flagging it for plagarism. 
I will teach you a new way of getting around this by modifying your own function.


![random codes, one same function](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%205.png?token=AGDMXqxOXjz0_5riZFWIT_0odVsNn2o-ks5WBhkGwA%3D%3D)

Click here to view source code [Example 3A](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example5A.cpp?token=AGDMXk75AyuSRZQFsn7_iddRaJ5nNKRdks5WBhxrwA%3D%3D)
[Example 3B](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example5B.cpp?token=AGDMXglxhStqx_9TMVkMVMcIvm9MljkXks5WBhyhwA%3D%3D)



![randome codes, one function, overview] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%205%20Overview.png?token=AGDMXl0PglDCEJwh-AbGmAMQSm5wIayyks5WBhklwA%3D%3D)

![random code, one function, results] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%205%20Results.png?token=AGDMXs76Bj2Qy1YJZrNQ_ov7bKVNGL4jks5WBhk5wA%3D%3D)

####Rewriting a function

Steps to rewriting a function

1. Analyze why the code works
2. Find the difference between the working code and your nonfunctional function
4. Find the bug in your function and apply the "difference" you discovered from **Step 2**
5. Copy and paste the working code into your IDE

```
#include <iostream>						             |#include <iostream>
                                                     |
void swap_string_with_user_input(string& data)       |void swap_with_user_input(string& data)
{                                                    |{
    string user_input;                               |    cout << "Please enter a string";
    cout << "Please enter a string: ";               |    cin >> data;
    getline(cin, user_input);                        |    return;
    data = user_input;                               |}
    return;                                          |
}                                                    |
```


##Lesson 4: If-else statements to switch statements

One fundamental part of programming is the ability to perform loops and conditional statements. 
If and else statements are something programmers are most familar with. 
I am going to now introduce you to a switch statement. 
Switch statements are exactly the same as if and else statements, only their appearance is different.



Below are the differences:

```
If-else statement						        |Switch Statements
                                                |
#include <iostream>							    |#include <iostream>
using namespace std;                            |using namespace std;
int main()                                      |int main()
{							                    |{
	int age;						            |    int age;
	cout << "Enter in your age ";               |    cout << "Enter in your age ";
	cin >> age;						            |    cin >> age;
	if(age >= 21)                               |    switch(age)
	{                                           |    { 
		cout << "you are an adult" << endl;     |         case age >= 21;
	}								            |         {
	if(age > 13 && age < 21)                    |             cout << "you are an adult" << endl;
	{                                           |         }
		cout << "teenager" << endl;             |         case age > 13 && case age < 21;
	}                                           |         {
	else                                        |             cout << "teenager" << endl;      
	{                                           |         }
		cout << "child" << endl;                |         case age;
	}					                        |         {
}	                                            |             cout << "child" << endl;
                                                |         }
                                                |    }
                                                |}
```



![guessing game pic of code](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%203.png?token=AGDMXoIdtsWOA6wn85yk1g25ACPlRDmSks5WBhmiwA%3D%3D)




Click here to view source code [Example 4A](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example3A.cpp?token=AGDMXtFmYh2EqfKtj9AsCEfdzTjhsOUyks5WBhy3wA%3D%3D) [Example 4B] (https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/src/example3B.cpp?token=AGDMXhgz1v5CtCZOeaEQjI-t08taD5rvks5WBhzJwA%3D%3D)

![guessing game results](https://raw.githubusercontent.com/hkwan003/Moss_Documentation/phone/images/Example%203%20Overview.png?token=AGDMXnaVbgXWyTKEye0TPFvDyLxFp6lyks5WBhm3wA%3D%3D)


##Conclusion

So if you are able to change all the variable names, the structure of the code, modify functions, change if statements to switch statements, and completely change your coding style, you will get away with cheating the Moss detection system( every time). 

However if you go through all this effort to cheat:
#####1. You won't learn anything 
Going through great lengths of modifying code, you might as well do the assignment and learn the material.
#####2. There's still a possibility of getting caught 
My method of beating MOSS isn't perfect.
If you follow my instructions, there is still a chance of you getting caught.
There is no fool proof way to protect cheaters.

#####3. Cheating requires just as much effort as genuinely doing the work
Modifying a homework assignment to make your own is just as much hard work as doing it yourself. Except when you do it yourself **you actually learn**.


##Background 


I am one of the students who did not follow the precautions of plagiarism. 
I took the risk and got caught. Writing this document was my punishment.

I got a low grade on an assignment, I was too preoccupied to complete the regrade at the end of the quarter so I cheated.

I took a previous cs100 student's working code.
I modified it, changed the code around and submitted it. 
My code was flagged by Moss and I did not want to risk expulsion so I admitted to everything.













