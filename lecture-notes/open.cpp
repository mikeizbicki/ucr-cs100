#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

using namespace std

int main()
{
    int fd=open("test",O_WRONLY|O_CREAT);
    if (fd==-1) {
        perror("open failed");
    }

    write(fd,"hodor hodor hodor HOOODDDDOOOORRRR", 7);


    return 0;
}
