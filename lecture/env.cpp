#include <iostream>
#include <unistd.h>
#include<stdlib.h>
#include <stdio.h>
using namespace std;

int main(int argc, char **argv)
{
    //char *var="PS1";
    //const char *var="var";
    if (chdir("/")==-1) {
        perror("chdir");
    }
    char buf[BUFSIZ];
    getcwd(buf,sizeof(buf));
    const char *var="PWD";
    cerr << getenv(var) << endl;
    cerr << buf << endl;
    return 0;
}
