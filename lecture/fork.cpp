#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    int pid=fork();

    const char* cmd="/bin/ls";

    if (pid ==0 ) {
        if (-1 == execl(cmd
                       ,""
                       ,NULL
                       )){
            perror ("execl failed");
        }
    }

    //wait(0);
    cout << "READ ME!!!!" << endl;

    return 0;
}
