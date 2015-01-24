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
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

//The following three functions are taken from the first answer on this question
//http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
string &trim(string &s) {
    return ltrim(rtrim(s));
}

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
    if(strcmp(cmd, "exit") == 0) {
        cout << "\033[0m";
        exit(0);
    }
    int pid = fork();
    if(pid == -1) {
        perror("fork fail");
        return 1;
    } else if(pid == 0) {
        if(execvp(cmd,argv) != 0) {
            char err[7 + strlen(cmd) + 1];
            strcpy(err, "-bqsh: ");
            strcat(err, cmd);
            perror(err);
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
    
    int result = run_cmd_(argv[0], argv);
    for(int x=0; x<=cmds_vec.size(); x++) {
        delete []argv[x];
    }
    delete []argv;
    return result;
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
    
    //Check if they lead with a conditional...
    if(s_cmds.substr(0, 2) == "&&" || s_cmds.substr(0, 2) == "||") {
        cerr << "Bad conditionals" << endl;
        return;
    }
    
    //Parse parse parse
    char prev = '\0';
    int last_found = 0;
    for(int i=0; i < s_cmds.size(); i++) {
        if(s_cmds.at(i) == prev && (prev == '&' || prev == '|')) {
            parsed.push_back(s_cmds.substr(last_found, i-last_found-1));
            trim(parsed.at(parsed.size()-1));
            if(parsed.at(parsed.size()-1) == "") parsed.pop_back();
            parsed.push_back(string(2, prev));
            last_found = i + 1;
        }
        prev = s_cmds.at(i);
    }
    parsed.push_back(s_cmds.substr(last_found, s_cmds.size() - last_found));
    trim(parsed.at(parsed.size()-1));
    if(parsed.at(parsed.size()-1) == "") parsed.pop_back();
    
    //Output args for debugging
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
    char space_test[strlen(cmds) + 1];
    strcpy(space_test, cmds);
    if(strtok(space_test, " \t\r\n") == NULL) return;
    
    char *parsed = strtok(cmds, ";");
    while(parsed != NULL) {
        parse_conditional(parsed);
        parsed = strtok(NULL, ";");
    }
}

int main(int argc, char *argv[]) {

    //Setup handler to change color back if they do ctrl-c
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = my_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
    
    
	while(true) {
        
        //Grab Username
        char uname[64] = "";
        if(getlogin_r(uname, sizeof(uname)-1) != 0) {
            perror("Error fetching Username");
            strcpy(uname, "???");
        }
        
        //Grab hostname
        char hostname[64] = "";
        if(gethostname(hostname, sizeof(hostname)-1) != 0) {
            perror("Error fetching Hostname");
            strcpy(hostname, "???");
        }
        
        //Grab a line and convert it to a C-String
        string cmds;
        cout << GREEN << uname << "@" << YELLOW << hostname << RESET << "$ ";
        getline(cin, cmds);
        //cout << "\033[0m";
        char cmd[cmds.size() + 1];
        strcpy(cmd, cmds.c_str());
        
        if(cmds.at(0) == '#') continue;
        
        
        //Cut out a comment if there is one and pass to the parsers
        parse_semi(strtok(cmd, "#"));
    }
    quit(0);
}
