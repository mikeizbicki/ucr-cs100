#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 
int main()
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3; 
	sort(&array[3], &array[3] + elements);//sort between the 4th element and the 6th
	//This case only d, k, b are sorted.
	for (int i = 0; i < 7; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
