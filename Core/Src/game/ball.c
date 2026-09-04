#include "game/ball.h"
#include "game/bar.h"
#include "stm32f4xx_hal_uart.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define REFLECTION_F_MAX 50.0

#define SIGN(x) (x >= 0 ? (1) : (-1))

bool check_paddle_vertical_collision(uint16_t ball_y, uint16_t paddle_y);
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

extern UART_HandleTypeDef huart2;
#include "stdio.h"
#include "string.h"
void ball_update(Ball *ball, Bar *player, Bar *enemy) {
    ball->x += ball->vx;
    ball->y += ball->vy;

    char msg[50];
    sprintf(msg, "Ball speed: %d\r\n", abs(ball->vx) + abs(ball->vy));
    HAL_UART_Transmit(&huart2, msg, strlen(msg), HAL_MAX_DELAY);
    
    if (ball->y >= GAME_WINDOW_HEIGHT) {
        ball->y = GAME_WINDOW_HEIGHT;
        ball->vy = -ball->vy;
    }

    if (ball->y < 0) {
        ball->y = 0;
        ball->vy = -ball->vy;
    }


    if (ball->x <= player->x && check_paddle_vertical_collision(ball->y, player->y)) {
        float rf = calculate_reflection_factor(ball->y - player->y);
        ball->x = player->x + PIXEL_HEIGHT_TIMES(1);
        uint8_t v = abs(ball->vx) + abs(ball->vy);
        ball->vx =((float)1 - fabs(rf)) * v;
        ball->vy = SIGN(rf) * (v - abs(ball->vx));
    }

    if (ball->x >= enemy->x && check_paddle_vertical_collision(ball->y, enemy->y)) {
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
    game_window_draw_pixel(window, ball->x, ball->y);
}

float calculate_reflection_factor(uint16_t hit_point) {
    return ((REFLECTION_F_MAX * (float) hit_point) / (BAR_HEIGHT / 2) - REFLECTION_F_MAX) / 100;
}

bool check_paddle_vertical_collision(uint16_t ball_y, uint16_t paddle_y) {
    uint16_t upper_square_start = (paddle_y / 32) * 32;
    uint16_t lower_square_end = ((paddle_y + BAR_HEIGHT) / 32) * 32;
    return upper_square_start <= ball_y && ball_y >= upper_square_start && ball_y <= lower_square_end;
}