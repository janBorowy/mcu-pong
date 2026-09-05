#include "i2s_interrupt_handler.h"
#include "stm32f4xx.h"

uint16_t audio_buffer[AUDIO_BUFFER_SIZE];
uint8_t *audio_data;
uint32_t audio_data_len;
uint32_t audio_pos;

uint16_t rescale_signal(uint16_t signal_8_bit);

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
    if (audio_pos >= audio_data_len) {
        HAL_I2S_DMAStop(hi2s);
        return;
    }

    for (int i = 0; i < AUDIO_BUFFER_SIZE / 4 && audio_pos + i < audio_data_len; i++) {
        audio_buffer[i * 2] = rescale_signal(audio_data[audio_pos + i]);
        audio_buffer[i * 2 + 1] = rescale_signal(audio_data[audio_pos + i]);
    }
    audio_pos += AUDIO_BUFFER_SIZE / 4;
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s) {
    if (audio_pos >= audio_data_len) {
        HAL_I2S_DMAStop(hi2s);
        return;
    }

    for (int i = 0; i < AUDIO_BUFFER_SIZE / 4 && audio_pos + i < audio_data_len; i++) {
        audio_buffer[AUDIO_BUFFER_SIZE / 2 + i * 2] = rescale_signal(audio_data[audio_pos + i]);
        audio_buffer[AUDIO_BUFFER_SIZE / 2 + i * 2 + 1] = rescale_signal(audio_data[audio_pos + i]);
    }
    audio_pos += AUDIO_BUFFER_SIZE / 4;
}

uint16_t rescale_signal(uint16_t signal_8_bit) {
    return ((float)signal_8_bit / UINT8_MAX) * UINT16_MAX / 8;
}