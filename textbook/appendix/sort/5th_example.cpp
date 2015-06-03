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
}
