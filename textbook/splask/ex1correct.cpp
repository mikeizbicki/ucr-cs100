#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

vector<int> getPrimes(int max)
{
	vector<int> result;

	for (int i = 2; i < max; i++)
	{
		bool isPrime = true;
		if (floor(sqrt(i) ) == sqrt(i) )
		{
			isPrime = false;
			continue;
		}
		for (int j = 2; j <= sqrt(i); j++)
		{
			if (i % j == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime) result.push_back(i);
	}
	return result;
}

int main(int argc, char** argv)
{

	if (argc < 2)
	{
		cerr << "Usage: ./a.out <number>\n";
		return 1;
	}
	vector<int> primes = getPrimes(atoi(argv[1]) );
	for (int i = 1; i < argc; i++)
	{
		int x = atoi(argv[i]);
		bool isPrime = true;

		if (x < 2)
		{
			cerr << x << ": Must be an integer greater than 1\n";
			continue;
		}
		cout << x << " = " << flush;
		for (int j = 0; j < primes.size(); j++)
		{
			int factorPower = 0;
			while (x % primes[j] == 0)
			{
				factorPower++;
				x /= primes[j];
				isPrime = false;
			}
			if (factorPower)
			{
				cout << '(' << primes[j];
				if (factorPower > 1) cout << '^' << factorPower;
				cout << ") * ";
			}
		}
		if (isPrime) cout << "Prime";
		else cout << "\b\b\b   \b\b\b";
		cout << endl;
	}
}
