#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include <iostream>

using namespace std;

/*
 * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
 * that there is no error checking on these functions.  You MUST add error 
 * checking yourself.
 */

int main()
{
    char *dirName = ".";
    DIR *dirp = opendir(dirName);
    dirent *direntp;
    while ((direntp = readdir(dirp)))
        cout << direntp->d_name << endl;  // use stat here to find attributes of file
    closedir(dirp);
}

