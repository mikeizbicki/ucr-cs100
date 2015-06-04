#include <iostream>
#include <fcntl.h>
#include <stdio.h>
using namespace std;
/*
 * 0 = stdin
 * 1 = stdout
 * 2 = stderr
 */
int main()
{
    /*
    cout << "hello \nworld!";
    cerr << "hola"
         << " mundo!" << endl;
    cout << endl;
    */

    int fd = open("empty.cpp",O_RDONLY);
    if (fd==-1) {
        perror("open failed");
    }
    return 0;
}
