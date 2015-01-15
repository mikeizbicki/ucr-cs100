#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main(int argc, char **argv)
{
    /*
    for (int i=0; i<argc; i++) {
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }
*/
    //char *cmd="lsdoesnotexist";
    char *cmd="ls";
    int pid=fork();
    if (pid== -1) {
        perror("fork fail");
    }
    else if (pid == 0) {
        if (execvp(cmd,argv) != 0) {
            //cerr << "error in execvp" << endl;
            perror("error in execvp");
        }
    }
    else {
        cerr << "will this print?!" << endl;
    }

    return 0;
}
