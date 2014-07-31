#include <iostream>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main()
{
    int pid=fork();

    if (pid ) {
        if (-1 == execl("/bin/ls"
                       ,"-l"
                       ,NULL
                       )){
            perror ("execl failed");
        }
    }

    cout << "READ ME!!!!" << endl;

    return 0;
}
