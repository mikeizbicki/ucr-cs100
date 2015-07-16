#include <stdio.h>

// function implementation
int add(int x, int y){
    return x + y;
}

// calling from main
int main() {
    int (*funcPtr)(int, int) = NULL;

    /* funcPtr = add; */
    funcPtr = &add;
    /* int z = funcPtr(20, 10); */
    int z = (*funcPtr)(20, 10);
    printf("Add gives: %d\n", z);
    return 0;
}