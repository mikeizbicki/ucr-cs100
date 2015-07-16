#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main()
{
	string str = "626123456790912345678";
	vector<int> offsets = {3, 3, 4};
	offset_separator sep(offsets.begin(), offsets.end());
	tokenizer<offset_separator> mytok(str, sep);

	cout << "Original String: " << str << endl;
	for(auto iter = mytok.begin(); iter != mytok.end(); ++iter)
	{
		cout << "Token: " << *iter << endl;
	}

	return 0;
}
