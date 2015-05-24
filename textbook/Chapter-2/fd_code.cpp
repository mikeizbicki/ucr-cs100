#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main()
{
    int fdnew;
    int fdold;
    if(-1 == (fdnew = open("filenew", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)))
    {
        perror("There was an error with open(). ");
        exit(1);
    }	
    if(-1 == (fdold = open("fileold", O_RDONLY))) 
    {
        perror("There was an error with open(). ");
        exit(1);
    }
    int size;
    char c[BUFSIZ];
    if(-1 == (size = read(fdold, c, sizeof(c)))) 
    {
        perror("There was an error with read(). ");
        exit(1);
    }
    while(size > 0)
    {
        if(-1 == write(fdnew, c, size))
        {
            perror("There was an error with write(). ");
            exit(1);
        }
        if(-1 == (size = read(fdold, c, sizeof(c))))
        {
            perror("There was an error with read(). ");
            exit(1);
        }
    }
    if(-1 == close(fdnew))
    {
        perror("There was an error with close(). ");
        exit(1);
    }
    if(-1 == close(fdold))
    {
        perror("There was an error with close(). ");
        exit(1);
    }
    return 0;
}
