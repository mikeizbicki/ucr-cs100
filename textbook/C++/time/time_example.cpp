#include <time.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    time_t startTime, endTime, elapsedTime, time1, time3;
    clock_t startClock, endClock, elapsedClock;
    struct tm *time2;
    
    time(&startTime);                            // time() put the number of seconds since Epoch into its argument
    
    startClock = clock();                        // clock() returns the number of clock ticks since the program begin
    
    time(&time1);
    cout << "time1: " << ctime(&time1);          // ctime() convert a time_t into a char*
    time2 = localtime(&time1);                   // using localtime() or gmtime() convert a time_t into their respective time zone in struct tm*
    
    cout << "\ntime_t convert to struct tm:\n";
    cout << "sec: " << time2->tm_sec << endl; 
    cout << "min: " << time2->tm_min << endl;
    cout << "hour: " << time2->tm_hour << endl;
    cout << "mday: " << time2->tm_mday << endl;
    cout << "mon: " << time2->tm_mon << endl;
    cout << "year: " << time2->tm_year << endl;
    cout << "wday: " << time2->tm_wday << endl;
    cout << "yday: " << time2->tm_yday << endl;
    cout << "isdst: " << time2->tm_isdst << endl;
    
    cout << "\ntime2: " << asctime(time2);        // asctime() convert a struct tm* to char* 
    time3 = mktime(time2);                        // mktime() convert a struct tm* to time_t
    cout << "time3: " << ctime(&time3); 
    
    cout << "\nwaiting for 5 seconds\n\n";
    sleep(5);
    
    time(&endTime);
    
    endClock = clock();                          
    
    elapsedClock = endClock - startClock;
    elapsedTime = difftime(endTime, startTime);  // difftime() returns the number of seconds between the two arguments
    
    cout << "startTime: " << ctime(&startTime);
    cout << "endTime: " << ctime(&endTime);     
    cout << "elapsedTime: " << elapsedTime << " seconds" << endl;
    
    
    cout << "\nin clock ticks:";
    cout << "\nstartClock: " << startClock << endl;
    cout << "endClock: " << endClock << endl;
    cout << "elapsedClock: " << elapsedClock << endl;
    cout << "elapsedClock in seconds: " << ((double) (endClock - startClock)) / CLOCKS_PER_SEC << endl; // as you can see from the output of this line, clock_t only elapse when the processor cycle through the current process
    
    return 0;
}