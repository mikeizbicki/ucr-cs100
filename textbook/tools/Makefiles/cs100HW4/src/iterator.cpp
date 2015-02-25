#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	cout << "Contents of vector: ";
	for(auto iterator = vec.begin(); iterator != vec.end(); iterator++)
	{
		cout << *iterator << " "; 
	}
	cout << endl;
	return 0;
}
