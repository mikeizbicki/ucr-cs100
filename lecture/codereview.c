#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
using namespace std;

int copyFile
    (const char* fin, const char* fout)
{
  // do nothing if the files are the same
    /*if (strcmp(fin,fout)==0)*/
    if (string(fin) == fout)
    return;

  // initialize file reading
  int fdi = open (fin, O_RDWR);
  if (fdi==-1) return -1;
  char buf[BUFSIZ];

  // copy the file
  int fdo = open (fout, O_APPEND);
  int numread;
  while (numread=read(fdi,buf,sizeof(buf))) {
    write(fdo,buf,numread);
  }
  close(fdo);
  close(fdi);
}
