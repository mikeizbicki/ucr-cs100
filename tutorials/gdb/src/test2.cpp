#include <iostream>

using namespace std;

void foo()
{
        cout << "test3" << endl;
}

void bar()
{
        cout << "test2" << endl;
        foo();
}

int main()
{
        cout << "test1" << endl;
        bar();
        return 0;
}
