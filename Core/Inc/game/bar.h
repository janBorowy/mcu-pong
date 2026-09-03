#ifndef BAR_H
#define BAR_H

#include "driver/double_max7219_display.h"
#include <stdint.h>
#include <stdbool.h>

#define BAR_HEIGHT 3

typedef struct {
    uint8_t x;
    uint8_t y;
    bool moving_up;
    bool moving_down;
} Bar;

Bar *bar_create(int x);
void bar_update(Bar *bar);
void bar_draw(Bar *bar, DoubleMax7219Config *display);

#endif