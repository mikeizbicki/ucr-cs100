#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char **argv)
{
    //for (int i=0; i<argc; i++) {
    //cout << "argv[" << i << "] = " << argv[i] << endl;
    //}

    int i=fork();
    if (i==0) {
        if (-1==execvp("ls",argv)) {
           perror("execvp");
        }
    }
    else {
        int status=0;
        wait(&status);
        cout << "status=" << status << endl;
        while (1);
    }

    return 0;
}
