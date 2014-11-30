#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

bool lessthan(int i, int j)
{
    return i<j;
}

class ffffff
{
private:
    string t;

public:
    bool operator ()(int i, int j){
        return (i<j);
    }

    setstr(string t1) { t=t1 }
};

int main()
{
    vector<int> v;
    for (int i=0; i<10; i++)
        v.push_back(rand()%100);

    for (int i=0; i<10; i++)
        cout << v[i] << " ";
    cout << endl;

    ffffff f;
    sort(v.begin(),v.end(),f);

    for (int i=0; i<10; i++)
        cout << v[i] << " ";
    cout << endl;

    return 0;
}
