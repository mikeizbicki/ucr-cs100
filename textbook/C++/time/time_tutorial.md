#time.h
`time.h` is a C library that allows users to denote time in their programs.
Time in Unix is measured by [number of seconds](http://www.coolepochcountdown.com/) since Epoch (00:00:00 UTC, January 1, 1970).
To use time correctly in Unix, the user must initialize a `time_t` or `struct tm` variable with `time()` and `localtime()`, respectively.

**IMPORTANT:** The types and functions in `time.h` is similar but different to the types and functions of the same name from the timing utilities defined in GNU Octave, this tutorial is for the C library `time.h`.

##struct tm
The `time.h` header defines the structure `tm`:


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

##Useful time.h functions


* `time_t time(time_t *timer)`
  * Takes a `time_t*` as input and returns the seconds since Epoch in `time_t`
  * `time()` is usually used to initialize `time_t` variables
  * Example:
  ```
  time_t startTime;
  time(&startTime);
  // startTime represent the number of seconds since Epoch
  ```
  Now `startTime` is initialized with the current seconds since Epoch.

* `clock_t clock(void)`
  * Takes no input and retuens the number of processor ticks since the start of the program in `clock_t`
  * `clock()` is usually used to initialize `clock_t` variables
  * Note that `clock_t` only increase when the processor is cycling for the current process, actions such as waiting for input or using `sleep()` does not count toward `clock_t`
  * The macro `CLOCKS_PER_SEC` is often used in conjunction with `clock()`
    * it represents the number of processor ticks in a second for the user's processor
    * the value of `CLOCKS_PER_SEC` varies from processor to processor
  * Example:
    ```
    clock_t startClock, endClock;
    double elapsedSec;
    startClock = clock();
    // Run Program Here
    endClock = clock();
    elapsedSec = ((double) (endClock - startClock)) / CLOCKS_PER_SEC;
    // elapsedSec represent the elapsed time in seconds
    ```
  
  * Here we calculated the time we used to run this program in terms of processor ticks
  * **Note:** `clock()` in `time.h` is a very different function than the `clock()` defined in GNU Octave, please be careful not to mix these two up.

* `char *ctime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns a formatted `char*`
  * `ctime()` is commonly used way to make sense of `time_t` variables
  * Example:
  ```
  time_t time1;
  time(&time1);
  cout << "time1: " << ctime(&time1);
  ```
  * Here we outputed current time in the following format: `Mon Feb 23 20:20:46 2015`
 
* `struct tm *localtime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns a `struct tm*` in the local timezone
  * `localtime()` is usually used to initialize a `struct tm` using an initialized `time_t` variable
  * Example:
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
  * If the local timezone is GMT `localtime()` returns the same output as `gmtime`
  * Example:
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
  * `asctime()` is very similar to `ctime`, the difference is that `asctime()` takes a `struct tm*` as argument
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
  * `mktime` is basically the reverse of `localtime()` and `gmtime`
  * Example:
  ```
  time_t time1;
  struct tm *time2;
  time(&time1);
  time2 = localtime(&time1);
  time3 = mktime(time2);  
  ```
  * Here we initialized `struct tm*``time2` using the `time_t` `time1` and then using  `struct tm*``time2` to initialize `time_t` `time3`
  * `time1`, `time2`, and `time3` all represent the same time
  
* `double difftime(time_t endTime, time_t startTime)`
  * Takes two `time_t` and returns the difference in seconds between `endTime` and `startTime` in `double`
  * `difftime` is only useful for finding time difference between periods of time greater than 1 second
  * Example:
  ```
  time_t startTime, endTime;
  double diff;
  time(&startTime);
  // Run Program Here
  time(&endTime);
  diff = difftime(endTime, startTime);
  // diff represent elapsed seconds
  ```
  * Here we calculated the time we used to run this program in terms of seconds
  
##time_example.cpp
The `time_example.cpp` is an example program that utilize the above functions to correctly output the current time and show the elapsed time of the program.

##Tips for Handling Time in lab5
The [cp lab](https://github.com/mikeizbicki/ucr-cs100/tree/2015winter/assignments/lab/lab5-cp) requires you to time the elapsed time for each of the three copying method when the optional flag is passed in.
There are, of course, multiple ways to accomplish this part of the lab.
For methods that takes less than 1 seconds, I suggest you use `clock()` as it is very accurate for handling microscopic passage of time.
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