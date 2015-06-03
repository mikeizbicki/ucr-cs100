//This is an example of what a map might look like in an "ls" program
#include <iostream>
#include <map>

using namespace std;

//you can enable this and replace all the "void(*)()" with "fun_ptr"
//Try it!
//typedef void (*fun_ptr)();

void printAll();
void printLong();
void printRecursive();
 
int main(int argc, char* argv[]) {
    
    //create and initialize map
    map<string, void(*)()> flag_functions;
    flag_functions["--all"]         = printAll;
    flag_functions["-a"]            = printAll;
    flag_functions["--long"]        = printLong;
    flag_functions["-l"]            = printLong;
    flag_functions["--recursive"]   = printRecursive;
    flag_functions["-R"]            = printRecursive;
    //...
    //...

    for(int i = 1 ; i < argc ; i++) {
        void (*fp)() = flag_functions[string(argv[i])];
        //ALWAYS CHECK FOR NULL!
        //If fp is a null pointer, running fp() will seg fault!
        if(fp != NULL) fp();
        else cout << "invalid flag: " << argv[i] << endl;
    }
}

void printAll() { cout << "printed All" << endl;}
void printLong() {cout << "printed Long" << endl;}
void printRecursive() {cout << "printed Recursive" << endl;}
