/**
 * CS 100: lab 1: buggy program 4
 */

#include <iostream>
using namespace std;

class CSquare
{
public:
    double Side;

    CSquare() : Side(0.00) {}
    CSquare(double side) : Side(side) { }
    ~CSquare() { }

    double getSide() const { return Side; }
    void setSide(const double s)
    {
	if( s <= 0 )
		Side = 0.00;
	else
		Side = (int)s;
    }

    double Perimeter() { return Side * Side; }
    double Area() { return Side * 4; }
};

int main()
{
    CSquare *sqr[4];

    sqr[0] = new CSquare;
    sqr[0].setSide(24.55);
    sqr[1] = new CSquare;
    sqr[1].setSide(15.08);
    sqr[2] = new CSquare;
    sqr[2].setSide(100);
    
    cout << "Squares Characteristics" << endl;
    cout << "Square 1" << endl;
    cout << "Side:      " << sqr[1]->getSide() << endl;
    cout << "Perimeter: " << sqr[1]->Perimeter() << endl;
    cout << "Area:      " << sqr[1]->Area() << endl;

    cout << "Square 2" << endl;
    cout << "Side:      " << sqr[2]->getSide() << endl;
    cout << "Perimeter: " << sqr[2]->Perimeter() << endl;
    cout << "Area:      " << sqr[2]->Area() << endl;
	
    cout << "Square 3" << endl;
    cout << "Side:      " << sqr[3]->getSide() << endl;
    cout << "Perimeter: " << sqr[3]->Perimeter() << endl;
    cout << "Area:      " << sqr[3]->Area() << endl;

    return 0;
}
