#include <fcntl.h>
#include <iostream>
#include <iomanip>
using namespace std;

//#define PROBLEM2(x) ((x ^ 3)\
//| (x & O_WRONLY)\
//| (x & O_RDWR))

//#define PROBLEM3(x) ~(0xfff7|(x&O_WRONLY))
#define PROBLEM3(x) !(x&O_WRONLY)

int main()
{
    int x=10;
    cout << "x=" << (~x) << endl;
    cout << "<<" << x<<1 << endl;
    //oct(cout);
    cout << (O_RDONLY | O_WRONLY) << endl;
    cout << (O_RDONLY & O_RDWR  ) << endl;
    cout << (O_APPEND ^ O_CREAT ) << endl;

    cout << endl;
    cout << PROBLEM2(O_RDONLY) << endl;
    //cout << PROBLEM2(O_WRONLY) << endl;
    //cout << PROBLEM2(O_RDWR  ) << endl;
    cout << endl;
    //cout << PROBLEM2(O_RDONLY | O_WRONLY )
    //     << endl;
    //cout << PROBLEM2(O_CREAT ) << endl;
    //cout << endl;
    //cout << PROBLEM2(O_RDONLY) << endl;

    return 0;
}
