#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void function(int sig)
{
    //if (sig==SIGINT) // not needed
        cerr << "inside function"
             << endl;

    alarm(1);
}

int main ()
{
    //function(0);
    //signal(SIGINT,function);
    signal(SIGALRM,function);
    alarm(1);
    //while (true) {
        //sleep(1);
        //cerr << "hello" << endl;
        //}
    return 0;
}
