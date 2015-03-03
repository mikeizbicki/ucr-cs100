#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int *buf1=new int[1024]();
    int *buf2=(int*)malloc(1024);
        //char buf[1024];

    cout << "Hodor hodor hodor... HODOR!!!" << endl;
    delete [] buf1;
    free(buf2);
    return 0;
}
