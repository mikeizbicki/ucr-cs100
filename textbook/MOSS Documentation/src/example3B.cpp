#include <iostream>
#include <ctime>

using namespace std;

int guess, rand_number;
int counter = 5;

int main()
{	
	int guess;
	srand(time(NULL));
	rand_number = rand() % 6;

	
	cout << "you are about to partake in my number guess game, please input your guess" << endl;
	while(counter > 0)
	{
		cin >> guess;
		if(guess == rand_number)
		{
			cout << "you guessed correctly" << endl;
			break;
		}
		else if(abs(guess - rand_number) >= 4)
		{
			cout << "you're a bit far, try again" << endl;
		}
		else if(abs(guess - rand_number) >= 2)
		{
			cout << "you're getting better, almost there" << endl;
		}
		else if(abs(guess - rand_number) >= 1)
		{
			cout << "you're just one away now, try again" << endl;
		}
		counter--;
	}
}