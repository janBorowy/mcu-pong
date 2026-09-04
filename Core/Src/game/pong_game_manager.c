#include "game/pong_game_manager.h"
#include "game/enemy_controller.h"
#include "game/game_window.h"
#include "stdlib.h"

#define BALL_VX 16
#define BALL_VY 8

void update(PongGameConfig *game);
void draw(PongGameConfig *game);
Ball *create_ball_random_direction();

void game_init(PongGameConfig *game) {
    game_window_init(game->window);

    game->player = bar_create(0);
    game->enemy = bar_create(PIXEL_HEIGHT_TIMES(15));
    game->ball = create_ball_random_direction();
    game->enemy_controller = enemy_controller_create(game->enemy); 

    game->was_initialized = true;
}

void game_deinit(PongGameConfig *game) {
    free(game->player);
    free(game->enemy);
    free(game->ball);
    free(game->enemy_controller);
}

void game_loop(PongGameConfig *game) {
    update(game);
    draw(game);
}

void game_handle_up_button_pressed(PongGameConfig *game) {
    game->player->moving_up = true;
}

void game_handle_down_button_pressed(PongGameConfig *game) {
    game->player->moving_down = true;
}

void game_handle_up_button_released(PongGameConfig *game) {
    game->player->moving_up = false;
}

void game_handle_down_button_released(PongGameConfig *game) {
    game->player->moving_down = false;
}

void update(PongGameConfig *game) {
    enemy_controller_update(game->enemy_controller, game->ball);
    bar_update(game->player);
    bar_update(game->enemy);
    ball_update(game->ball, game->player, game->enemy);

    if (game->ball->enemy_scored || game->ball->player_scored) {
        game_deinit(game);
        game_init(game);
    }
}

void draw(PongGameConfig *game) {
    game_window_clear(game->window);
    bar_draw(game->player,game->window);
    bar_draw(game->enemy, game->window);
    ball_draw(game->ball, game->window);
    game_window_refresh(game->window);
}

Ball *create_ball_random_direction() {
    uint8_t dir = rand() % 6;
    switch (dir) {
        case 0:
            return ball_create(PIXEL_HEIGHT_TIMES(7), PIXEL_HEIGHT_TIMES(4), -BALL_VX - BALL_VY, 0);
        case 1:
            return ball_create(PIXEL_HEIGHT_TIMES(8),PIXEL_HEIGHT_TIMES(4), BALL_VX + BALL_VY, 0);
        case 2:
            return ball_create(PIXEL_HEIGHT_TIMES(7),PIXEL_HEIGHT_TIMES(3), -BALL_VX, -BALL_VY);
        case 3:
            return ball_create(PIXEL_HEIGHT_TIMES(7),PIXEL_HEIGHT_TIMES(4), -BALL_VX, BALL_VY);
        case 4:
            return ball_create(PIXEL_HEIGHT_TIMES(8),PIXEL_HEIGHT_TIMES(3), BALL_VX, -BALL_VY);
        case 5:
        default:
            return ball_create(PIXEL_HEIGHT_TIMES(8),PIXEL_HEIGHT_TIMES(4), BALL_VX, BALL_VY);
    }
}