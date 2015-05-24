#include <iostream>
#include <map>

using namespace std;

void initialize_month_map(map<string, int> &month_map);

int main(int argc, char* argv[]) {
    map<string, int> month_map;
    initialize_month_map(month_map);
    
    for(int i = 1 ; i < argc ; i++) {
        cout << argv[i] << " = " << month_map[argv[i]] << endl;
    }
    return 0;
}

void initialize_month_map(map<string, int> &month_map) {
    month_map["jan"] = 1;
    month_map["feb"] = 2;
    month_map["mar"] = 3;
    month_map["apr"] = 4;
    month_map["may"] = 5;
    month_map["jun"] = 6;
    month_map["jul"] = 7;
    month_map["aug"] = 8;
    month_map["sep"] = 9;
    month_map["oct"] = 10;
    month_map["nov"] = 11;
    month_map["dec"] = 12;
    
    month_map["January"] = 1;
    month_map["February"] = 2;
    month_map["March"] = 3;
    month_map["April"] = 4;
    month_map["May"] = 5;
    month_map["June"] = 6;
    month_map["July"] = 7;
    month_map["August"] = 8;
    month_map["September"] = 9;
    month_map["October"] = 10;
    month_map["November"] = 11;
    month_map["December"] = 12;
}
