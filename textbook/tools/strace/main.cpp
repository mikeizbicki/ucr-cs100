#include <fstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
	string input = "data.dat";
	string output = "output.dat";

	ifstream fin;
	fin.open(input.c_str());

	if (!fin)
	{
		perror("open");
		exit(1);
	}

	ofstream fout;
	fout.open(output.c_str());

	if(!fout)
	{
		perror("open");
		exit(1);
	}

	fin.close();
	fout.close();

	cout << endl;
	return 0;
}
