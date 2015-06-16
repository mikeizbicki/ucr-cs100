#include <cstdint>

#include "game.h"



int main(int argc, char **argv){
    // parse 
    // quiz q;
    // quiz();
    
    int init_status = init(); 

    if(init_status == 0)
        run();

    return 0;
}
