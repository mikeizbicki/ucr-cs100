#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

typedef tokenizer<char_separator<char> > mytok;

int main() {
   string str = "CS&100&is&really             amazing";
   char_separator<char> delim("&");
   mytok tok(str, delim);
    
   for(auto it = tok.begin(); it != tok.end(); ++it) {
	    cout << "token: " <<  *it << endl;
	}
		cout << endl;
	    return 0;
}
