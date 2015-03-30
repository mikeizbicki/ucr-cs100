//you can make your own elements too

#include <iostream>
#include <map>

using namespace std;

class coin {
        double radius;
    public:
        void setRadius(double r){radius = r;}
        double getRadius() {return radius;}
        double area() {return 3.14159265 * radius * radius;}
        void printCoinSpecs();
};

void coin::printCoinSpecs() {
    cout << "Radius(mm): " << getRadius() << endl;
    cout << "Area(mm^2): " << area() << endl;
    return;
}

int main(int argc, char* argv[]) {
    map<string, coin> UScoins;
    UScoins["penny"].setRadius(9.525);
    UScoins["nickel"].setRadius(10.605);
    UScoins["dime"].setRadius(8.955);
    UScoins["quarter"].setRadius(12.13);
    UScoins["Penny"].setRadius(9.525);
    UScoins["Nickel"].setRadius(10.605);
    UScoins["Dime"].setRadius(8.955);
    UScoins["Quarter"].setRadius(12.13);
    UScoins["PENNY"].setRadius(9.525);
    UScoins["NICKEL"].setRadius(10.605);
    UScoins["DIME"].setRadius(8.955);
    UScoins["QUARTER"].setRadius(12.13);
    
    for (int i = 1 ; i < argc ; i++) {
        cout << argv[i] << ": " << endl;
        UScoins[string(argv[i])].printCoinSpecs();
    }
    return 0;
}
