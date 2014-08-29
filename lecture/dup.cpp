#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    close(1);
    int fd=open("test",O_RDWR|O_CREAT);
    cout << "is this a file????" << endl;
    return 0;

    if (fd==-1) {
        perror("open failed");
        exit(1);
    }
    
    const char* str="hello world!\n";
    int terminal=dup(1);
    int fd2=dup(fd);
    cerr << "fd:  " << fd << endl;
    cerr << "fd2: " << fd2 << endl;
    if (write(fd2,str,strlen(str))==-1) {
        perror("write failed");
    }
    cout << "does this work?" << endl;

    close(1);
    dup(terminal);
    cout << "is this the screen?" << endl;

    // 
    //write(fd2,str,strlen(str));
    //
    return 0;
}
