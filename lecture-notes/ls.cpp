#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//using namespace std;

int main()
{
    struct stat s;
    stat("test",&s);
    std::cout << "num bytes: " << s.st_size << std::endl;

    return 0;
}
