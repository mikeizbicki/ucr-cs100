#include <iostream>
#include <vector>

using namespace std;

vector<string> tok_string(const string& input)
{
  vector<string> v;
  string token;
  istringstream ss(input.c_str());

  //String whitespaces from input
  while(ss>>token)
    v.push_back(token);

  return v;
}
