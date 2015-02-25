#include <iostream>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;
    
int main() {
   string str = "I'm getting pretty good at this.";
   vector<string> v;
   tokenizer<> tok(str);
    
   for(auto it = tok.begin(); it != tok.end(); ++it) {
	    v.push_back(*it);
	    cout << *it << ' ';
	}
		cout << endl;
	    return 0;
}
