#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char ** argv)
{
    int fdo=open("testfile",O_WRONLY);
    int fdi=open("in",O_RDONLY);
    close(0);
    close(1);
    dup(fdi);
    dup(fdo);
    argv[0]="ls";
    execvp(argv[0],argv);
    return 0;
}
