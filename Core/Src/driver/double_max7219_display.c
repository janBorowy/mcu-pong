#include "driver/double_max7219_display.h"
#include "string.h"

void display_init(DoubleMax7219Config *config) {
    max7219_init(&config->left);
    max7219_init(&config->right);
    memset(config->display_data, 0, DISPLAY_COLS);
    memset(config->display_data_updated, false, DISPLAY_COLS);
}

void display_set(DoubleMax7219Config *config, uint8_t col, uint8_t row, _Bool is_on) {
    if (col >= DISPLAY_COLS || row >= DISPLAY_ROWS) return;

    if (is_on) {
        config->display_data[col] |= (1 << row);
    } else {
        config->display_data[col] &= (0xFF - (1 << row));
    }

    config->display_data_updated[col] = true;
}

void display_clear(DoubleMax7219Config *config) {
    for (int i = 0; i < DISPLAY_COLS; i++) {
        config->display_data[i] = 0;
    }
}

void display_refresh(DoubleMax7219Config *config) {
    for (int i = 0; i < DISPLAY_COLS / 2; i++) {
        if (config->display_data_updated[i]) {
            max7219_set_column(&config->left, i, config->display_data[i]);
            config->display_data_updated[i] = false;
        }
    }
    for (int i = DISPLAY_COLS / 2; i < DISPLAY_COLS; i++) {
        if (config->display_data_updated[i]) {
            max7219_set_column(&config->right, i - DISPLAY_COLS / 2, config->display_data[i]);
            config->display_data_updated[i] = false;
        }
    }
}