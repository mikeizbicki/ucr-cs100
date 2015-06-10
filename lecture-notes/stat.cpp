#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main()
{
    struct stat s;
    stat(".", &s);

    cout << "size = " << s.st_size << endl;

    cout << "permissions = "
         << ((S_IFDIR & s.st_mode)?"d":"-")
         << ((S_IRUSR & s.st_mode)?"r":"-")
         << ((S_IWUSR & s.st_mode)?"w":"-")
         << ((S_IXUSR & s.st_mode)?"x":"-")
         << ((S_IRGRP & s.st_mode)?"r":"-")
         << ((S_IWGRP & s.st_mode)?"w":"-")
         << ((S_IXGRP & s.st_mode)?"x":"-")
         << ((S_IROTH & s.st_mode)?"r":"-")
         << ((S_IWOTH & s.st_mode)?"w":"-")
         << ((S_IXOTH & s.st_mode)?"x":"-")
         << endl;

    /*
     * a = 0010
     * b = 1100 = 12
     *
     * a & b = 0000
     *
     */

    return 0;
}
