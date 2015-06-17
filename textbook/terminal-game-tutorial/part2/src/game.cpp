#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>

#include "game.h"

struct {
    vec2i pos;
    char disp_char;
} player;

WINDOW* wnd;

int init() {
    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    // enable function keys
    keypad(wnd, true);

    // disable input blocking
    nodelay(wnd, true);

    // hide cursor
    curs_set(0);

    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    // enable color modification
    start_color();

    // draw box around screen
    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);

    return 0;
}


void run() {

    player.disp_char = '0';
    player.pos = {10, 5};

    int in_char;

    bool exit_requested = false;

    while(1) {
        in_char = wgetch(wnd);

        mvaddch(player.pos.y, player.pos.x, ' ');

        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w':
                player.pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
                player.pos.y += 1;
                break;
            case KEY_LEFT:
            case 'a':
                player.pos.x -= 1;
                break;
            case KEY_RIGHT:
            case 'd':
                player.pos.x += 1;
                break;
            default:
                break;
        }

        mvaddch(player.pos.y, player.pos.x, player.disp_char);

        if(exit_requested) break;

        usleep(10000); // 10 ms

        refresh();
    }
}


void close() {
    endwin();
}
