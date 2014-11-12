#include <iostream>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    //close(1);
    int fd=open("testfile",O_RDWR|O_CREAT);
    int oldstdout=dup(1);
    close(1);
    dup(fd);
    cout << "fd=" << fd << endl;
    close(1);
    dup(oldstdout);
    cout << "to the screen" << endl;
    return 0;
}
