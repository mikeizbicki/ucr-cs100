#include <iostream>
#include <cstring>

using namespace std;

void doSomething(char *ptr)
{
	char *var2 = new char[1024]; //create a new char*
	strcpy(var2, ptr);			 //copy old char* into a new char*
	cout << var2 << endl; 		 //output new char*
	//delete [] var2;
}

int main()
{
	char *var = new char[1024];	 //create char*
	string str = "hello world";  //create string to go into char*
	strcpy(var, str.c_str());    //copy string into char*
	cout << var << endl; 		 //output char*
	doSomething(var);			 //call function with char*
	//delete [] var;
	return 0;
}
