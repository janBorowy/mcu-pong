#include "game/bar.h"
#include "driver/double_max7219_display.h"
#include <stdlib.h>

Bar *bar_create(int x) {
    Bar *bar = malloc(sizeof(Bar));
    bar->x = x;
    bar->y = 3;
    bar->moving_down = false;
    bar->moving_up = false;
}

void bar_update(Bar *bar) {
    if (bar->moving_down && bar->moving_up) return;
    if (bar->moving_up) {
        if (bar->y > 0) {
            bar->y--;
        }
    }
    if (bar->moving_down) {
        if (bar->y < DISPLAY_ROWS - BAR_HEIGHT) {
            bar->y++;
        }
    }
}

void bar_draw(Bar *bar, DoubleMax7219Config *display) {
    display_set(display, bar->x, bar->y, true);
    display_set(display, bar->x, bar->y + 1, true);
    display_set(display, bar->x, bar->y + 2, true);
}