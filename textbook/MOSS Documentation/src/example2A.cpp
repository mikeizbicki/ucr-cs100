#include <iostream>

using namespace std;

int main()
{
	unsigned int num1, num2, choice;
	double result;
	cout << "Please Enter in the first number to calculate" << " ";

	cin >> num1;
	cout << "Please enter in your second number to calculate" << " ";
	cin >> num2;
	cout << "Please select the number which mathetical operation you would like to perform";
	cout << endl << "Addition: 1";
	cout << endl << "Subtration: 2";
	cout << endl << "Multiplication: 3";
	cout << endl << "Division: 4" << endl;
	cin >> choice;

	if(choice == 1)
	{
		result = num1 + num2;
	}
	else if(result == 2)
	{
		result = num1 - num2;
	}
	else if(result == 3)
	{
		result = num2 * num1;
	}
	else
	{
		result = num1 / num2;
	}
	cout << "And your result is: " <<result << endl;



}