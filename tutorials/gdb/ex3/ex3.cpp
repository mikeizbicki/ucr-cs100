#include <iostream>

using namespace std;

int main()
{
        int *pointer = NULL;
        int number = 0;

        *pointer = number;

        // proper output should be 0
        cout << *pointer << endl;

        return 0;
}
