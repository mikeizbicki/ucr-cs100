#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

typedef tokenizer<char_separator<char> > mytok;

int main() {
    string str = "I;m test^ing this || out;";
    char_separator<char> delim("^| ", ";");
    //char_separator<char> delim("^| ", ";", keep_empty_tokens);
    cout << "Original string: " << str << endl;

    tokenizer< char_separator<char> > mytok(str, delim);

    for(auto it = mytok.begin(); it != mytok.end(); ++it)
        cout << "(" << *it << ")" << " ";

    return 0;

}
