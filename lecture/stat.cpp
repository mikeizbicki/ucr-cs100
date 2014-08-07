#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

int main()
{
    struct stat s;
    stat("a.out",&s);

    cout << "s.st_size = " << s.st_size << endl;
    cout << "s.st_mode = " << s.st_mode << endl;

    cout << "user permissions: ";
    if (s.st_mode & S_IRUSR) {
        cout << 'r';
    }
    else {
        cout << '-';
    }
    if (s.st_mode & S_IWUSR) {
        cout << 'w';
    }
    else {
        cout << '-';
    }

    if (s.st_mode & S_IXUSR) {
        cout << 'x';
    }
    else {
        cout << '-';
    }
    cout << endl;
    return 0;
}
