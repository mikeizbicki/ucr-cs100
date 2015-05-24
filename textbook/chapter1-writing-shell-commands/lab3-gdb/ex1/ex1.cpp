#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>

using namespace std;

char* my_strcpy(char *dst, const char* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return NULL;
    }

    int target_size;

    for(target_size = 0; src[target_size] != '\0'; target_size++)
    {}

    char* dstArr = new char[target_size];

    size_t i;

    for(i = 0; src[i] != '\0'; ++i)
    {
        dstArr[i] = src[i];
    }

    dst = dstArr;

    delete dstArr;

    return dst;
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        cout<<"not enough arguments."<<endl;
        return -1;
    }

    if (argc > 3)
    {
        cout<<"too many arguments."<<endl;
        return -1;
    }

    cout<<"First: "<<argv[1]<<endl;
    cout<<"Second: "<<argv[2]<<endl;

    argv[1] = my_strcpy(argv[1], argv[2]);

    cout<<endl<<"COPY DONE"<<endl<<endl;
    cout<<"First: "<<argv[1]<<endl;
    cout<<"Second: "<<argv[2]<<endl;

    return 0;
}
