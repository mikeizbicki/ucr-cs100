#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <iostream>

using namespace std;

int main()
{
   char *dirName = ".";
   DIR *dirp;
   if (!(dirp  = opendir(dirName)))
    {
       cerr << "Error(" << errno << ") opening " << dirName << endl;
       return errno;
   }
   dirent *direntp;
   while ((direntp = readdir(dirp)))
       cout << direntp->d_name << endl;  // use stat here to find attributes of file
   closedir(dirp);
}

