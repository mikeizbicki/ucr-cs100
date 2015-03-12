We often encounter situations that requires us to sort an array in a particular order in daily life. As is known, in CS 100, we are required to sort our file display alphabetacially in "ls" function. Instead of writing it ourselves, we could use the C++ Standard Library `sort` with less codes and higher efficiency. Besides that, we would have some discussion about when to allocate char array pointer memory.
`sort` takes two random-access iterators, the start and the end, as arguments and performs a comparison sort on the range of elements between the two iterators, front-inclusive and end-exclusive: [start, end). `sort` function is included from the algorithm header of the C++ Standard Library, and carries three arguments: start value, end value and  Compare function. The third argument has default value - the "less-than" (<) operator to compare elements.

Sort is define as:
```
default (1)
template <class RandomAccessIterator>
  void sort (RandomAccessIterator first, RandomAccessIterator last);
custom (2)
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```
# Default(1) form
Here is a basic example for the 1st form:
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
10, 0, 5, 23
 ```
In fact, sort function sorts the successive array from the start address to the end address. Thus, it could be usde to sort only part of an array.
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
int main()
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3;
	sort(&array[3], &array[3] + elements);//This case only d, k, b are sorted.
	for (int i = 0; i < strlen(array); ++i)
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The result looks like:
```
a, p, s, b, d, k, c
```
#Custom (2) form
Sort is powerful because we could use it to get a sequence by any particular rule. It accepts two elements in the range as arguments, and returns a value convertible to bool which indicates the order. This can either be a function pointer or a function object.
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

bool compare(const char p1,const char p2)//sort descendingly
{
	if (p1>p2) return true;
	else return false;
}

int main()
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3;
	sort(&array[3], &array[3] + elements,compare);
	for (int i = 0; i < strlen(array); ++i)
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The result is:
```
a, p, s, k, d, b, c
```
##default comparison function
There are lots of default comparison function, such as greater、less. The 4th example is about how to sort a char array by default comparison:
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
	for (int i = 0; i < strlen(array); ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	sort(array, array + elements,greater<char>());
	for (int i = 0; i < strlen(array); ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
The result is not in alphabetacally order, however.
```
0 1 D Z a b c d k p s 
s p k d c b a Z D 1 0
```
##write your own comparison function
To get desired sequence, we need to write comparison function ourselves. Fistly, we look at comparison function in the 3rd example.
```
bool compare(const char p1, const char p2)//sort descendingly
{
	if (p1>p2) return true;
	else return false;
}
```
As is seen above, comparison function is a bool function that give an order between two inputs. Its return value is bool type. It returns true when the first input should be in front of the second one in the sorted sequence. Otherwise, it returns false.
The default less comparison function compares the ascii numbers of the two inputs and it returns true when the first one has a smaller ascii number than the second. In order to sort alphabetacally, we need to convert uppercase letter into lowercase. However, valid comparison requires two const inputs. If you try to change their value, it could not pass compiler.
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
Thus, to change its value, you need to pass it to a new variable first.
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
	for (int i = 0; i < strlen(array); ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
When you compare p3 and 'A', you compare the ascii numbers of 'p3' and 'A'. It is also true when you add or subtract between 'p3' and 'A'. After conversion, we compare 'p3' and 'p4'. The result looks like:
```
a b c d D k p s Z
```
##compare char array
In our homework, we are required to compare two file names, which is char arrays.
###accept char array
Initial gusses seems like:
```
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 
int main() 
{
	char array[][10] = { "abc", "pab", "slm", "dfp", "ktw", "b", "bac","DFq","Z"};
	int elements = 10; //number of example char array
	sort(array, array+elements);
	for (int i = 0; i < elements; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
```
However, it would not pass compiler. In order to pass char array to compare, we need to use char array pointer. This is the 6th example. 
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
The difference between initial guess and our 6th example is that we pass the pointer storing address in our example 6. sort accepts our char array, but there is no default comparison function to do that.
###write comparison function
Therefore, we try to write comparison function for alphabetacal order. At first, we should convert two arguments both into lowercase letters or uppercase letters. In order to do that we must assign them to two new char arrays, as two inputs are constant values.
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
Inside 'convert', we convert all the uppercase letters into lowercase letters by operating on elements' ascii number.
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
As is known, C or C++ use pointers to pass array. We return array pointer instead of array itself. 
 not only from an array, but also a vector or struct.
