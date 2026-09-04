#ifndef PONG_GAME_MANAGER_H
#define PONG_GAME_MANAGER_H

#include "game/bar.h"
#include "game/ball.h"
#include "game/game_window.h"

typedef struct {
    bool was_initialized;
    GameWindow *window;
    Bar *player;
    Bar *enemy;
    Ball *ball;
} PongGameConfig;

void game_init(PongGameConfig *game);
void game_deinit(PongGameConfig *game);
void game_loop(PongGameConfig *game);
void game_handle_up_button_pressed(PongGameConfig *game);
void game_handle_up_button_released(PongGameConfig *game);
void game_handle_down_button_pressed(PongGameConfig *game);
void game_handle_down_button_released(PongGameConfig *game);

#endif