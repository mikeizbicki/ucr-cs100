#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <vector>

#include "game.h"
#include "ObjectField.h"


WINDOW* main_wnd;
WINDOW* game_wnd;

rect game_area;
rect screen_area;

vec2ui cur_size;

ObjectField asteroids;
ObjectField stars;

struct {
    vec2i pos;
    rect bounds;
    char disp_char;
    int energy;
} player;


int init() {
    
    srand(time(0));

    // ncurses init
    main_wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    curs_set(0);

    start_color();

    // define window areas
    //
    screen_area = { { 0, 0 }, { 80, 24 } };
    int infopanel_height = 4;
    game_wnd = newwin(  screen_area.height () - infopanel_height - 2,
                        screen_area.width() - 2,
                        screen_area.top() + 1,
                        screen_area.left() + 1 );

    main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);

    game_area = { { 0, 0 }, { screen_area.width() - 2, screen_area.height() - infopanel_height - 4 } };

    // useful color pairs
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    // enable function keys
    keypad(main_wnd, true);
    keypad(game_wnd, true);

    // disable input blocking
    nodelay(main_wnd, true);
    nodelay(game_wnd, true);

    // color check
    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    return 0;
}


void run() {

    int tick;

    // init character
    player.disp_char = 'o';
    player.pos = {10, 5};

    asteroids.setBounds(game_area);
    stars.setBounds(game_area);

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;

    // frame around screen
    wattron(main_wnd, A_BOLD);
    box(main_wnd, 0, 0);
    wattroff(main_wnd, A_BOLD);

    // horizontal dividing line
    wmove(main_wnd, game_area.bot() + 3, 1);
    whline(main_wnd, '-', screen_area.width() - 2);

    // initial draw
    wrefresh(main_wnd);
    wrefresh(game_wnd);

    tick = 0;
    while(1) {
        
        werase(game_wnd);

        // get input
        in_char = wgetch(main_wnd);
        in_char = tolower(in_char);

        // controls switch
        switch(in_char) {
            case 'q':
                exit_requested = true;
                break;
            case KEY_UP:
            case 'w':
            case 'i':
                if(player.pos.y > game_area.top())
                    player.pos.y -= 1;
                break;
            case KEY_DOWN:
            case 's':
            case 'k':
                if(player.pos.y < game_area.bot() + 1)
                    player.pos.y += 1;
                break;
            case KEY_LEFT:
            case 'a':
            case 'j':
                if(player.pos.x > game_area.left() + 1)
                    player.pos.x -= 1;
                break;
            case KEY_RIGHT:
            case 'd':
            case 'l':
                if(player.pos.x < game_area.right() - 2)
                    player.pos.x += 1;
                break;
            default:
                break;
        }
   
        // update object fields
        if(tick % 7 == 0)
            stars.update();

        if(tick > 100 && tick % 20 == 0)
            asteroids.update();

        // update player bounds 
        player.bounds = { { player.pos.x - 1, player.pos.y }, { 3, 1 } }; // player is 3x1

        // remove asteroid if collided
        for(size_t i = 0; i < asteroids.getData().size(); i++) {
            if(player.bounds.contains(asteroids.getData().at(i).getPos())) {
                asteroids.erase(i);
            }
        }

        // draw object fields
        for(auto s : stars.getData())
            mvwaddch(game_wnd, s.getPos().y, s.getPos().x, '.');

        for(auto a : asteroids.getData()) {
            wattron(game_wnd, A_BOLD);
            mvwaddch(game_wnd, a.getPos().y, a.getPos().x, '*');
            wattroff(game_wnd, A_BOLD);
        }

        // draw player body
        wattron(game_wnd, A_BOLD);
        mvwaddch(game_wnd, player.pos.y, player.pos.x, player.disp_char);
        wattroff(game_wnd, A_BOLD);

        // draw player sides
        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, player.pos.y, player.pos.x - 1, ACS_LARROW);
        mvwaddch(game_wnd, player.pos.y, player.pos.x + 1, ACS_RARROW);

        // draw engine flame
        if((tick % 10) / 3) {
            wattron(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
            mvwaddch(game_wnd, player.pos.y + 1, player.pos.x, ACS_UARROW);
            wattroff(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
        }

        wattroff(game_wnd, A_ALTCHARSET);

        // refresh all
        wrefresh(main_wnd);
        wrefresh(game_wnd);
        if(exit_requested || game_over) break;

        tick++;

        usleep(10000); // 10 ms
    }
}



void close() {
    delwin(main_wnd);
    delwin(game_wnd);
    endwin();
}
