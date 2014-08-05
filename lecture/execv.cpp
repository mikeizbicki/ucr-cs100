#include <iostream>
#include <unistd.h>
#include <stdlib.h>


using namespace std;

int main(int argc, char** argv)
{
    /*
    cerr << "argc: " << argc << endl;

    cerr << "argv: [";
    for (int i=0; i<argc; i++) {
        cerr << argv[i] << ", ";
    }
    cerr << "]" << endl;
    */

    // c++ way
    //char** argv2;
    //argv2 = new char*[7];
    //delete[] argv2;

    // c way
    char **argv2;
    argv2 = (char**)
        malloc(7*sizeof(void*));

    argv2[0] = (char*)"/bin/ls";
    argv2[1] = (char*)"-l";
    argv2[2] = (char*)"-a";
    argv2[3] = 0;
    argv2[4] = 0;
    argv2[5] = 0;
    argv2[6] = 0;

    execv("/bin/ls",(char *const*)argv2);

    free (argv2);

    return 0;
}
