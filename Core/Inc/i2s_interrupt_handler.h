#ifndef I2S_INTERRUPT_HANDLER
#define I2S_INTERRUPT_HANDLER

#include <stdint.h>

#define AUDIO_BUFFER_SIZE 1028
extern uint16_t audio_buffer[AUDIO_BUFFER_SIZE];
extern uint8_t *audio_data;
extern uint32_t audio_data_len;
extern uint32_t audio_pos;

void set_current_playback(uint8_t *data);

#endif