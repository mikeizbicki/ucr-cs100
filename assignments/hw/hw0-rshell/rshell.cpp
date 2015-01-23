#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <string.h>
#include <exception>
#include <signal.h>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;

void quit(int exit_val) {
    cout << "\033[0m";
    exit(exit_val);
}

void my_handler(int s){
    cerr << endl;
    quit(1);
}

//Run a command and do error checking
//Return the return of the command (or 1 if it wasn't run)
int run_cmd_(char *cmd, char **argv) {
    if(strcmp(cmd, "exit") == 0) quit(0);
    int pid = fork();
    if(pid == -1) {
        perror("fork fail");
        return 1;
    } else if(pid == 0) {
        if(execvp(cmd,argv) != 0) {
            cerr << "FAILED" << endl;
            perror("error in execvp");
        }
        return 1;
    } else {
        int status;
        waitpid(pid, &status, WUNTRACED);
        //cerr << "Status of " << cmd << " is: " << status << endl;
        return status;
    }
}

//Take a string and pull out the command (first word) and arguments
// to pass to run_cmd_ to be run
int run_cmd(string line) {
    istringstream stream(line);
    vector<string> cmds_vec;
    string cmd;
    while(stream >> cmd) {
        cmds_vec.push_back(cmd);
    }
    
    char **argv = new char*[cmds_vec.size() + 1];
    for(int x=0; x<cmds_vec.size(); x++) {
        argv[x] = new char[cmds_vec.at(x).size() + 1];
        strcpy(argv[x], cmds_vec.at(x).c_str());
    }
    argv[cmds_vec.size()] = NULL;
    
    //for(int x=0; x<cmds_vec.size(); x++) {
    //    cerr << argv[x] << endl;
    //}
    
    return run_cmd_(argv[0], argv);
}

//Recursively parse and check the conditionals
//This is where the magic happens
int parse_conditional_(string cond, const vector<string>& cmds, int num) {
    int result;
    if(num == 0) {
        return run_cmd(cmds.at(0));
    } else if(num == 2) {
        result = run_cmd(cmds.at(num-2));
    } else {
        result = parse_conditional_(cmds.at(num-3), cmds, num-2);
    }
    if(result == 0 && (cond == "||")) return true;
    if(result != 0 && (cond == "&&")) return false;
    return run_cmd(cmds.at(num));
}

//Put conditionals into array to be parsed recursively
void parse_conditional(char cmds[]) {
    if(cmds == NULL) return;
    
    vector<string> parsed;
    string s_cmds = cmds;
    
    char prev = '\0';
    int last_found = 0;
    for(int i=0; i < s_cmds.size(); i++) {
        if(s_cmds.at(i) == prev && (prev == '&' || prev == '|')) {
            parsed.push_back(s_cmds.substr(last_found, i-last_found-1));
            parsed.push_back(string(2, prev));
            last_found = i + 1;
        }
        prev = s_cmds.at(i);
    }
    parsed.push_back(s_cmds.substr(last_found, s_cmds.size() - last_found));
    
    //TODO:
    //Fix case where all conditionals
    //Fix case where ends in a conditional
    //Fix case where starts in conditional
    
    //for(int x=0; x<parsed.size(); x++) {
    //    cout << parsed[x] << endl;
    //}
    
    if((parsed.size() % 2) == 0) {
        cerr << "Bad conditionals" << endl;
        return;
    }
    
    parse_conditional_((parsed.size() == 1) ? "" : parsed.at(parsed.size()-2),
                       parsed, parsed.size()-1);
}

void parse_semi(char cmds[]) {
    if(cmds == NULL) return;
    
    char *parsed = strtok(cmds, ";");
    while(parsed != NULL) {
        parse_conditional(parsed);
        parsed = strtok(NULL, ";");
    }
}

int main(int argc, char *argv[]) {
    //Change terminal color for the rest of the program
    cout << "\033[1m\033[35m";
    
    //Setup handler to change color back if they do ctrl-c
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    
    
	//while(true) {
    
    //Grab a line and convert it to a C-String
    string cmds;
    cout << "$ ";
    getline(cin, cmds);
    char cmd[cmds.size() + 1];
    strcpy(cmd, cmds.c_str());
    
    //Cut out a comment if there is one and pass to the parsers
    parse_semi(strtok(cmd, "#"));
    
    //run_cmd(cmd, argv);
    
    	//}*/
    quit(0);
}
