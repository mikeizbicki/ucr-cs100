#include <list>
#include <iostream>
#include <boost/foreach.hpp>

using namespace std;

int main(){
    list<int> l;
    for(int i = 0; i < 100; i++) l.push_back(i);
    for(list<int>::const_iterator it = l.begin(); it != l.end(); ++it){
        cout << *it << " "; //example of how to iterate through a list
    }
    cout << endl;
            
    return 0;
}
