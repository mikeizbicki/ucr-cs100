#include <string>
#include <ncurses.h>



int main(int argc, char **argv){
    
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    move(5, 5);

    std::string text = "Hello world!";
    for(size_t i = 0; i < text.size(); i++) {
        addch(text[i]);
        addch(' ');
    }

    refresh();

    while(1);

    endwin();
    return 0;
}
