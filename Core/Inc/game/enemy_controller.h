#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include "game/bar.h"
#include "game/ball.h"

typedef struct {
    Bar *bar;
    uint16_t last_reaction_counter;
} EnemyController;

EnemyController *enemy_controller_create(Bar *enemy_bar);
void enemy_controller_update(EnemyController *controller, Ball *ball);

#endif