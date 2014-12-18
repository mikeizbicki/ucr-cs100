#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    //int fd=open("out",O_RDONLY);
    //if (fd==-1) {
    perror ("open");
        //exit(1);
        //}
        //while(1);
    return 0;
}
