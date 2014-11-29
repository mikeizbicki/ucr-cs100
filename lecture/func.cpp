#include <iostream>
#include <unistd.h>
using namespace std;

bool hello(string name, int n) {
    cerr << "hello "
         << name;
    for (int i=0; i<n; i++)
         cerr << "!";
     cerr << endl;
     return true;
}

int main()
{
    bool (*foo)(string, int);
    foo=hello;
    foo("cs100",10);
    return 0;
}
