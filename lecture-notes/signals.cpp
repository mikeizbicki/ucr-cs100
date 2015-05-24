#include <iostream>
#include <signal.h>
using namespace std;

//typedef void (*sighandler_t)(int);

void handle(int x)
{
    if (x==SIGINT)
        cout << "hello world" << endl;
}

void mysignaltest(void (*f)(int))
{
    f(5);
}

void nothing()
{
    while(1);
}

int main()
{
    //mysignaltest(handle);
    signal(SIGINT, handle);
    nothing();
    //while(1) {
    //}
    return 0;
}
