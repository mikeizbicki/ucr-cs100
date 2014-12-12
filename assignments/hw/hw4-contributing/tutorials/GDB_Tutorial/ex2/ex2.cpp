#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>
#include <errno.h>
#include <grp.h>
#include <time.h>

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

int info(const char * dirName)
{
    struct stat sb;

    if(stat(dirName, &sb)==-1)
    {
        perror("stat");
    }

    string firstpart = "|??|";
  
    //Read permission - owner
    if((sb.st_mode & S_IRUSR))
    {
        //BREAK HERE TO CHECK
    }

    //Write permission - owner
    if((sb.st_mode & S_IWUSR))
    {
        //BREAK HERE TO CHECK
    }

    //Execute/search permission - owner
    if((sb.st_mode & S_IXUSR))
    {
        //BREAK HERE TO CHECK
    }               


    cout<<left<<setw(10)<<setfill('-');
    cout<<firstpart;
    cout<<setw(8)<<right;
    cout<<setw(10);
    cout<<dirName<<endl;

    return 0;
}


int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        cerr<<"No argument."<<endl;
    }

    vector <char *> dirlist;

    for (int i = 1; i < argc; i++)
    {
        char* command = argv[i];
        struct stat sb; 

        if( stat (argv[i], &sb) != 0 && command[0] != '-')
        {
            cerr<<"Input does not exist. Filename entered: "<<argv[i] <<endl;
            return -1;
        }

        else if (command[0] == '-')
        {
            cerr<<"This program does not take flags."<<endl;
            return -1;
        }
        else
        {
            dirlist.push_back(argv[i]);     //keeps track of all directories passed
        }
    }

    for(unsigned int i = 0; i < dirlist.size(); i++)
    {
        info(dirlist.at(i));
    }

    if (dirlist.empty())
    {
        cout<<"Please enter file(s)."<<endl;
        return -1;
    }

    return 0;
}

