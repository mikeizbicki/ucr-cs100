We often encounter situations that requires us to sort an array in a particular order in daily life. As is known, in CS 100, we are required to sort our file display alphabetacially in "ls" function. Instead of writing it ourselves, we could use the C++ Standard Library `sort` with less codes and higher efficiency.

It takes two random-access iterators, the start and the end, as arguments and performs a comparison sort on the range of elements between the two iterators, front-inclusive and end-exclusive: [start, end). The sort function is included from the algorithm header of the C++ Standard Library, and carries three arguments: start value, end value and  Compare function. The third argument has default value - the "less-than" (<) operator to compare elements.

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
There are lots of default comparison function, such as greater<Type>、less<Type>. The 4th example is about how to sort a char array:
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
	sort(array, array + elements,less_equal<char>());
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
0 1 D Z a b c d k p s 

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
As is seen above, comparison function is a bool function that give an order between two inputs. Its return value is bool type. It returns true when the first input should be in the front in the sorted sequence. Otherwise, it returns false. In addition, valid comparison requires two const inputs. If you try to change their value, it could not pass compiler.
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

 not only from an array, but also a vector or struct.
