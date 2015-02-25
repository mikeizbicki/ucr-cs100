#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

typedef tokenizer<char_separator<char> > mytok;

int main() {
    string str = "12*34 I, declare a&&thumb    !war";
    char_separator<char> delim;
    tokenizer< char_separator<char> > mytok(str, delim);

    //This also behaves the same
    //tokenizer< char_separator<char> > mytok(str);

    for(auto it = mytok.begin(); it != mytok.end(); ++it)
        cout << *it << " ";

    cout << endl;

    return 0;

}


