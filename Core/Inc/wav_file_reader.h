#ifndef WAV_FILE_READER_H
#define WAV_FILE_READER_H

#include "stm32f4xx.h"
#include <stdint.h>

enum WavLoadStatus {
    RIFF_ID_ERROR,
    FILE_ID_FORMAT_ERROR,
    WAV_BLOCK_NOT_FOUND_ERROR,
    AUDIO_FORMAT_ERROR,
    DATA_BLOCK_ID,
    WAV_SUCCESS
};

typedef struct {
    uint32_t file_size;
    uint8_t num_of_channels;
    uint32_t frequency_hertz;
    uint32_t bytes_per_second;
    uint16_t bytes_per_block;
    uint16_t bits_per_sample;
    uint32_t sound_data_size;
    uint8_t *sound_data;
} WavFile;

enum WavLoadStatus wav_load_file(WavFile *file, const uint8_t *binary_data);

#endif