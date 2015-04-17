#include <iostream>
#include<stdio.h>
#include<sys/types.h>
#include <sys/wait.h>
#include<unistd.h>
#include <stdlib.h>

using namespace std;

#define prints 10000

int main() {
	for(int j=0; j<=3; j++){
		int child1=fork();
		if(child1==-1)
		{	
			perror("fork");
			exit(1);
		}
		else if(child1==0)
		{
			char x;
			if(j==0){
				x = 'A';
			}
			else if (j == 1) {
				x = 'B';
			}
			else if (j == 2) {
				x = 'C';
			}
			else if (j ==  3) {
				x = 'D';
			}
				for(int i=0; i<prints; i++) {
					cout << x << flush;
				}
				cout <<endl << getpid()<< endl;
				exit(1);
		
		}
		else if(wait(0)==-1)
			perror("error with wait(0)");
	}
	return 0;
}

