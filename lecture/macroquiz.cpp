#include <iostream>
using namespace std;

#define PRINT(x)  cout << #x << ": " << sizeof(x) << endl;
#define PRINTALL(x) \
    PRINT(x);       \
    PRINT(x*);      \
    cout << endl;

//#define PRINTALL(X) PRINT(x*) PRINT(x**) ..

#define PRINTALLU(x) PRINTALL(x); PRINTALL(unsigned x);

struct s1 { char a; };
struct s2 { char a; char b; };
struct s3 { char a; int b; };
struct s4 { char a; int b; char c; };
struct s5 { char a; char b; int c; };

int main()
{
    PRINTALL(s1);
    PRINTALL(s2);
    PRINTALL(s3);
    PRINTALL(s4);
    PRINTALL(s5);
    
    //PRINTALLU(char);
    //PRINTALLU(short);
    //PRINTALLU(int);
    //PRINTALLU(long);
    //PRINTALLU(long long);
    //
    //PRINTALL(float);
    //PRINTALL(double);

    //PRINT(char);
    //PRINT(char*);
    //PRINT(char**);
    cout << "char: " << sizeof(char) << endl;
    return 0;
}
