#include <iostream>
#include <map>
#include <boost/foreach.hpp>
#include <sstream>

using namespace std;

int main(){
    map<string,pair<int, string> > m;
    //We're going to award the 3 most popular in each category
    string contests[3] = {"Best at walking",
                          "Best at talking",
                          "Best at bsing it"}; 
    //So we need to get input that delivers to us these fabulous winners
    //Because I don't want to put too much into the portion that isn't about 
    //  maps just pretend the input comes from a databases containing all
    //  the contestants and parses out the winners full name and contact
    //  information from their IDs which are based in by the judges at the time
    //  of selection. I'm not THAT dedicated to a single example
    string test; //string holding the value of the current line being passed in
    int pos = 1, curcont = -1; //position of the winner and which contest
    while(getline(cin, test)){
        if(pos%3 == 1){
            if(curcont > 2) break;
            cout << "--------------------"<< endl;
            cout << contests[++curcont]<< endl << "--------------------"<< endl;
        }
        int paran = test.find("(");
        pair<int, string> parse;
        if(pos%3 == 0) parse.first = 3;
        else parse.first = pos%3;
        parse.second = test;
        string str = test.substr(0, paran-1);
        m[str]= parse;
        //just to show what exactly is being added to the map
        cout << "Key: " << str << ": "
             << " Place: " << m[str].first << " "
             << "Contact Information: " << m[str].second << endl; 
        pos++;
    }
    //boom, now we have a map of all the contests with their place and contact
    //  information. So now we could just iterate through and based on how
    //  they placed we could call and congratulate them and tell them we're
    //  sending them their prize money through the email address they also
    //  put down when signing up.
}
