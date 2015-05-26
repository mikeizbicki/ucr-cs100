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
