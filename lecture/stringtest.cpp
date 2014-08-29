#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

int fib(int n)
{
    if (n==0) return 1;
    if (n==1) return 1;
    return fib(n-1)+fib(n-2);
}

int main()
{
    int x;
    const int y=9;
    char *str = "hello";
    string str2 = "hello world";

    for (int i=0; i<10; i++)
        cout << fib(i) << endl;

    return 0;

    str[0] = 'H';
    
    //infiniteRecursion();

    //cout << str << endl;
    //string str;
    //cin >> str;

    char** cp;
    cp = (char**)malloc(100);
    cp[0] = (char*)malloc(str2.length()+1);

    strcpy(cp[0],str2.c_str());

    //cp[0] =(char*) str.c_str();

}
