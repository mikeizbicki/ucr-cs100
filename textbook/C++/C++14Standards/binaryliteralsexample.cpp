#include <iostream>

using namespace std;

int main() {
	// Example of C++14 support of binary literals
	// Numeric literals specified in binary form

	// Decimal literals
	int deci = 10;              // the number 10 in decimal
	cout << "deci (no prefix required) = ";
	cout << deci << endl;       // should print the number 10 as expected

	// octal support using the 0 prefix
	int oct = 024;              // equivalent to 20 in decimal
	cout << "oct (0 prefix) = ";
	cout << oct << endl;        // should print the decimal representation of value in oct

	// hexidecimal support using the 0x prefix
	int hexi = 0x16D;           // equivalent to 365 in decimal
	cout << "hexi (0x prefix) = ";
	cout << hexi << endl;       // should print the decimal representation of value in hexi

	cout << endl;

	// ******** NEW ******** Binary Literals supported in new standard using
	// either the 0B or 0b prefix
	int AM = 0b11111001010;     // the number 1994 in binary using the 0b prefix
	cout << "AM (0b prefix) = ";
	cout << AM << endl;         // should print the decimal representation of value in AM

	int CB = 0B11111000111;     // the number 1991 in binary using the 0B prefix
	cout << "CB (0B prefix) = ";
	cout << CB << endl;         // should print the decimal representation of value in CB

	cout << endl;

	// no specification will result in the compiler interpreting
	// the number as the default deciamal integer
	int six = 110;              // the number 6 in binary not using any prefix
	cout << "six (no prefix) = ";
	cout << six << endl;        // should NOT print the decimal representation 6
															// since no prefix was specified
	                            // instead defaults to decimal and prints 110 since
	                            // no prefix was specified. This applies to all
	                            // numeral systems as well.

	cout << endl;

	// binary literals can be used wherever an constant integral type is expected
	// example 1) comparison
	cout << "100101 = " << 0b100101 << endl;
	cout << "11001 = " << 0b11001 << endl;
	cout << "comparison: (100101 < 11001) == ";
	if(0b100101 < 0b11001) {
		cout << "TRUE" << endl;
	}
	else {
		cout<< "FALSE" << endl;
	}
	cout << "comparison: (100101 > 11001) == ";
	if(0b100101 > 0b11001) {
		cout << "TRUE" << endl;
	}
	else {
		cout<< "FALSE" << endl;
	}

	cout << endl;

	// example 2) char casting spells out
	// "I used Binary Literals."
	unsigned char ASCII_letters[0b00010111];
	ASCII_letters[0b00000000] = 0b01001001; // equivalent to 73 in decimal or ASCII letter 'I'
	ASCII_letters[0b00000001] = 0b00100000; // equivalent to 32 in decimal or ASCII letter ' '
	ASCII_letters[0b00000010] = 0b01110101; // equivalent to 117 in decimal or ASCII letter 'u'
	ASCII_letters[0b00000011] = 0b01110011; // equivalent to 115 in decimal or ASCII letter 's'
	ASCII_letters[0b00000100] = 0b01100101; // equivalent to 101 in decimal or ASCII letter 'e'
	ASCII_letters[0b00000101] = 0b01100100; // equivalent to 100 in decimal or ASCII letter 'd'
	ASCII_letters[0b00000110] = 0b00100000; // equivalent to 32 in decimal or ASCII letter ' '
	ASCII_letters[0b00000111] = 0b01000010; // equivalent to 66 in decimal or ASCII letter 'B'
	ASCII_letters[0b00001000] = 0b01101001; // equivalent to 105 in decimal or ASCII letter 'i'
	ASCII_letters[0b00001001] = 0b01101110; // equivalent to 110 in decimal or ASCII letter 'n'
	ASCII_letters[0b00001010] = 0b01100001; // equivalent to 97 in decimal or ASCII letter 'a'
	ASCII_letters[0b00001011] = 0b01110010; // equivalent to 114 in decimal or ASCII letter 'r'
	ASCII_letters[0b00001100] = 0b01111001; // equivalent to 121 in decimal or ASCII letter 'y'
	ASCII_letters[0b00001101] = 0b00100000; // equivalent to 32 in decimal or ASCII letter ' '
	ASCII_letters[0b00001110] = 0b01001100; // equivalent to 76 in decimal or ASCII letter 'L'
	ASCII_letters[0b00001111] = 0b01101001; // equivalent to 105 in decimal or ASCII letter 'i'
	ASCII_letters[0b00010000] = 0b01110100; // equivalent to 116 in decimal or ASCII letter 't'
	ASCII_letters[0b00010001] = 0b01100101; // equivalent to 101 in decimal or ASCII letter 'e'
	ASCII_letters[0b00010010] = 0b01110010; // equivalent to 114 in decimal or ASCII letter 'r'
	ASCII_letters[0b00010011] = 0b01100001; // equivalent to 97 in decimal or ASCII letter 'a'
	ASCII_letters[0b00010100] = 0b01101100; // equivalent to 108 in decimal or ASCII letter 'l'
	ASCII_letters[0b00010101] = 0b01110011; // equivalent to 115 in decimal or ASCII letter 's'
	ASCII_letters[0b00010110] = 0b00101110; // equivalent to 46 in decimal or ASCII letter '.'
	for(auto i = 0b00000000; i < 0b00010111; ++i) {
		cout << ASCII_letters[i];
	}
	cout << endl;

	// unfortunately there is no "std::bin" manipulators for binary like there are
	// in octal and hexidecimal number systems yet.

	return 0;
}
