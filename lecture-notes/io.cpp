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

    int pid=fork();
    if (pid==0) {
        close(1);
        dup(fd[1]);
        if (-1==write(fd[1],"hello world", 11)) {
            perror ("write");
        }
        cout << "goodbye world" << endl;
    }
    else if (pid>0) {
        close(0);
        dup(fd[0]);
        string buf;
        cin >> buf;
        //char buf[BUFSIZ];
        //read(fd[0],buf,BUFSIZ);
        cerr << "buf=" << buf << endl;
    }

    /*
    close(0);
    open("outfile",O_WRONLY|O_CREAT|O_TRUNC);
    execvp("ls",argv);
    */
    //cout << "hello world" << endl;
    return 0;
}
