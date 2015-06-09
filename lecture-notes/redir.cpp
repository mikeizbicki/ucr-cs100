#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
using namespace std;

int main()
{
    if (-1==close(1)) {
        perror("close");
    }
    int fd=open("outfile",O_WRONLY|O_CREAT|O_TRUNC);
    if (-1== fd) {
        perror("open");
    }
    //write(1,"hello world",11);
    cout << "fd=" << fd << endl;
    return 0;
}
