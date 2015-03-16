#include <iostream>

using namespace std;

int main() {
	// quick example on Digit separators and how they improve readability and
	// nothing more.

	// A single-quote character can be used arbitratily as a digit separator in
	// numeric literals
	// for example it can be used to separate digits into thousands
	auto int_lit = 1000000;             // this is an example of an integer literal
																			// with bo digit separators
	auto int_lit_digseps = 1'000'000;   // this is the same number ad the one
																			// but this one uses digit separators
	// both int_lit_digseps and int_lit contain the same exact number one-million
	// so both statemnts below print the same number to stdout
	cout << int_lit << endl;
	cout << int_lit_digseps << endl;

	cout << endl;

	// digit separators can be extended to work for floating point literals as
	// well and in general work for all number literal types like octal, hex, and
	// even Binary
	// below is an example of how digit separators can be used in floating point
	// representations of numerals
	auto float_lit = 0.000153;
	auto float_lit_digseps = 0.000'153;
	cout << float_lit << endl;
	cout << float_lit_digseps << endl;

	cout << endl;

	// and binary representations of numbers
	auto bin_lit = 0b010011000110;
	auto bin_lit_digseps = 0b0100'1100'0110;
	cout << bin_lit << endl;
	cout << bin_lit_digseps << endl;

	cout << endl;

	// in general digit separators are intended to improve code readability
	// they generally make numbers easier for human eyes to read since we are all
	// used to seeing digits separated by thousands but they can be used
	// arbitrarily and in no specific pattern
	// for example
	auto tenmilli = 10000000;
	auto tenmilli_digseps = 1'0'0'000'00; // this form of digit separating follows
	                                      // known standard for separating digits
	                                      // but still as mentioned above both
	                                      // variables hold the same exact numeric
	                                      // value ten-million
	cout << tenmilli << endl;
	cout << tenmilli_digseps << endl;

	// why we use digit separators?
	// the question is easily answered using another question
	// which of the following is easier to read
	// 478628904483 or 478'628'904'483

	// Again they can be used to improve
	// aesthetic readability. It does not affect the numeric value.

	return 0;
}
