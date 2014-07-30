#include <iostream>
#include <string>

#include <unistd.h>
#include <fcntl.h>

int main()
{
    std::string str = "hello";
    char *str2 = "goodbye";

    std::cout << str2 << std::endl;

    int fd=open("testfile",O_RDWR);
    write(fd,"goodbye\n",8);

    return 0;
}
