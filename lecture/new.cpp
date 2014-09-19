#include <iostream>
using namespace std;

int main()
{
    const char *str = "test";
    cout << str[0] << endl;
    cout << 0[str] << endl;
    cout << *(str+0) << endl;
    cout << *(0+str) << endl;
    return 0;
}
