#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
using namespace std;

#define NOFLAG  0
#define l 1
#define R 2
#define a 4

//struct foo { int x; int y; crazy c; };

#define mkStruct(name) struct name {int x; int y; char c; }

mkStruct(s1);
mkStruct(s2);

#define Min(x,y) (x<y?x:y)

int f(int x, int y)
{
    if (x<y) return x;
    else return y;
}

void open2(char*file, int flags)
{
    if (flags&O_APPEND) {
        cout << "O_APPEND" << endl;
    }
    if (flags&O_ASYNC) 
        cout << "O_ASYNC" << endl;
}

int main(int argc, char**argv)
{
    s1 test;
    test.x=5;
    test.y=23;
    test.c='a';

    cout << Min(1,23) << endl;
    cout << f(1,23) << endl;

    //int x = 1025 >> 3;
    //
    //cout << "x: " << x << endl;

    //open2("test",
                  //O_APPEND|O_ASYNC
                  //);

    //cout << O_APPEND << endl;
    //cout << O_ASYNC << endl;
    //cout << pow(2,13) << endl;

    /*
    unsigned int flags 
        = NOFLAG | a | l;

    cout << "l: " << l << endl;
    cout << "flags: " << flags << endl;
    cout << "flags & l: " << (flags&l)
         << endl;

    if (flags & R) {
        cout << "flag -R was passed";
        cout << endl;
    }
    */

    //unsigned int x=NOFLAG | l | R;
    //unsigned int y=NOFLAG | R | a;

    //cout << "x: " << x << endl;
    //cout << "y: " << y << endl;

    //cout << "x&y:" << (x&y) << endl;
    //cout << "x|y:" << (x|y) << endl;
    //cout << "x^y:" << (x^y) << endl;
    //cout << "~y:" << (~y) << endl;

    return 0;
}
