#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 

int main() 
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c', 'D','Z','1','0'};
	int elements = strlen(array); 
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
