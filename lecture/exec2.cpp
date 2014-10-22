#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
using namespace std;

int main(int argc, char**argv)
{
    char *argv2[3];
    argv2[0]="./exec2.cpp";
    argv2[1]=0;
    int r=execvp(argv2[0],argv2);
    if (r==-1) {
        perror("execvp");
        //cout << "error" << endl;
        exit(1);
    }
    return 0;
}
