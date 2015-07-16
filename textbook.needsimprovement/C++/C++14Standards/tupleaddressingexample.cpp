#include <iostream>
#include <tuple>
#include <algorithm>

using namespace std;

int main(int argc, const char **argv) {
	// A quick example on tuple addressing by type

	// I - declaration to tuple using initializer list
	std::tuple<int, int, string> myTuple(1,2,"I am a String");

	// II - getting tuple element value by argument number (like in C++11)
	cout << "First tuple int: " << std::get<0>(myTuple) << endl;
	cout << "Second tuple int: " << std::get<1>(myTuple) << endl;
	cout << "Tuple string: " << std::get<2>(myTuple) << endl;

	// III - getting tuple element via type name (new in C++14)
	cout << "Get tuple string element by type: " << std::get<string>(myTuple) << endl;

	// VI - unable to get tuple int element by type because it is ambiguous
	// comment out the line and the program will compile
	cout << "First tuple int by type: " << std::get<int>(myTuple) << endl;

	// Also If the declaration of the tuple were instead
	// std::tuple<bool, int, string> myTuple(1,2,"myString");
	// a statement like
	// cout << "First tuple int by type: " << std::get<int>(myTuple) << endl;
	// would print the number 2 to stdout

	return 0;
}
