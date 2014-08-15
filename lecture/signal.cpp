#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

void dosomething(int x, char a)
    //void dosomething(int x)
{
    cerr << "did something with " 
         << x 
         << endl;
}

typedef void (*funcptr)(int,char); 
typedef int int32 ;

void foo(funcptr f)
{
    f(1,'a');
    f(2,'b');
    f(3,'c');
}

int main()
{
    foo(dosomething);
    //dosomething(1);
    signal(SIGINT,dosomething);
    while (1);
    return 0;
}
