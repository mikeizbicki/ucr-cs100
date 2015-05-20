#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main()
{
	string str = "Whiskers,Cat,\\\"Whiskers is very, very healthy\\\"\\nBuddy,Dog,'Buddy is healthy\\\\strong'";
	escaped_list_separator<char> sep("\\", ",\n", "\"");
	tokenizer<escaped_list_separator<char>> mytok(str, sep);

	cout << "Original String: " << str << endl;
	for(auto iter = mytok.begin(); iter != mytok.end(); ++iter)
	{
		cout << "Token: " << *iter << endl;
	}

	return 0;
}
