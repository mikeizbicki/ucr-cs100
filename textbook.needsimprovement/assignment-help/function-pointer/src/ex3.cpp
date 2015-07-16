#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <ctype.h>

using namespace std;
bool ASCII(string s1, string s2) { return s1 < s2; }
bool alphabet(string s1, string s2) 
{
    char str1[10], str2[10];
    strcpy(str1, s1.c_str());
    strcpy(str2, s2.c_str());
    for(int i = 0; str1[i] != '\0'; i++){
        str1[i] = tolower(str1[i]);
    }
    for(int i = 0; str2[i] != '\0'; i++){
        str2[i] = tolower(str2[i]);
    }
    return strcmp(str1, str2) < 0;
}

int main()
{
    string data[6] = {"Sad", "haha", "adore", "dog", "few", "Zoo"};
    vector<string> myvector;
    for (int i = 0; i < 6; i++)
    {
        myvector.push_back(data[i]);
    }
    sort(myvector.begin(), myvector.end());
    for (int i = 0; i < myvector.size(); ++i)
        cout << myvector.at(i) << " " << endl;
    
    bool (*compare)(string, string) = NULL;
    
    cout << endl;
    compare = ASCII;
    sort(myvector.begin(), myvector.end(), compare);
    for (int i = 0; i < myvector.size(); ++i)
        cout << myvector.at(i) << " " << endl;
    
    cout << endl;
    compare = alphabet;
    sort(myvector.begin(), myvector.end(), compare);
    for (int i = 0; i < myvector.size(); ++i)
        cout << myvector.at(i) << " " << endl;
    
    
}