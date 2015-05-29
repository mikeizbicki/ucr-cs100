#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

typedef tokenizer<char_separator<char> > mytok;

int main() {
    string str = "ls dir || cat file | tr a-z A-Z";
    char_separator<char> delim(" ||");
    tokenizer< char_separator<char> > mytok(str, delim);

    for(auto it = mytok.begin(); it != mytok.end(); ++it)
        cout << *it << " ";

    cout << endl;

    return 0;

}
