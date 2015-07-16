#include <iostream>
#include <vector>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void segfault1(){
//This produces a very
//common segfault

     //how big is the array?
     int ten[10];
     int twenty = 20;

     for(int i =0; i < twenty; ++i){
          ten[i] = i;
          cout << "loop: " << ten[i] << endl;
     }
}

int segfault2(int x){
//This also produces a segfault
//because there's no base case
//to end the recursive calls
     //if(x >= 1) return 0;

     return segfault2(x-1);
}

int factorial(int x){
//This is going to find the factorial of a number
     int y;
     if(x <= 1){ return 1;}
          y = x* factorial(x-1);
          return y;
}

int initialize(){

     int p;
     for(int i = 1; i <= 5; i++){
          p = p*i;
     }
     return p;
}

bool leap_year(){
//This function determines if
//a given year is a leap year

     int year;

     cout <<"Please enter the year in question:  ";
     cin >> year;

     if(year % 4 == 0 && year %100 != 0){
          cout <<"\nYes, " << year <<" is a leap year.";
          return true;
     }

     else {
          cout <<"\nNo, " << year <<" is not a leap year.";
          return false;
     }
}

void my_max(){
//This is going to sort some variables
//Unfortunately, none of the variables have been
//initialized...ouch!

     int first, second;
     int a,b;

     if(a > b ){
          first = a;
          second = b;
     }
     else if(a < b) {
          first = b;
          second = a;
     }
     else if(a == b) {cout << "You GDB often?" << endl;}

     cout <<"first:  "<<  first << endl;
     cout <<"second: "<< second << endl;
}

void simple_fork(){
//This is a simple use case
//of the sys call fork
//child and parent are
//separate

     int pid = fork();
     if(pid == -1){ perror("error in fork");}

     else if(pid == 0){
          cout <<"CHILD says 'I am a child' "<< endl;
          leap_year();
          exit(0);
          //set follow-fork-mode to see what's happening
     }
     else if(pid > 0){
          wait(0);
          cout <<"\nPARENT says 'I am your parent' " << endl;
          cout <<"Enter a number and I'll get the factorial: ";
          int x;
          cin >> x;
          cout << factorial(x) << endl;
     }
}


int main(){


while (1){
     int number;

     cout <<"\nEnter 0 to quit" << endl;
     cout <<"Enter 1 to see a segfault " << endl;
     cout <<"Enter 2 to see another common segfault" << endl;
     cout <<"Enter 3 to find a factorial" << endl;
     cout <<"Enter 4 to look at an unitialized var " << endl;
     cout <<"Enter 5 to find out if a year is a leap year" << endl;
     cout <<"Enter 6 to run max on unitialized var's" << endl;
     cout <<"Enter 7 to see some processes" << endl;
     cout << endl;
     cout <<"Enter a number and we'll run a function: ";
     cin >> number;

     cout << endl;
     cout << endl;
     if(number == 0) {return 0;}
     if(number == 1){
//          cout <<"This will produce a segfault" << endl;
          segfault1();
     }
     if(number == 2){
//          cout <<"This too will produce a segfault" << endl;
          segfault2(10);
     }
     if(number == 3){
          cout << "enter another number: ";
          int x;
          cin >> x;
          cout << "Finding the factorial of " << x << endl;
          cout <<"The facorial of " << x <<" is: ";
          cout << factorial(x) << endl;

     }
     if(number == 4){
          cout <<"Here we'll call a function that will do some math";
          cout <<" without first initializing" << endl;
          cout << initialize() << endl;
     }

     if(number == 5){
          leap_year();
     }
     if(number == 6){
          cout <<"Here are some variables that haven't been initialized ";
          cout <<"but we'll do something with them anyways" << endl;

          my_max();
     }
     if(number == 7){
          cout <<"Let's use a system call and see some processes" << endl;
          simple_fork();
     }
     cout << endl;
     }

     return 0;
}
