#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include "game/bar.h"
#include "audio_player.h"

typedef struct {
    int x;
    int y;
    signed char vx;
    signed char vy;
    bool player_scored;
    bool enemy_scored;
} Ball;

Ball *ball_create(int x, int y, int vx, int vy);
void ball_update(Ball *ball, Bar *player, Bar *enemy, AudioPlayer *audio_player);
void ball_draw(Ball*, GameWindow *window);

#endif