#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// simple function using return type deduction
auto foo() { // deduced to return int
	return 47;
}

// a more omplicated return type since the initial types are unknown until
// function is used
template<typename T, typename U>
auto multiply(T t, U u) { // deduced to return type of (t * u)
    return t * u;
}

// ever dealt with functions returning vectors of 2d matrices or something
// similar?
template<typename T>
auto twoDeevec(int rows, int columns, T t) {
	vector<vector<T> > matrix;
	vector<T> vec;
	for(auto i = 0; i < rows; ++i) {
		for(auto j = 0; j < columns; ++j) {
			vec.push_back(j * i * t * t);
		}
		matrix.push_back(vec);
	}

	vector<vector<vector<T> > > matrixvec;
	matrixvec.push_back(matrix);

	return matrixvec;
}
// well now you can without having to worry about repeting yourself

int main() {
	// Question: when should you use this?
	// Answer: Whenever possible to avoid humen error. Why do it when the compiler
	// can do it for you? The less work you have to put in the better. Programmers
	// are lazy and dont want the extra, unnecessary keystrokes.

	// example 2) uses the simple function that just returns 5
	cout << foo() << endl;

	cout << endl;

	// example 3) deduces the return type of two values multiplied together
	cout << multiply(2,5) << endl;
	cout << multiply(2.5374124717,0.4216419) << endl;

	cout << endl;

	// example 4) deduces the type of a function with a complicated return type
	int n = 2;
	vector<vector<vector<int> > > examplematrixvector(twoDeevec(3,3,n));
	for(auto i = 0; i < examplematrixvector.size(); ++i) {
		for(auto j = 0; j < examplematrixvector[i].size(); ++j) {
			for(auto k = 0; k < examplematrixvector[i][j].size(); ++k) {
				cout << examplematrixvector[i][j][k] << ' ';
			}
		}
	}

	// Return type deduction can be used in many ways
	// though it is best used in situations where it can make your code cleaner
	// and speed up the coding process

	return 0;
}
