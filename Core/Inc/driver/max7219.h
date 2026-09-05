#ifndef MAX7219_H
#define MAX7219_H

#include <stdint.h>
#include "stm32f4xx.h"
#include <stdbool.h>

typedef struct {
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;
    uint8_t led_intensity;
} Max7219_Config;

void max7219_init(const Max7219_Config *config);
void max7219_test(const Max7219_Config *config);
void max7219_set_column(const Max7219_Config *config, uint8_t col, uint8_t led_values);

#endif