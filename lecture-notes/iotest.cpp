#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

int main()
{
    int ret;
    int pipefd[2];
    if (-1==(ret=pipe(pipefd))) {
        perror("pipe failed");
    }
    cout << "pipefd[0]=" << pipefd[0] << endl;
    cout << "pipefd[1]=" << pipefd[1] << endl;

    if (-1==write(pipefd[1],"hello world\n",12)) {
        perror("write");
    }
    char buf[1024];
    if (-1==read(pipefd[0],buf,sizeof(buf))) {
        perror("read");
    }
    cout << "buf=" << buf << endl;

    /*
    close(2);
    int fd=open("stderr",O_WRONLY|O_CREAT);
    if (fd==-1) {
        perror("open failed");
    }
    cout << "fd=" << fd << endl;

    write(1,"stdout\n",7);

    if (-1==(ret=write(2,"stderr\n",7))) {
        write(1,"failed\n",7);
        //perror("write-stderr");
    }
    */
    //cout << "stdout" << endl;
    //cerr << "stderr" << endl;
    return 0;
}
