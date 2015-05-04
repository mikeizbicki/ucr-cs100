#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main(int argc, char **argv)
{
    int fd[2];
    if (-1==pipe(fd)) {
        perror(__FILE__ ": " "pipe");
    }
    cerr << "fd[0] = " << fd[0] << endl;
    cerr << "fd[1] = " << fd[1] << endl;

    if (-1==write(fd[1],"hello world", 11)) {
        perror ("write");
    }

    char buf[BUFSIZ];
    read(fd[0],buf,11);
    cerr << "buf=" << buf << endl;

    /*
    close(0);
    open("outfile",O_WRONLY|O_CREAT|O_TRUNC);
    execvp("ls",argv);
    */
    //cout << "hello world" << endl;
    return 0;
}
