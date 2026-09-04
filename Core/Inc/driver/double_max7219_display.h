#ifndef DOUBLE_MAX7219_DISPLAY_H
#define DOUBLE_MAX7219_DISPLAY_H
#include "max7219.h"

#define DISPLAY_COLS 16
#define DISPLAY_ROWS 8

typedef struct {
    Max7219_Config left;
    Max7219_Config right;
    uint8_t display_data[DISPLAY_COLS];
} DoubleMax7219Config;

void display_init(DoubleMax7219Config *config);
void display_set(DoubleMax7219Config *config, uint8_t col, uint8_t row, _Bool is_on);
void display_clear(DoubleMax7219Config *config);
void display_refresh(DoubleMax7219Config *config);

#endif