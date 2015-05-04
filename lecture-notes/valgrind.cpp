#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int buf[10];
    memset(buf,0,sizeof(buf));

    for (int i=0; i<=10; i++) {
        cout << "buf[i]=" << buf[i] << endl;
    }
    /*
    // sizeof(int*) = 8
    // sizeof(int)  = 4
    int *i=(int*)malloc(sizeof(int));
    cout << "hello world" << endl;
    //delete i;
    //free(i);
    */
    return 0;
}
