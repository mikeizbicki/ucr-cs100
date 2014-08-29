#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// 14) return int; set errno on failure
// 15) should be const char *
void copyFile (char *fin, char *fout)
{
    // do nothing if the files are the same
    // 1) use strcmp
    if (fin==fout) {
        return;
    }

    // initialize file reading
    // 2) use perror everywhere
    // 3) O_RDONLY
    // 6) change sb.st_size to BUFSIZ
    // 7) delete buf
    // 8) put buf on stack
    // 12) close file
    // 16) delete fstat and stat
    int fdi = open (fin, O_RDWR);
    struct stat sb;
    fstat(fdi, &sb);
    char *buf = new char [sb.st_size];

    // copy the file
    // 4) replace sizeof(buff)
    // 5) open/close outside of loop
    // 9) should have O_WRONLY
    // 10) add O_CREAT
    // 11) error check if file exists
    // 13) write takes the number of bytes read
    while (read(fdi,buf,sizeof(buf))) {
        int fdo = open (fout, O_APPEND);
        write(fdo,buf,sizeof(buf));
        close(fout);
    }
}
