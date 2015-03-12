#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std; 

bool compare(const char p1,const char p2)
{
	if (p1>p2) return true;
	else return false;
}

int main() 
{
	char array[] = { 'a', 'p', 's', 'd', 'k', 'b', 'c'};
	int elements = 3; 
	sort(&array[3], &array[3] + elements,compare);
	for (int i = 0; i < 7; ++i) 
		cout << array[i] << ' ';
	cout<<endl;
	return 0;
}
