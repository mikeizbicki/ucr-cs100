#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

void quit() { exit(0); }
void hello() { cerr << "hello\n"; }
void goodbye() { cerr << "goodbye\n"; }

int main()
{
    map<string, void (*)()> commands;
    commands["hello"] = hello;
    commands["goodbye"] = goodbye;
    commands["exit"] = quit;

    while (true) {
         string cmd;
         cout << "$ ";
         cin >> cmd;
         //commands[cmd]();
         commands.at(cmd)();
    }

    return 0;
}
