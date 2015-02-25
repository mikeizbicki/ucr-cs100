#Time.h
`time.h` is a C library that allows users to denote time in their programs. Time in Unix is measured by number of seconds since Epoch (00:00:00 UTC, January 1, 1970). To use time correctly in Unix, the user must initialize a `time_t` or `struct tm` variable with functions.

##struct tm
The `time.h` header creates a structure `tm` with the following members:
<!--
| Names of Member | Description | Range | Note |
|-----------------------| --- | --- | --- |
| `int tm_sec` |  seconds | 0-60 | 60 is for leap second
| `int tm_min` |  minutes | 0-59 | |
| `int tm_hour` | hour | 0-23 | number of hours since midnight |
| `int tm_mday` | day | 1-31 | |
| `int tm_mon` | month | 0-11 | number of months since January |
| `int tm_year` | years since 1900 | | use negative number to denote year before 1900 |
| `int tm_wday` | day of week | 0-6 | number of days since Sunday |
| `int tm_yday` | day of year | 0-365 | |
| `int tm_isdst` | daylight saving flag | any integer | positve means daylight saving is in effect, 0 means daylight saving is not in effect, negative means daylight saving information is not available |
-->

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

* `char *asctime(const struct tm *timeptr)`
  * Takes a `const struct tm*` as input and returns a formatted `char*`
  * Example Output: `Mon Feb 23 20:15:31 2015`

* `clock_t clock(void)`
  * Takes no input and retuens the processor time used in `clock_t`
  * Example:
  ```
  clock_t t;
  t = clock();
  // Run Program Here
  t = clock() - t;
  // t represent the elapsed processor time
  ```

* `char *ctime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns a formatted `char*`
  * Example Output: `Mon Feb 23 20:20:46 2015`

* `double difftime(time_t endTime, time_t startTime)`
  * Takes two `time_t` and returns the difference in seconds between endTime and startTime in `double`
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

* `struct tm *gmtime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns an equivalent `struct tm*` in GMT timezone
  * Example:
  ```
  time_t t1;
  struct tm *t2;
  time(&t1);
  t2 = gmtime(&t1)
  // t2 represent t1 in the GMT timezone
  ```

* `struct tm *localtime(const time_t *timer)`
  * Takes a `const time_t*` as input and returns a `struct tm*` in the local timezone
  * Example:
  ```
  time_t t1;
  struct tm *t2;
  time(&t1);
  t2 = localtime(&t1)
  // t2 represent t1 in the local timezone
  ```

* `time_t mktime(struct tm *timeptr)`
  * Takes a `struct tm*` as input and returns a `const time_t*` in the local timezone
  * Example:
  ```
  struct tm *t1;
  time_t t2;
  time(&t1);
  t2 = mktime(t1)
  // t2 represent t1 in the local timezone
  ```
  
* `time_t time(time_t *timer)`
  * Takes a `time_t*` as input and returns the seconds since Epoch in `time_t`
  * Example:
  ```
  time_t t;
  t = time(&t);
  // t represent the seconds since Epoch
  ```
  
##time_example.cpp
The `time_example.cpp` is an example program that utilize the above functions to correctly output the current time and show the elapsed time of the program.
  
##Bonus Video
[The Problem with Time & Timezones](https://www.youtube.com/watch?v=-5wpm-gesOY) by [Computerphile](https://www.youtube.com/user/Computerphile)