#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

typedef bool (*comparator)(int,int);

bool greaterThan(int a, int b)
{
    return a>b;
}

int minimum(int a, int b, bool (*c)(int,int))
{
    if (c(a,b)) return a;
    return b;
}

int main()
{
    cout << "minimum(3,4)=" << minimum(3,4,greaterThan) << endl;
    /*
    vector<int> v = {1,2,3,9,5};
    sort(v.begin(),v.end(),greaterThan);

    for (auto i=v.begin(); i!=v.end(); i++) {
        cout << "*i= " << *i << endl;
    }
    */
    return 0;
}
