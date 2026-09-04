#include "game/game_window.h"
#include <stdint.h>


void game_window_init(GameWindow *game_window) {
    display_init(game_window->led_matrix);
}

void game_window_draw_pixel(GameWindow *game_window, uint16_t x, uint16_t y) {
    display_set(game_window->led_matrix, x / 32, y / 32, true);
}

void game_window_clear(GameWindow *game_window) {
    display_clear(game_window->led_matrix);
}

void game_window_refresh(GameWindow *game_window) {
    display_refresh(game_window->led_matrix);
}