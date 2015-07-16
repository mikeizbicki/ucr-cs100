#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int main()
{
   
    int outfd = -1;
    
    outfd = open("filename.txt", O_WRONLY | O_CREAT | O_TRUNC);
    
    if( outfd < 0 )
    {
        perror("open " );
        exit(1);
    }
    
    if(dup2(outfd,1) < 0)
    {
        perror("dup2 " );
        exit(1);
    }
    
    cout << "This statement will print within filename.txt." << endl;

    return 0;
}
