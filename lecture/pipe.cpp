#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
using namespace std;
int main()
{
    char buf[BUFSIZ];
    memset(buf,0,sizeof(buf));
    int fd[3];
    int *qq = new int[2];
    pipe(fd);
    cerr << "fd[0]=" << fd[0] << endl;
    cerr << "fd[1]=" << fd[1] << endl;
    write(fd[1],"hello world",12);
    read(fd[0],buf,sizeof(buf));
    write(1,buf,sizeof(buf));
    while(1);
    return 0;
}
