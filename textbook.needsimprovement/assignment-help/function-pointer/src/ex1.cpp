#include <stdio.h>

// function implementation
void hello() {
    printf("hello world!");
}

// calling from main
int main() {
    /* void (*funcPtr)() = hello; can also be used here */
    void (*funcPtr)() = &hello;
    /* funcPtr(); can also be used here */
    (*funcPtr)();
    return 0;
}