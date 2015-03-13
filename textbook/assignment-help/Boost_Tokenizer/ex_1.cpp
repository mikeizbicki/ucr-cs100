#include <boost/tokenizer.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace boost;

int main()
{
    string str = "Don't Panic, too much.";
   tokenizer<> tok{str};
    for (auto it = tok.begin(); it != tok.end(); ++it)
           std::cout << *it << endl;;

      return 0;


}
