#ifndef PONG_GAME_MANAGER_H
#define PONG_GAME_MANAGER_H

#include "driver/double_max7219_display.h"
#include "game/bar.h"

typedef struct {
    bool was_initialized;
    DoubleMax7219Config *display;
    Bar *player;
    Bar *enemy;
} PongGameConfig;

void game_init(PongGameConfig *game);
void game_deinit(PongGameConfig *game);
void game_loop(PongGameConfig *game);
void game_handle_up_button_pressed(PongGameConfig *game);
void game_handle_up_button_released(PongGameConfig *game);
void game_handle_down_button_pressed(PongGameConfig *game);
void game_handle_down_button_released(PongGameConfig *game);

#endif