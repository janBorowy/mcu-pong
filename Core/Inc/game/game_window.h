#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "driver/double_max7219_display.h"
#include <stdint.h>

#define GAME_WINDOW_HEIGHT 256
#define GAME_WINDOW_WIDTH 512
#define PIXEL_HEIGHT_TIMES(n) (32*(n))

typedef struct {
    DoubleMax7219Config *led_matrix;
} GameWindow;

void game_window_init(GameWindow *game_window);
void game_window_draw_pixel(GameWindow *game_window, uint16_t x, uint16_t y);
void game_window_clear(GameWindow *game_window);
void game_window_refresh(GameWindow *game_window);

#endif