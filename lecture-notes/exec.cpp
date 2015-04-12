#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main(int argc, char **argv)
{
    //for (int i=0; i<argc; i++) {
    //cout << "argv[" << i << "] = " << argv[i] << endl;
    //}

    int i=fork();
    if (i==0) {
        if (-1==execvp("asdasdasdadsls",argv)) {
           perror("execvp");
        }
    }
    else {
        cout << "hello world!!!" << endl;
    }

    return 0;
}
