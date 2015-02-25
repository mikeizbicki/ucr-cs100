#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>

using namespace std;

int main()
{
	const char *dirName = ".";
	DIR * dirp = opendir(dirName);
	dirent *direntp;
	while((direntp = readdir(dirp)))
		cout << direntp->d_name << endl;
	closedir(dirp);
}
