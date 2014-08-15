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
    int fd[2];
    if (pipe(fd)==-1) {
        perror ("pipe failed");
        exit(1);
    }
    
    int pid=fork();
    if (pid==0) {
        // write to the pipe
        //write(fd[1],"test",5);
        close(1);
        dup(fd[1]);
        cout << "test" << endl;
    }
    else {
        //wait(0);
        char buf[BUFSIZ];
        read(fd[0],buf,BUFSIZ);
        //cout << "buf=" << buf << endl;
        // read from the pipe
    }
    cout << "what'll happen?!" <<  endl;

    //cerr << "fd[0] = " << fd[0] << endl;
    //cerr << "fd[1] = " << fd[1] << endl;
    return 0;
}
