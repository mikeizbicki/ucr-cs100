#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 
int main()
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3; 
	sort(&array[3], &array[3] + elements);//This case only d, k, b are sorted, and others remain the same.
	for (int i = 0; i < strlen(array); ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
