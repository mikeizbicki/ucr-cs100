#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{
    cout << O_RDONLY << endl;
    cout << O_WRONLY << endl;
    cout << O_RDWR << endl;
    int fd=open("test",O_RDWR | O_CREAT);
    if (fd==-1) {
        perror("open");
        return 1;
    }
    char buf[1024];
    memset(buf,0,sizeof(buf));
    //char *buf = new char[1024];
    buf[0]='h';
    buf[1]='i';
    buf[2]='!';
    buf[3]='\0';
    write(fd,buf,sizeof(buf));
    //cout << "sizeof(buf): " << sizeof(buf) << endl;
    close(fd);
}
