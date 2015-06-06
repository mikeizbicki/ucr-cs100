#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
using namespace std;

//Need a list "names.txt" at least 400 lines long
//Need output file "class.txt"

int main() {
	//Compile list of names in names.txt
	vector<char> grades = {'A','B','C','D','F'};
	vector<string> names;
	ifstream inFS("names.txt");
	string name;
	if (inFS.is_open()){
		while(getline (inFS, name))
			names.push_back(name);
		inFS.close();
	}
	else {
		cout <<"Error: cannot open file\n";
		exit(1);
	}

	//Generate class
	srand (time(NULL));
	unsigned printNum, numToPrint, teacher, student, grade;
	ofstream outFS;
	outFS.open("../class.txt");

	numToPrint = rand() % 15 + 6;
	for (unsigned i = 0; i < numToPrint; i++){
		printNum = rand() % 15 + 6;
		teacher = rand() % names.size();
		outFS << "Class #" << i+1 << " taught by " << names.at(teacher)  << endl;
		names.erase(names.begin() + teacher);
		for (unsigned j = 0; j < printNum; j++){
			student = rand() % names.size();
			grade = rand() % grades.size();
			outFS << left << setw(1) << "\t"
						<< setw(25) << names.at(student) 
						<< right << setw(20) << "Grade: " << grades.at(grade) << endl;
			names.erase(names.begin() + student);
		}
	}

	outFS.close();
	return 0;
}
