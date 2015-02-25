#include <unistd.h>
#include <fcntl.h>
#include <iostream>
using namespace std;

int main()
{
    int fd[2];
    pipe(fd);
    close(2);
    cout << "fd[0]=" << fd[0] << endl
         << "fd[1]=" << fd[1]
         << endl;
    dup(fd[0]);
    dup2(fd[0],2);
    return 0;
}
