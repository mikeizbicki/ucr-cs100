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
