#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ofstream outfile("outfile.txt", fstream::out);
    if(outfile.is_open())
    {
        outfile << "Redirected to file.\n";
        outfile.close();
    }
    else
    {
        cout << "Unable to open outfile." << endl;
    }
    string line;
    ifstream infile("infile.txt");
    if(infile.is_open())
    {
        while(getline(infile, line))
        {
            cout << line << endl;
        }
        infile.close();
    }
    else
    {
        cout << "Unable to open infile" << endl;
    }
    return 0;
}


