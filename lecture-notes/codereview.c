#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int copyFile
    ( const char *fin
    , const char *fout
    )
{
    // do nothing if files are the same
    if (strcmp(fin,fout)==0)
        return;

    // initialize file reading
    int fdi=open(fin, O_RDWR);
    char buf[BUFSIZ];

    // copy the file
    int fdo=open(fout, O_WRONLY|O_CREAT);
    int r;
    while (r=read(fdi,buf,sizeof(buf))) {
        write(fdo,buf,r);
    }
    close(fdo);

    return 0;
}
