#include <signal.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void handler(int i)
{
    char *c=0;
    if (i==SIGSEGV) cerr << "don't panic!" << endl;
    if (i==SIGINT)  cerr << "panic!"       << *c << endl;
    exit(0);
}

int main()
{
    oct(cout);
    cout << SIGSEGV << endl;
    cout << SIGINT << endl;
    //handler(0);
    signal(SIGSEGV, handler);
    signal(SIGINT, handler);
    while(true);
    return 0;
}
