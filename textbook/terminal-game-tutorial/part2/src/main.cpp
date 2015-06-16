#include <cstdint>
#include "game.h"


int main(int argc, char **argv){
   
    int init_status = init();

    if(init_status == 0)
        run();

    close();

    return 0;
}
