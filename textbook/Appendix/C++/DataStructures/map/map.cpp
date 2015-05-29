#include <iostream>
#include <map>
#include <boost/foreach.hpp>

using namespace std;

int main(){
    //basic map involving a pair<string,string> 
    map<string, string> m;

    //Data values resembling something you may encounter if you ran ls -la on
    //a directory just containing this file and the executable. 
    m["map.cpp"]="perm sz user group date map.cpp";
    m["a.out"]="perm sz user group date a.out";
    m["."] = "perm sz user group date .";
    m[".."] = "perm sz user group date ..";

    /*Originally the map was created in seemingly random order, but stl maps
          are implemented as binary trees so when iterating through the map
          the iterator will traverse the tree in order.
    */
    cout << "----------------------------------------" << endl;
    pair<string, string> p;
    BOOST_FOREACH(p, m){ 
       //Just think of FOREACH as a for loop iterating through the values
       // in map m because that is exactly what it is doing.
       cout << "data: " << (p).second << endl;
       // ^ outputting the data value, not the key. If you wanted to reference
       //the key you would simply do p.second.
    }
    cout << "----------------------------------------" << endl;
    return 0;
}
/*Assuming instead you were do use say, a vector<string>, to contain
    these values you would then have to figure out how to sort the data
    yourself, or look at the example below included to show the difference
    in ease.  

-----------------------------------------------------------------------
namespace {
    struct ignoreCaseSort : public binary_function<char, char, bool>{
        bool operator() (char x, char y) const{
            return toupper(static_cast<unsigned char>(x) ) < 
                   toupper(static_cast<unsigned char>(y) );
        }
    };
    bool string_ignore_case_sort(const string &a, const string &b){
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                    ignoreCaseSort() );
    }
}
void sorted_vector_output(vector<string> v){
    sort(v.begin(), v.end(), string_ignore_case_sort);
    for(unsigned  i = 0; i < v.size(); i++){
        cout << v.at(i) << endl;
    }
}

*/
