#include <unistd.h>
#include <fcntl.h>

int main()
{
    char *str2 = "goodbye";

    int fd=open("testfile",O_RDWR);
    write(fd,"goodbye\n",8);

    return 0;
}
