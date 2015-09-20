#include <iostream>
#include <string>

using namespace std;

void output_name(string name)
{
	cout << "Hello there " << name << endl;
}

void input_age()
{
	cout << "Please enter in your age ";
	unsigned int age = 0;
	cin >> age;
	if(age != 0)
	{
		if(age > 0 && age <= 12)
		{
			cout << "you're a youngster" << endl;
		}
		else if(age >= 13 && age < 21)
		{
			cout << "you must be a teenager than" << endl;
		}
		else if(age >= 21 && age < 40)
		{
			cout << "you're still a kid at heart" << endl;
		}
		else if(age >= 40 && age < 60)
		{
			cout << "you are still in your golden years" << endl;
		}
		else if(age >= 60)
		{
			cout << "you should definitely consider retirement" << endl;
		}
	}
}

int main()
{
	cout << "Please enter in your name ";
	string your_name = "";
	getline(cin, your_name);
	output_name(your_name);	
	input_age();
}
