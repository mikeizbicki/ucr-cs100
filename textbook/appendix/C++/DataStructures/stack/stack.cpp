#include <stack>
#include <iostream>
#include <string.h>

using namespace std;

int main(){
    stack<int> rev;
    int arr[10];
    unsigned i;
    for(i = 0; i < 10; ++i) rev.push(i); //0-9
    i= 0; //reset i to 0 after using it to fill the stack
    while(!rev.empty()){
         arr[i] = rev.top();
         rev.pop();
         ++i;
    }
    for(i = 0; i < 10; ++i) cout << arr[i] << " "; //now reversed 0-9
    cout << endl;
    return 0;    
}
