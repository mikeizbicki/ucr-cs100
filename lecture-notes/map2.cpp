#include <map>
#include <iostream>
#include <vector>
using namespace std;

typedef void (*handler)();

void f1() { cout << "f1" << endl; }
void f2() { cout << "f2" << endl; }

int main()
{
    map<string,handler> m;

    //vector<handler> v = { f1,f2 };
    //
    //int i;
    //while (cin >> i) {
    //(*v[i])();
    //}
        //for (auto i=v.begin(); i!=v.end(); i++) {
        //(*i)();
        //}

    return 0;
}
