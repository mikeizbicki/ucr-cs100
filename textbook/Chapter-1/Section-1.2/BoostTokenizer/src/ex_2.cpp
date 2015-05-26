#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

int main() {
    string str = "Thou&&&&art&as    fat&as&&butter";
    char_separator<char> delim("&");
    //char_separator<char> delim(" &");
    tokenizer< char_separator<char> > mytok(str, delim);

    cout << "Original string: " << str << endl;
    for(auto it = mytok.begin(); it != mytok.end(); ++it)
        cout << "token: " << *it << endl;


    return 0;

}

