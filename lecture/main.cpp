#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include <iostream>

int errno2;

int main()
{
    char *str2 = "goodbye";

    int fd;
    if ((fd=open("testfile",O_RDWR))==-1)    {
        perror("there was an error openning the file");
        exit(1);
        // std::cout << "there was an error openning the file; errno=" << errno << std::endl;
    }
    if (write(fd,"goodbye\n",8)==-1) {
        perror ("write failed");
        exit(1);
    }

    return 0;
}
