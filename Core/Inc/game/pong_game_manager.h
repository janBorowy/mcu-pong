#ifndef PONG_GAME_MANAGER_H
#define PONG_GAME_MANAGER_H

#include "game/bar.h"
#include "game/ball.h"
#include "game/enemy_controller.h"
#include "game/game_window.h"
#include "audio_player.h"

typedef struct {
    bool was_initialized;
    bool frozen;
    GameWindow *window;
    Bar *player;
    Bar *enemy;
    Ball *ball;
    EnemyController *enemy_controller;
    AudioPlayer *audio_player;
} PongGameConfig;

void game_init(PongGameConfig *game);
void game_deinit(PongGameConfig *game);
void game_reset(PongGameConfig *game);
void game_loop(PongGameConfig *game);
void game_handle_up_button_pressed(PongGameConfig *game);
void game_handle_up_button_released(PongGameConfig *game);
void game_handle_down_button_pressed(PongGameConfig *game);
void game_handle_down_button_released(PongGameConfig *game);

#endif