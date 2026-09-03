
#include <stdint.h>
#include "driver/max7219.h"
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_gpio.h"

#define REG_SHUTDOWN 0x0C
#define REG_DISPLAY_TEST 0x0F
#define REG_INTENSITY 0x0A
#define REG_SCAN_LIMIT 0x0B
#define REG_DECODE_MODE 0x09

void set_register(const Max7219_Config *config, uint8_t address, uint8_t value);
void clear_display(const Max7219_Config *config);

void max7219_init(const Max7219_Config *config) {
    set_register(config, REG_DISPLAY_TEST, 0);
    set_register(config, REG_SHUTDOWN, 1);
    set_register(config, REG_INTENSITY, config->led_intensity);
    set_register(config, REG_SCAN_LIMIT, 0b111);
    set_register(config, REG_DECODE_MODE, 0);
    clear_display(config);
}

void max7219_set_column(const Max7219_Config *config, uint8_t col, uint8_t led_values) {
    if (col > 7) return;
    set_register(config, col + 1, led_values);
}

void max7219_test(const Max7219_Config *config) {
    set_register(config, REG_DISPLAY_TEST, 1);
}

void clear_display(const Max7219_Config *config) {
    for (uint8_t reg = 0x01; reg < 0x09; reg++) {
        set_register(config, reg, 0);
    }
}

void set_register(const Max7219_Config *config, uint8_t address, uint8_t value) {
    uint16_t payload = (((uint16_t) 0x0F & address) << 8) | value;
    HAL_StatusTypeDef status;
    HAL_GPIO_WritePin(config->gpio_port, config->gpio_pin, RESET);
    status = HAL_SPI_Transmit(config->hspi, (uint8_t *) &payload, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(config->gpio_port, config->gpio_pin, SET);
    return;
}
