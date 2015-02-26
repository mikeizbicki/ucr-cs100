#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd;
    if (-1==(fd=open("test",O_RDWR))) {
        perror ("open failed");
    }

    char buf[1024];
    int size;
    if (-1==(size=read(fd,buf,sizeof(buf)))) {
        perror ("read failed");
    }

    write(1,buf,size);

    close(fd);

    /*
    int size=write(fd,"hello\n",6);
    if (-1==size) {
        perror ("write failed");
    }
    */
    return 0;
}
