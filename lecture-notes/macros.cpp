#include <iostream>
using namespace std;

#define PRINT(x) cout << "sizeof(" \
                      << # x \
                      << "):" << sizeof(x) \
                      << endl;
#define PtrPRINT(x) PRINT(x); PRINT(x*); PRINT(x**); \
                    cout << endl;

#define UPRINT(x) PtrPRINT(x); PtrPRINT(unsigned x);

struct s1 { char a; };
struct s2 { char a; char b; };
struct s3 { char a; int b; };
struct s4 { char a; int b; char c; };
struct s5 { char a; char c; int b; };

int main()
{
    PtrPRINT(s1);
    PtrPRINT(s2);
    PtrPRINT(s3);
    PtrPRINT(s4);
    PtrPRINT(s5);

    //UPRINT(char);
    //UPRINT(short);
    //UPRINT(int);
    //UPRINT(long);
    //UPRINT(long long);

    //PtrPRINT(float);
    //PtrPRINT(double);
}
