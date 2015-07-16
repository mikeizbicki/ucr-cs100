#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define msg "Standard out is now a file"

int main()
{
    int outfd = -1;
    
    outfd = open("filename.txt", O_WRONLY | O_CREAT | O_TRUNC);
    
    if(outfd < 0)
    {
        perror("open " );
        exit(1);
    }
    
    if(close(1) < 0)
    {
        perror("close");
        close(outfd);
        exit(1);
    }
    
    if(dup(outfd) != 1)
    {
        perror("dup");
        close(outfd);
        exit(1);
    }
    
    close(outfd);
    puts(msg);
    
    return 0;
}
