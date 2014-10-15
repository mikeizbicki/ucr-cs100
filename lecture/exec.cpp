#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int pid=fork();
    if (pid==0) {
        cout << "i'm a child"
             << endl;
        char *argv[3];
        argv[0]=new char[3];
        strcpy(argv[0],"ls");
        argv[1]="-a";
        argv[2]="-l";

        cout <<" before" << endl;
        execvp
            ("ls"
            ,argv
            );
        cout << "after" << endl;
    }
    else {
        wait(NULL);
        cout << "I'm a parent."
             << endl;
    }
    return 0;

}
