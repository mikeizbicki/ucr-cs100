//ex3

// The main function for the Complex Classes

#include "complex.h"
#include <iostream>

using namespace std;

int main (void)
{
 Complex c1;
 Complex c2(4);
 Complex c3(7.823);
 Complex c4(43, 3), c5(-54, -84);
 Complex c6 = c4;
 Complex c7(c4);

 cout << "c1 is " << c1 << endl;
 cout << "c2 is " << c2 << endl;
 cout << "c3 is " << c3 << endl;
 cout << "c4 is " << c4 << endl;
 cout << "c5 is " << c5 << endl;
 cout << "c6 is " << c6 << endl;
 cout << "c7 is " << c7 << endl;

 c1.setReal(4);

 cout << endl;
 cout << "c1 is " << c1 << endl;
 cout << "c2 is " << c2 << endl;
 if (c1 == c2)
    cout << "C1 and C2 are the same." << endl;
 else
    cout << "C1 and C2 not are the same." << endl;
    
 cout << endl;
 c6 = Complex (12, -18);
 cout << "c6 is " << c6 << endl;
 cout << "c7 is " << c7 << endl;
 if (c6 < c7)
    cout << "c6 is less than c7" << endl;
 else
    cout << "c6 is not less than c7" << endl;
 if (c7 < c6)
    cout << "c7 is less than c6" << endl;
 else
    cout << "c7 is not less than c6" << endl;
    
 cout << endl;
 c6 = Complex (12, 18);
 c7 = Complex (12, -15);
 cout << "c6 is " << c6 << endl;
 cout << "c7 is " << c7 << endl;
 if (c6 < c7)
    cout << "c6 is less than c7" << endl;
 else
    cout << "c6 is not less than c7" << endl;
 if (c7 < c6)
    cout << "c7 is less than c6" << endl;
 else
    cout << "c7 is not less than c6" << endl;

 cout << endl;
 cout << "c3 = c4 + c5" << endl;
 c3 = c4 + c5;
 cout << "c3 is " << c3 << endl;
 cout << "c4 is " << c4 << endl;
 cout << "c5 is " << c5 << endl;
    
 cout << endl;
 cout << "c3 = 4 + c5" << endl;
 cout << "c4 = c5 + 5" << endl;
 c3 = 4 + c5;
 c4 = c5 + 5;
 cout << "c3 is " << c3 << endl;
 cout << "c4 is " << c4 << endl;
 cout << "c5 is " << c5 << endl;
}
