#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main()
{
	string str = ",Flappy;Bird:All good,";
	escaped_list_separator<char> sep("", ",;:", "");
	tokenizer<escaped_list_separator<char>> mytok(str, sep);

	cout << "Original String: " << str << endl;
	for(auto iter = mytok.begin(); iter != mytok.end(); ++iter)
	{
		cout << "Token: " << *iter << endl;
	}

	return 0;
}
