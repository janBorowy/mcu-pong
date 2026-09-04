#include "game/ball.h"
#include "game/bar.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define BALL_DIAMETER 32
#define REFLECTION_F_MAX 50.0

#define SIGN(x) (x >= 0 ? (1) : (-1))

float calculate_reflection_factor(uint16_t hit_point);

Ball *ball_create(int x, int y, int vx, int vy) {
    Ball *ball = malloc(sizeof(Ball));
    ball->x = x;
    ball->y = y;
    ball->vx = vx;
    ball->vy = vy;
    ball->enemy_scored = false;
    ball->player_scored = false;
    return ball;
}

void ball_update(Ball *ball, Bar *player, Bar *enemy) {
    ball->x += ball->vx;
    ball->y += ball->vy;
    
    if (ball->y >= GAME_WINDOW_HEIGHT) {
        ball->y = GAME_WINDOW_HEIGHT;
        ball->vy = -ball->vy;
    }

    if (ball->y < 0) {
        ball->y = 0;
        ball->vy = -ball->vy;
    }


    if (ball->x <= player->x && player->y < ball->y && ball->y - player->y < BAR_HEIGHT) {
        float rf = calculate_reflection_factor(ball->y - player->y);
        ball->x = player->x + PIXEL_HEIGHT_TIMES(1);
        uint8_t v = abs(ball->vx) + abs(ball->vy);
        ball->vx =((float)1 - fabs(rf)) * v;
        ball->vy = SIGN(rf) * (v - abs(ball->vx));
    }

    if (ball->x >= enemy->x && enemy->y < ball->y && abs(enemy->y - ball->y) < BAR_HEIGHT) {
        float rf = calculate_reflection_factor(ball->y - enemy->y);
        ball->x = enemy->x - PIXEL_HEIGHT_TIMES(1);
        uint8_t v = abs(ball->vx) + abs(ball->vy);
        ball->vx = -((float)1 - fabs(rf)) * v;
        ball->vy = SIGN(rf) * (v - abs(ball->vx));
    }

    if (ball->x < 0) {
        ball->enemy_scored = true;
    }
    if (ball->x > GAME_WINDOW_WIDTH) {
        ball->player_scored = true;
    }
}

void ball_draw(Ball *ball, GameWindow *window) {
    game_window_draw_pixel(window, ball->x + BALL_DIAMETER / 2, ball->y + BALL_DIAMETER / 2);
}

float calculate_reflection_factor(uint16_t hit_point) {
    return ((REFLECTION_F_MAX * (float) hit_point) / (BAR_HEIGHT / 2) - REFLECTION_F_MAX) / 100;
}