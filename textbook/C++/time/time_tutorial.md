#time.h
`time.h` is a C library that allow you to denote time in their programs.
Time in Unix is measured by [number of seconds](http://www.coolepochcountdown.com/) since Epoch (00:00:00 UTC, January 1, 1970).
To use time correctly in Unix, you must initialize a `time_t` or `struct tm` variable with `time()` or `localtime()`, respectively.

##Types
The `time.h` header defines three different types: `time_t`, `clock_t`, and `struct tm`.

###time_t
`time_t` is measured in terms of seconds since Epoch.
It is the easiest of the three types to use.

For example:
```
time_t time1 = 5;  // time1 is 5 seconds since Epoch at 00:00:05 UTC, January 1, 1970
```

###clock_t
`clock_t` measure time in terms of processor ticks.
It only increment when the processor is cycling for the current process, actions such as waiting for input or using `sleep()` does not count toward `clock_t`.
It starts counting when you run the program.

* To get seconds from `clock_t`, you must use the macro `CLOCKS_PER_SEC`.
`CLOCKS_PER_SEC` represents the number of processor ticks in a second for the user's processor, the value of `CLOCKS_PER_SEC` varies from processor to processor.

For example:
```
double seconds;
clock_t time2;
time2 = clock();
seconds = ((double) time2) / CLOCKS_PER_SEC; // time2 is the number of seconds since the start of the program
```

###struct tm
`struct tm` is a struct with members for different time categories.
```
struct tm {
    int tm_sec;    // seconds (0-60); 60 is for leap second
    int tm_min;    // minutes (0-59)
    int tm_hour;   // hour (0-23); number of hours since midnight
    int tm_mday;   // day (1-31)
    int tm_mon;    // month (0-11); number of months since January
    int tm_year;   // years since 1900; use negative number to denote year before 1900
    int tm_wday;   // day of week (0-6); number of days since Sunday 
    int tm_yday;   // day of year (0-365)
    int tm_isdst;  // daylight saving flag; positve means daylight saving is in effect,
                   //     0 means daylight saving is not in effect,
                   //     negative means daylight saving information is not available
};
```
Unlike `time_t` or `clock_t`, `struct tm` allow programmers to individually adjust specific value of time such as day(`tm_day`) and year(`tm_year`).
To use `struct tm` you must declear it as a pointer(`struct tm*`) and it is usually used in conjuction with a `time_t` varible.

For example:
```
struct tm *time1;
time_t time1;
time(&time1);
time1 = localtime(&time2);
time1->tm_mon = 4     // Changing the month to May
time1->tm_mday = 25   // Changing the day of month to 25th
```


##Useful time.h functions
Here are some of the commonly used `time.h` functions that will help you on your journey as a programmer.
The file `time_example.cpp` is an example program that utilize the functions below to correctly output the current time and show the elapsed time of the program.

* `time_t time(time_t *timer)`
  * Takes a `time_t*` as input and returns the seconds since Epoch in `time_t`
  * `time()` is used to initialize `time_t` variables
  * Let's try using `time()` to initialize a `time_t` with the current time:
  ```
  time_t startTime;
  time(&startTime);
  // startTime represent the number of seconds since Epoch
  ```

* `clock_t clock(void)`
  * Takes no input and returns the number of processor ticks since the start of the program in `clock_t`
  * `clock()` is used to initialize `clock_t` variables
  * Let's try to use `clock()` to find the elapsed time of a program:
    ```
    clock_t startClock, endClock;
    double elapsedSec;
    startClock = clock();
    // Run Program Here
    endClock = clock();
    elapsedSec = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
    // elapsedSec represent the elapsed time in seconds
    ```
  

* `char *ctime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns a formatted `char*`
  * `ctime()` is used as a way to make sense of `time_t` variables
  * Let's use `ctime()` to output a nicely formatted `time_t`:
  ```
  time_t time1;
  time(&time1);
  cout << "time1: " << ctime(&time1);
  ```
  * Here we outputed current time in the following format: `Mon Feb 23 20:20:46 2015`
 
* `struct tm *localtime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns a `struct tm*` in the local timezone
  * `localtime()` is used to initialize a `struct tm` using an initialized `time_t` variable
  * Let's initialize a `struct tm` in the local timezone with a `time_t`:
  ```
  time_t time1;
  struct tm *time2;
  time(&time1);
  time2 = localtime(&time1);  
  // time2 represent time1 in the local timezone
  ```
  * Here we initialized `time2` in the local timezone using the current time `time1`
  
* `struct tm *gmtime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns an equivalent `struct tm*` in the GMT timezone
  * `gmtime()` is used to initialize a `struct tm` using an initialized `time_t` variable
  * If the local timezone is GMT `localtime()` returns the same output as `gmtime()`
  * Let's initialize a `struct tm` in the GMT timezone with a `time_t`:
  ```
  time_t time1;
  struct tm *time2;
  time(&time1);
  time2 = gmtime(&time1);  
  // time2 represent time1 in the GMT timezone
  ```
  * Here we initialized `time2` in the GMT timezone using the current time `time1`
  
* `char *asctime(const struct tm *timeptr)`
  * Takes a `const struct tm*` as input and returns a formatted `char*`
  * `asctime()` is very similar to `ctime()`, the difference is that `asctime()` takes a `struct tm*` as argument
  * Let's use `asctime()` to output a nicely formatted `struct tm`:
  ```
  time_t time1;
  struct tm *time2;
  time(&time1);
  time2 = gmtime(&time1);  
  cout << "time2: " << asctime(time2);
  ```
  * Here we outputed current time in the following format: `Mon Feb 23 20:15:31 2015`

* `time_t mktime(struct tm *timeptr)`
  * Takes a `struct tm*` as input and returns a `const time_t*` in the local timezone
  * `mktime()` is used to initialize a `time_t` using an initialized `struct tm` variable
  * `mktime()` is basically the reverse of `localtime()`
  * Let's try initializing a `time_t` with a `struct tm`:
  ```
  time_t time1, time3;
  struct tm *time2;
  time(&time1);
  time2 = localtime(&time1);
  time3 = mktime(time2);  
  ```
  * Here we initialized `struct tm*` `time2` using the `time_t` `time1` and then using  `struct tm*` `time2` to initialize `time_t` `time3`
  * `time1`, `time2`, and `time3` all represent the same time
  
* `double difftime(time_t endTime, time_t startTime)`
  * Takes two `time_t` and returns the difference in seconds between `endTime` and `startTime` in `double`
  * `difftime` is only useful for finding time difference between periods of time greater than 1 second
  * Let's calculate the elapsed time of our program using two `time_t`:
  ```
  time_t startTime, endTime;
  double diff;
  time(&startTime);
  // Run Program Here
  time(&endTime);
  diff = difftime(endTime, startTime);
  // diff represent elapsed seconds
  ```
  * Here we calculated the time we used to run this program in number of seconds

When using a `time_t` variable to deal with current time, it is esstenial to use `time()` to initialize the variable.
While using a `clock_t` variable, you should use `CLOCKS_PER_SEC` to make sense of the processor ticks number.
If are using `struct tm` to denote a specific time, you should assign the `struct tm` members individually instead of using functions.
While if you are using `struct tm` to denote current time, you should use `localtime()` or `gmtime()` with an initialized `time_t` variable to convert the time.

##Timezones and Leap Seconds
Time in Unix is always calculated in terms of the UTC timezone.
When we choose to display time in another timezone, an offset is applied to the time variable to correctly calculate the time.
For example, when we use `localtime()` the function first look up our timezone, then it look up the offset of that timezone, the offset is then applied to the `time_t` argument, and then it returns a `struct tm` that corresponds to the same time as `time_t` argument but in our local timezone.

When a leap second occurs in Unix, the second at the time of the leap second is two seconds.
In other words, two seconds pass while one second is counted by the Unix clock.
This task is accomplished by jumping back one second after the leap second passed.
`time_t` on the other hand counts both of the seconds, because it represents the absolute seconds since Epoch.

##Tips for Handling Time in lab5
The [cp lab](../../../assignments/lab/lab5-cp/) requires you to time the elapsed time for each of the three copying method when the optional flag is passed in.
Instead of using `Timer.h`, you could use `time.h` to complete the lab.
For methods that takes less than 1 seconds, I suggest you use `clock()` with `CLOCKS_PER_SEC` as it is very accurate for handling microscopic passage of time.
For methods that takes more than 1 seconds, you could use `difftime()` as `time_t` increment slower than `clock_t`, preventing `clock_t` from reaching `DBL_MAX` in case of a large file such as `/usr/share/dict/linux.words`.

One possible implementation:
```
double elapsedTime;
clock_t startClock, endClock;
startClock = clock();
// Copy
endClock = clock();
elapsedTime = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
```
  
##Bonus Video
[The Problem with Time & Timezones](https://www.youtube.com/watch?v=-5wpm-gesOY) by [Computerphile](https://www.youtube.com/user/Computerphile)

[End of Time (Unix)](https://www.youtube.com/watch?v=QJQ691PTKsA) by [Numberphile](https://www.youtube.com/user/numberphile)