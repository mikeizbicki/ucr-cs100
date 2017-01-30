#include <iostream>
#include <vector>

using namespace std;


int count_vector(vector<int> foo)
{
	int total = 0;
	for(int x = 0; x < x.size(); x++)
	{
		total += foo.at(x);
	}
	return
}

bool isPalindrome(string s)
{
    if(s.size() > 1)
    {
        if(s.at(0) != s.at(s.size() - 1))
        {
            cout << "wrongs: " << endl;
            return false;
        }
        else
        {
            isPalindrome(s.substr(1, s.size()-2));
        }
    }
    cout << "what are u doing: " << endl;
    return true;
    if(s.size() <= 1)
    {
        return true;
    }
   
}

int square_nums(int x)
{
	return (x*x);
}

int main()
{
    
    cout << isPalindrome("racecasdfsaaar");
    vector<int> vect_of_ints;
	vect_of_ints.push_back(4);
	vect_of_ints.push_back(8);
	vect_of_ints.push_back(12);
	vect_of_ints.push_back(5);
	vect_of_ints.push_back(13);
	int result = count_vector(vect_of_ints);
	cout << "result of count: " << result << endl;
	cout << square_nums(8) << endl;
  
}