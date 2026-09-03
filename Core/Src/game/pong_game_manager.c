#include "game/pong_game_manager.h"
#include "stdlib.h"

void update(PongGameConfig *game);
void draw(PongGameConfig *game);

void game_init(PongGameConfig *game) {
    display_init(game->display);

    game->player = bar_create(0);
    game->enemy = bar_create(15);

    game->was_initialized = true;
}

void game_deinit(PongGameConfig *game) {
    free(game->player);
    free(game->enemy);
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
    bar_update(game->player);
    bar_update(game->enemy);
}

void draw(PongGameConfig *game) {
    display_clear(game->display);
    bar_draw(game->player,game->display);
    bar_draw(game->enemy, game->display);
    display_refresh(game->display);
}
