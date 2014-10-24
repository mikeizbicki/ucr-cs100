#include <iostream>
using namespace std;

#define PRINT(t)  \
    cout << "sizeof("# t "): " \
         << sizeof(t)  \
         << endl;
#define PRINTALL(t) \
         PRINT(t) PRINT(t*) PRINT(t**)
#define PRINT_UN(t) \
         PRINTALL(t) PRINTALL(unsigned t) \
         cout << endl;

struct s1 { char a1; };
struct s2 { char a1; char a2; };
struct s3 { char a1; int a2; };
struct s4 { char a1; int a2; char a3; };
struct s5 { char a1; char a3; int a2; };

int main()
{
    PRINTALL(s1)
    PRINTALL(s2)
    PRINTALL(s3)
    PRINTALL(s4)
    PRINTALL(s5)
    //PRINT_UN(char)
    //PRINT_UN(short)
    //PRINT_UN(int)
    //PRINT_UN(long)
    //PRINT_UN(long long)
    //PRINTALL(float)
    //PRINTALL(double)
    return 0;
}
