#ifndef BAR_H
#define BAR_H

#include "game/game_window.h"
#include <stdint.h>
#include <stdbool.h>

#define BAR_HEIGHT PIXEL_HEIGHT_TIMES(2)
#define BAR_SPEED 16

typedef struct {
    uint16_t x;
    uint16_t y;
    bool moving_up;
    bool moving_down;
} Bar;

Bar *bar_create(int x);
void bar_update(Bar *bar);
void bar_draw(Bar *bar, GameWindow *window);

#endif