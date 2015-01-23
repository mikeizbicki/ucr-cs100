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

using namespace std;

void quit(int exit_val) {
    cout << "\033[0m";
    exit(exit_val);
}

void my_handler(int s){
    cerr << endl;
    quit(1);
    
}

int run_cmd(char *cmd, char **argv) {
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
        return status;
    }
}

void parse_conditional(char cmds[]) {
    if(cmds == NULL) return;
    
    char *parsed = strtok(cmds, "&&");
    cerr << "Parssssed: " << parsed << endl;
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
