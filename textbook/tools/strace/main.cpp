#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    string input = "data.dat";
    string output = "output.dat";
    
    ifstream fin;
    fin.open(input.c_str());
    
    if (!fin)
    {
        cout << "Could not open input file." << endl;
        return 1;
    }
    
    ofstream fout;
    fout.open(output.c_str());
    
    if(!fout)
    {
        cout << "Could not open output file." << endl;
        return 1;
    }
    
    fin.close();
    fout.close();
    
    cout << endl;
    return 0;
}
