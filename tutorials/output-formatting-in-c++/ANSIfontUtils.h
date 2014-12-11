#include <string>
#include <iostream>

using namespace std;

string fgBlack = "\033[30m";
string fgRed = "\033[31m";
string fgGreen = "\033[32m";
string fgYellow = "\033[33m";
string fgBlue = "\033[34m";
string fgPurple = "\033[35m";
string fgTeal = "\033[36m";
string fgWhite = "\033[37m";

string bgBlack = "\033[40m";
string bgRed = "\033[41m";
string bgGreen = "\033[42m";
string bgYellow = "\033[43m";
string bgBlue = "\033[44m";
string bgPurple = "\033[45m";
string bgTeal = "\033[46m";
string bgWhite = "\033[47m";


string underline = "\033[4m";
string bold = "\033[1m";

string reset = "\033[0m";//resets to terminal's default colors


//FOREGROUND COLOR
string mkfgBlack(string in){
	return fgBlack + in + reset;
}

string mkfgRed(string in){
	return fgRed + in + reset;
}

string mkfgGreen(string in){
	return fgGreen + in + reset;
}

string mkfgYellow(string in){
	return fgYellow + in + reset;
}

string mkfgBlue(string in){
	return fgBlue + in + reset;
}

string mkfgPurple(string in){
	return fgPurple + in + reset;
}

string mkfgTeal(string in){
	return fgTeal + in + reset;
}

string mkfgWhite(string in){
	return fgWhite + in + reset;
}


//BACKGROUND COLOR
string mkbgBlack(string in){
	return bgBlack + in + reset;
}

string mkbgRed(string in){
	return bgRed + in + reset;
}

string mkbgGreen(string in){
	return bgGreen + in + reset;
}

string mkbgYellow(string in){
	return bgYellow + in + reset;
}

string mkbgBlue(string in){
	return bgBlue + in + reset;
}

string mkbgPurple(string in){
	return bgPurple + in + reset;
}

string mkbgTeal(string in){
	return bgTeal + in + reset;
}

string mkbgWhite(string in){
	return bgWhite + in + reset;
}


//Misc
string mkUnderline(string in){
	return underline + in + reset;
}

string mkBold(string in){
	return bold + in + reset;
}

void resetTerminalColors(){
	cout << reset;
}

