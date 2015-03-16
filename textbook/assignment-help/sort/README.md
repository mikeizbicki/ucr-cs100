We often encounter situations that require us to sort an array in a particular order. In CS 100, we are required to sort our file display alphabetacially by "ls" function. Instead of writing it ourselves, we could use the C++ Standard Library `sort` with less codes and higher efficiency. Besides, we discusses the char array pointer memory allocation.

`sort` takes two random-access iterators, the start and the end. It performs a sort on the range of elements between the two iterators, front-inclusive and end-exclusive: [start, end). `sort` function is included from the algorithm header of the C++ Standard Library, and carries three arguments: the start value, the end value, and  the compare function. The third argument has a default value - the "less-than" (<) operator to compare elements.

`sort` is defined as:
```
default (1)
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);
custom (2)
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```
#Sort(1)- default form
Here is a basic example for default form:
```
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
	int array[] = { 23, 5, -10, 0};//This is the array need to be sorted
	int elements = sizeof(array) / sizeof(array[0]);//There are 4 intergers in the array
	sort(array, array + elements);//The array is sorted and stored in the origin space
					// If you also want to keep the origin one, do not forget to store it first!
	for (int i = 0; i < elements; ++i)
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The output is:
```
-10, 0, 5, 23
 ```
It sorts all the elements between from start to end. In fact, `sort` goes over all successive arraries from the start address to the end address. Thus, it could be used to sort only some parts of an array.
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int main()
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3;
	sort(&array[3], &array[3] + elements);//sort between the 4th element and the 6th
	for (int i = 0; i < 7; ++i)
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The result may look like:
```
a, p, s, b, d, k, c//This case only d, k, b are sorted.
```
#Sort(2)- custom forms
`sort` is powerful because we can have any particular orders with compare function. It can be either a function pointer or a function object. Compare function accepts two elements in the range as arguments and returns a value convertible to boolen which indicates the order. This is the example 3, partial sort with compare function: 
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
//partial sort with compare function
bool compare(const char p1,const char p2)//sort descendingly
{
	if (p1>p2) return true;
	else return false;
}

int main()
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3;
	sort(&array[3], &array[3] + elements,compare);//This case only d, k, b are sorted.
	for (int i = 0; i < 7; ++i)
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The result is:
```
a, p, s, k, d, b, c
```
##default compare function
There are lots of default compare functions in standard library, such as greater、less with different types. The 4th example is about how to sort a char array by default:
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 

int main() 
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c', 'D','Z','1','0'}; 
	cout <<elements<<endl;
	sort(array, array + elements,less<char>());
	for (int i = 0; i < 7; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	sort(array, array + elements,greater<char>());
	for (int i = 0; i < 7; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The result is not in alphabetacally order but acsii order, however.
```
0 1 D Z a b c d k p s 
s p k d c b a Z D 1 0
```
##write your own alphabetacal compare function
To get desired sequence, we need to write compare functions ourselves. Fistly, we should look at compare function. The default `<` compares the ascii numbers with the two inputs and it returns true when the first one has a smaller ascii number than the second one.
```
bool compare(const char p1, const char p2)//sort descendingly
{
	if (p1<p2) return true;
	else return false;
}
```
It returns true when the first input should be put in the front of the second one in the sorted sequence. Otherwise, it returns false.
###convert input
In order to sort alphabetacally, we need to convert uppercase letter into lowercase. However, valid comparation requires two const inputs. If you try to change their value, it could not pass compiler.
```
bool compare(char p1,char p2)
{
	if (p1>p2)
	{
		p1="z";//p1 is changed, which is incompatible with compiler.
		return true;
	}
	else return false;
}
```
When you compile, it looks like:
```
tst.cpp: In function ‘bool compare(char, char)’:
tst.cpp:10:5: error: invalid conversion from ‘const char*’ to ‘char’ [-fpermissive]
   p1="z";
     ^
