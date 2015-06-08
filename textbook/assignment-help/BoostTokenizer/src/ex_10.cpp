#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main()
{
	string str = "626123456790912345678";
	int offsets[] = {3, 3, 4, 1, 2, 3};
	offset_separator sep(offsets, offsets+3);
	tokenizer<offset_separator> mytok(str, sep);

	cout << "Original String: " << str << endl;
	for(auto iter = mytok.begin(); iter != mytok.end(); ++iter)
	{
		cout << "Token: " << *iter << endl;
	}

	return 0;
}
