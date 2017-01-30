#include <iostream>
#include <string>

using namespace std;

void output_name(string birth_name)
{
	cout << "Hello there " << birth_name << endl;
}

void input_age()
{
	cout << "Please enter in your age ";
	unsigned int years_alive = 0;
	cin >> years_alive;
	if(years_alive != 0)
	{
		if(years_alive > 0 && years_alive <= 12)
		{
			cout << "you're a youngster" << endl;
		}
		else if(years_alive >= 13 && years_alive  < 21)
		{
			cout << "you must be a teenager than" << endl;
		}
		else if(years_alive >= 21 && years_alive < 40)
		{
			cout << "you're still a kid at heart" << endl;
		}
		else if(years_alive >= 40 && years_alive < 60)
		{
			cout << "you are still in your golden years" << endl;
		}
		else if(years_alive >= 60)
		{
			cout << "you should definitely consider retirement" << endl;
		}
	}
}

int main()
{
	cout << "Please enter in your name ";
	string user_name = "";
	getline(cin, user_name);
	output_name(user_name);	
	input_age();
}
