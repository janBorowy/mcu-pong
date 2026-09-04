#include "game/bar.h"
#include "game/game_window.h"
#include <stdlib.h>

Bar *bar_create(int x) {
    Bar *bar = malloc(sizeof(Bar));
    bar->x = x;
    bar->y = PIXEL_HEIGHT_TIMES(3);
    bar->moving_down = false;
    bar->moving_up = false;
}

void bar_update(Bar *bar) {
    if (bar->moving_down && bar->moving_up) return;
    if (bar->moving_up) {
        if (bar->y > 0) {
            bar->y -= BAR_SPEED;
            if (bar->y < 0) {
                bar->y = 0;
            }
        }
    }
    if (bar->moving_down) {
        if (bar->y < GAME_WINDOW_HEIGHT - BAR_HEIGHT) {
            bar->y += BAR_SPEED;
            if (bar->y > GAME_WINDOW_HEIGHT - BAR_HEIGHT) {
                bar->y = GAME_WINDOW_HEIGHT - BAR_HEIGHT;
            }
        }
    }
}

void bar_draw(Bar *bar, GameWindow *window) {
    game_window_draw_pixel(window, bar->x, bar->y);
    game_window_draw_pixel(window, bar->x, bar->y + PIXEL_HEIGHT_TIMES(1));
    game_window_draw_pixel(window, bar->x, bar->y + PIXEL_HEIGHT_TIMES(2));
}