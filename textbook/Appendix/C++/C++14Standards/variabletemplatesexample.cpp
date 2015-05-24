#include <iostream>
#include <iomanip>

using namespace std;

//used in example 1
template<class T>
constexpr T pi = T(3.1415926535897932385);  // variable template

template<class T>
T circumfrence(T r) { // function template
  return ((pi<T> * r) + (pi<T> * r)); // pi<T> is a variable template instantiation
}

int main() {
	// example on templated variables

	// example 1) Given in the proposal is a variable pi that can be
	// read to get the value of pi for various types such as int and double
	cout << setprecision(50);
	// Actual value of pi to 50 digits
	cout << "exact value (to 50 digits): " << 3.141592653589793238462643383279502884197169399375 << endl;

	cout << setprecision(15);
	// pi when int passed in
	cout << "int: " << pi<int> << endl;         // returns pi with int precision

	// pi when double passed in
	cout << "double: " << pi<double> << endl;   // returns pi with double precision

	cout << endl;

	// also given in the proposal uses the value of pi with different
	// precision types to find the circumfrence of a circle of radius r. The specified precision
	// used for r will be the one pi will be set to
	int r = 2;                        // integer precision
	cout << circumfrence(r) << endl;  // will evaluate 3*2 + 3*2 ant print result to stdout

	double R = 0.333333333333333;			// double precision
	cout << circumfrence(R) << endl;  // will evaluare pi<double>*r + pi<double>*r and print result
																		// to stdout in double precision
	return 0;
}
