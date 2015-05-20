#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main()
{
	string str = "\\\"Octocat\\\",\"Half cat, half octupus\",Github's official mascot";
	escaped_list_separator<char> sep;
	tokenizer<escaped_list_separator<char>> mytok(str, sep);

	cout << "Original String: " << str << endl;
	for(auto iter = mytok.begin(); iter != mytok.end(); ++iter)
	{
		cout << "Token: " << *iter << endl;
	}

	return 0;
}