```
Although we do not announce input arguments constant, `sort` makes it default. Thus, in order to change its value, you need to pass it to a new variable first.
```
bool compare(const char p1,const char p2)
{
	char p3=p1;//p3 is not const
	char p4=p2;//p4 is not const
	...
}
```
When you look at p3 and 'A', you should compare the ascii numbers with 'p3' and 'A'. It is also true when 'p3' plus or minus 'A'.
```
bool compare(const char p1,const char p2)
{
	...
	if(p3>='A'&&p3<='Z')
		{
			p3=p3+'a'-'A';//change uppercase letter into lowercase letter
		}
		if(p4>='A'&&p4<='Z')
		{
			p4=p4+'a'-'A';
		}
		if (p3<p4) 
			return true;
		else 
			return false;
}
```

To conclude, the whole program looks like:
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 

bool compare(const char p1,const char p2)
{
	char p3=p1;//p3 is not const
	char p4=p2;//p4 is not const
	if(p3>='A'&&p3<='Z')
	{
		p3=p3+'a'-'A';//change uppercase letter into lowercase letter
	}
	if(p4>='A'&&p4<='Z')
	{
		p4=p4+'a'-'A';
	}
	if (p3<p4) 
		return true;
	else 
		return false;
}

int main() 
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c','D','Z'};
	int elements = strlen(array); 
	sort(array, array + elements,compare);
	for (int i = 0; i < 7; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
``` 
The result looks like:
```
a b c d D k p s Z
```
##Sort char arrays
In our homework, we are required to compare two file names, which are char arrays.
###pass char array
Initial gusses seems like:
```
int main() 
{
	char array[][10] = { "abc", "pab", "slm", "dfp", "ktw", "b", "bac","DFq","Z"};
	int elements = 10; //number of example char array
	sort(array, array+elements);
	...
}
```
However, it would not pass compiler. In order to pass char array to compare function, we need to give char address to char array pointer. This is the 6th example:
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 

