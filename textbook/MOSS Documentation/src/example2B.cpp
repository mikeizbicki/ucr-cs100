#include <iostream>

using namespace std;


void do_math()
{
	cout << "Please input your first number" << " ";
	unsigned int foo1;
	cin >> foo1;
	cout << endl;
	cout << "Please enter in yoru second selection" << " ";
	unsigned int foo2;
	cin >> foo2;
	cout << endl;
	cout << "Please pick what operation you wanna perform. input your response (add, subtract, mult, divide)" << endl;
	cout << "input your response" << " ";
	string selection;
	cin >> selection;
	double answer;
	if(selection == "add")
	{
		answer = foo1 + foo2;
	}
	else if(selection == "subtract")
	{
		answer = foo1 - foo2;
	}
	else if(selection == "mult")
	{
		answer = foo1 * foo2;
	}
	else if(selection == "divide")
	{
		answer = foo1 / foo2;
	}
	cout << "Outputting your answers right now " << answer << endl;
}


int main()
{
	do_math();
}