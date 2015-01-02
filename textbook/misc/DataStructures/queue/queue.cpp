#include <queue>
#include <iostream>

using namespace std;

int main(){
    queue<int> q;
    for(unsigned i = 0; i < 10; ++i)
        q.push(i); //add commands you wish to execute
    while(!q.empty()){
        cout << q.front() << " ";//first in first out. 
        q.pop(); //remove last executed command
    }
    cout << endl;
    return 0;
}