int main() 
{
	char array[][10] = { "abc", "pab", "slm", "dfp", "ktw", "b", "bac","DFq","Z"};
	int elements = 10; 
	char *p[10];
	for(int i=0;i<10;i++)
	{
		p[i]=array[i];
	}
	sort(p, p+elements);
	for (int i = 0; i < elements; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The output looks like:
```
abc pab slm dfp ktw b bac DFq Z
```
It seems that there are no default compare functions to sort char arrays, so we write one ourselves.
###char arrays compare function
We try to write compare function for alphabetacal order. At first, we should convert both two arguments into lowercase or uppercase letters. In order to do that, we must assign them to two new char arrays; at the time the input arguments are constant values.
```
bool compare(const char *p1, const char *p2)//sort alphabetically
{
	char q1[MAXLINE];
	char q2[MAXLINE];
	strcpy(q1,p1);
	strcpy(q2,p2);
	char *q3;
	q3=convert(q1);//convert q1 to lowercase letter
	char *q4;
	q4=convert(q2);//convert q1 to lowercase letter

	if (strcmp(q3,q4)<0) //char array compare
		return true;
	else 
		return false;
}
```
Inside `convert`, we convert all the uppercase letters into lowercase ones by operating on elements' ascii number.
```
char* convert(char a[])
{
	for(int k=0;k<strlen(a);k++)
	{
		if((a[k]>='A'&&a[k]<='Z'))
		{
			a[k]=a[k]+'a'-'A';
		}
	}
	char *q=&a[0];
	return q;
}
```
As we can see, C or C++ use pointers to pass array. We return the array pointer instead of the array itself. Thus, our final sort function looks like:
```
#include <iostream>
#include <algorithm>
#include <string.h>
#define MAXLINE 10
using namespace std; 

char* convert(char *a)//remain only a~z and 0~9
{
	char *q=&a[0];
	while(strcmp(a,"\0")!=0)
	{
		if((*a>='A'&&*a<='Z'))
		{
			*a=*a+'a'-'A';
		}
		a++;
	}
	return q;
}

bool compare(const char *p1,const char *p2)//sort alphabetically
{
	char q1[MAXLINE];
	char q2[MAXLINE];
	strcpy(q1,p1);
	strcpy(q2,p2);
	
	char *q3;
	q3=convert(q1);

	char *q4;
	q4=convert(q2);

	if (strcmp(q3,q4)<0) return true;
	else return false;
}


int main() 
{
	char array[][10] = { "abc", "pab", "slm", "dfp", "ktw", "b", "bac","DFq","Z"};
	int elements = 9; 
	char *p[10];
	for(int i=0;i<9;i++)
	{
		p[i]=array[i];
	}
	sort(p, p+elements,compare);
	for (int i = 0; i < elements; ++i) 
		cout << p[i] << ' ';
	cout<<endl;
	return 0;
}
```
After you run it, the result seems like:
```
abc b bac dfp DFq ktw pab slm Z 
```
##sort other types
`sort` not only applies to an array or arrays, but also vectors or structs. This is an example of vector rewrited from wikipedia:
```
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() 
{
	vector<int> vec {10, 5, 100};
	sort(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i) 
		cout << vec[i] << ' ';
	cout<<endl;
	return 0;
}
```
This needs c++11 standard to compile. Use the command like this:
```
$g++ -g -std=c++11 8_example.cpp 
```
The output is
```
5 10 100
```
For struct, we now have another example. Initialization involves standard c++11 features, so compile it with `-std=c++11`.
```
#include <iostream>
#include <algorithm>
using namespace std;
struct data
{
	int a;
	int b;
	int c;
}; 
bool cmp(data x,data y)
{
	if(x.a!=y.a)
	{
		return x.a<y.a;
	}
	else if(x.b!=y.b)
	{
		return x.b>y.b;
	}
	else
	{
		return x.c>y.c;
	}
}
void output(struct data tst)
{
	cout<<"a="<<tst.a<<" b="<<tst.b<<" c="<<tst.c<<endl;
}
int main()
{
	struct data tst[4];
	tst[0]={3,4,2};
	tst[1]={2,4,5};
	tst[2]={2,5,5};
	tst[3]={2,5,6};
	cout<<"Before sort:"<<endl;
	for(int i=0;i<4;i++)
		output(tst[i]);
	sort(tst,tst+4,cmp);
	cout<<"After sort:"<<endl;
	for(int i=0;i<4;i++)
		output(tst[i]);
	return 0;
}
```
In this example, we sort struct by `.a` ascending order first, `.b` descending second and `.c` descending third. The result looks like:
```
Before sort:
a=3 b=4 c=2
a=2 b=4 c=5
a=2 b=5 c=5
a=2 b=5 c=6
After sort:
a=2 b=5 c=6
a=2 b=5 c=5
a=2 b=4 c=5
a=3 b=4 c=2
```
#Char array memory allocation instruction
Let us look at 7th example's compare function again.
```
bool compare(const char *p1,const char *p2)//sort alphabetically
{
	char q1[MAXLINE];
	char q2[MAXLINE];
	strcpy(q1,p1);
	strcpy(q2,p2);
	
	char *q3;
	q3=convert(q1);

	char *q4;
	q4=convert(q2);

	if (strcmp(q3,q4)<0) return true;
	else return false;
}
```
We use char arrray pointers without memory allocation and there is no memory leak. Because the message is stored at its origin char array, there is no need to allocate another space for the pointer. In some sence, origin char array seems like a container. The message already had a container for itself, and then it does not require new place for storage.
##no origin char array
What if there is no origin container? It means there is no origin char array. Then, you need to allocate some memory space to store the message and free it when you finish. Look at the 10th example to compare:
```
bool compare(const char *p1,const char *p2)//sort alphabetically
{
	char q1[MAXLINE];
	//char q2[MAXLINE];
	strcpy(q1,p1);
	//strcpy(q2,p2);
	
	char *q3;
	q3=convert(q1);

	char *q4=(char*)malloc(MAXLINE*sizeof(char));//allocate memory to char array pointer
	*q4=*p2;//pass p2 value to q4
	q4=convert(q4);

	if (strcmp(q3,q4)<0) 
	{
		free(q4);
		return true;
	}
	else 
	{
		free(q4);
		return false;
	}
}
```
We use `valgrind` to test:
```
==24216== HEAP SUMMARY:
==24216==     in use at exit: 0 bytes in 0 blocks
==24216==   total heap usage: 31 allocs, 31 frees, 310 bytes allocated
==24216== 
==24216== All heap blocks were freed -- no leaks are possible
```
It looks fine. Also, we have the same result as before:
```
abc b bac dfp DFq ktw pab slm Z
```
##diffrence about these two versions
These two versions have the same result. In the first program, `q4` is just a nickname for us to operate the char array, and `q2`stores it . In the second one, `q4` is allocated memory space manully by `malloc` to store it. The `malloc` would necessarily come with the `free` at last. They both use the same amount of space to store the message.

The advantage of first version is that you do not need to free it. Therefore, you do not need to consider when to free it. The advantage of second version is that you could allocate memory dynamically to save memory. To be more detailed, it looks like:
```
char *q4=(char*)malloc(strlen(p2)*sizeof(char));
```
The disadvantages are the opposite.

In conclusion, `malloc` and `free` make the system work efficient while you need to consider when to free memory carefully. Using only char array without `malloc` is easy but inefficient. As the data increases, dynamic memory allocation saves lots of spac, but it also makes it more difficult for you to decide when to free memory. Just like the olding saying goes: "every coin has two sides". It is up to you to descide which version to use.
