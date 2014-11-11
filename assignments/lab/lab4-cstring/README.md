# cstring functions

You should complete this lab using pair programming with a new partner.

### coding instructions

In this lab you will implement your own versions of the functions found in the cstring library.  Create a header file `myCString.h` which contains your implementation of the following functions: 

1. `strcpy`
1. `strncpy`
2. `strcat`
2. `strncat`
3. `strcmp`
4. `strchr`
5. `strstr`
6. `strlen`

You must write each function from scratch.  You CANNOT use the functions provided within the cstring library to implement your own; however, using your own implementation of one function in another, such as `strlen` in `strcpy`, is fine.   A simple way to avoid conflicts with cstring is to give a different name to your own functions (e.g., `my_strcpy`, `my_strcmp`).

You will need to look up the man pages for each of these functions to make sure they work just like the versions in the library.  

**IMPORTANT:** You should be implementing the cstring versions, NOT the string versions (i.e. the parameters should be `char*` and not `std::string`).  Your function signatures should be exactly the same as the standard cstring versions.  You should not implement your own string class.

**IMPORTANT:** None of these functions allocate memory.  They assume the user calling them has already allocated the correct amount of memory.  If you are using the `new` or `malloc` in any of these functions, you are doing something wrong.

Write a `main.c` file that tests your library.  You must use the C compiler `gcc` to compile your program.  You are not allowed to use `g++`.  This will ensure you are not using any C++ features in your code. You must have detailed tests that cover every possible edge case.

### deliverables

When finished, demo your working code for the TA.  
