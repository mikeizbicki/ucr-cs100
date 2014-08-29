#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include <iostream>
using namespace std;

//#define O_RDWR    1024
//#define O_CREAT   2048

int main()
{
    //int fd=open("doesnotexist",O_RDWR | O_CREAT);
    //if (fd==-1) {
        //perror ("open failed");
    //}
    //cerr << "fd:  " << fd << endl;

    int res=write(2,"test\n",5);
    if (res==-1) {
        perror("write failed");
    }

    return 0;
}
