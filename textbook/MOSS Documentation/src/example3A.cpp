#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	int rand_num;
	int input;
	cout << "Welcome to the randome number generation guessing game, please enter your guess, it is between 1 - 5. You have 5 tries." << endl;
	int guess;
	srand(time(NULL));
	rand_num = rand() % 6;

	for(int x = 5; x > 0; x--)
	{
		cout << "Lives left: " << x << endl;
 		cin >> input;
 		switch(input)
 		{
			case input == rand_num:
			{
				cout << "hooray you win" << endl;
				break;
			}
			case abs(input - rand_num) < 4:
			{
				cout << "you're getting close" << endl;
			}
			case abs(input - rand_num) < 2:
			{
				cout << "you're so close I can see victory" << endl;
			}
			case abs(input - rand_num) < 1:
			{
				cout << "you're one off, just one more time" << endl;
			}
		}
	}

}