#ifndef GAME_H
#define GAME_H

typedef struct {
    uint_fast8_t x;
    uint_fast8_t y;
} vec2ui;

typedef struct {
    int_fast8_t x;
    int_fast8_t y;
} vec2i;

int init();
void run();
void close();

#endif
