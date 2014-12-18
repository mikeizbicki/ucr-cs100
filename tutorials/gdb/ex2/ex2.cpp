#include <iostream>

using namespace std;

void foo(int x)
{
    x = x + 1;
    cout << x << endl;
}

void bar(int x)
{
    x = x + 1;
    cout << x << endl;
    foo(x);
}

int main()
{
    int x = 0;
    
    cout << x << endl;
    bar(x);
    
    // the final output should be 2
    
    return 0;
}
