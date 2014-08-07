#include <stdlib.h>
#include <iostream>
using namespace std;

int main()
{
    char *str=(char*)malloc(100);

    for (int i=0; i<=100; i++) {
        cout << str[i] << endl;
    }

    free(str);
    return 0;
}

