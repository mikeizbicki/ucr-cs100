#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

int main()
{
    cout << (2 >> 1) << endl;
    return 0;

    struct stat s;
    stat("stat2.cpp",&s);
    cout << oct;
    cout << s.st_mode << endl;

    cout << ((s.st_mode&S_IRUSR)?"r":"-");
    cout << ((s.st_mode&S_IWUSR)?"w":"-");
    cout << ((s.st_mode&S_IXUSR)?"x":"-");

    //if (s.st_mode & S_IRUSR) cout << "r";
    //else cout << "-";

    cout << endl;
}
