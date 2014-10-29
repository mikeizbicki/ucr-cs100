#include <iostream>
using namespace std;
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FLAG_a 1
#define FLAG_l 2
#define FLAG_r 3
#define FLAG_R 4

int main(int argc, char**argv)
{
    int flags=0;

    for (int i=1; i<argc; i++) {
        if (argv[i][0] == '-') {
            for (int j=1; argv[i][j] != 0; j++) {
                if (argv[i][j] == 'a')
                    flags |= FLAG_a;
        }
    }

    if ( /*-a occurs */) flags |= FLAG_a;
    if ( /*-l occurs */) flags |= FLAG_l;
    if ( /*-R occurs */) flags |= FLAG_R;

    // main code here

    for curfile in files {
    if (flags & FLAG_a && curfile[0]=='.') {
        // display file
     }
     }

    /*
    struct stat statbuf;
    stat("bin",&statbuf);
    cout << "size: "
         << statbuf.st_size
         << endl;

    if (S_ISDIR(statbuf.st_mode)) {
        cout << "d";
    }
    else cout << "-";

    if (statbuf.st_mode & S_IRUSR) {
        cout << "r";
    } else cout << "-";
    if (statbuf.st_mode & S_IWUSR) {
        cout << "w";
    } else cout << "-";
    if (statbuf.st_mode & S_IXUSR) {
        cout << "x";
    } else cout << "-";
    cout << endl;
    */
    return 0;
}
