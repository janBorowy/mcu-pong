#include "game/enemy_controller.h"
#include "stdlib.h"

#define ENEMY_REACTION_TIME_FRAMES 6

EnemyController *enemy_controller_create(Bar *enemy_bar) {
    EnemyController *controller = malloc(sizeof(EnemyController));
    controller->bar = enemy_bar;
    controller->last_reaction_counter = 0;
    return controller;
}

void enemy_controller_update(EnemyController *controller, Ball *ball) {
    if (controller->last_reaction_counter >= ENEMY_REACTION_TIME_FRAMES) {
        controller->bar->moving_down = ball->y > controller->bar->y + BAR_HEIGHT / 2;
        controller->bar->moving_up = ball->y < controller->bar->y + BAR_HEIGHT / 2;
        controller->last_reaction_counter = 0;
    } else {
        controller->last_reaction_counter++;
    }
}