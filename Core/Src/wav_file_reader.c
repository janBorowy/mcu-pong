#include "wav_file_reader.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

#define RIFF_ID 0x46464952
#define FILE_ID_FORMAT 0x45564157
#define BLOCK_ID 0x20746d66
#define WAV_FILE_BLOCK_ID 0x20746d66
#define DATA_BLOCK_ID 0x61746164

typedef struct {
    uint32_t block_id;
    uint32_t block_size;
    uint8_t *data;
} WavBlock;

uint16_t read_short(const uint8_t *data);
uint32_t read_int(const uint8_t *data);
_Bool check_equals(const uint8_t *data, uint32_t value);
void read_blocks(uint8_t *data, uint32_t data_size, WavBlock *blocks, uint8_t *blocks_num);

enum WavLoadStatus wav_load_file(WavFile *file, const uint8_t *binary_data) {
    if (!check_equals(binary_data, RIFF_ID)) {
        return RIFF_ID_ERROR;
    }

    file->file_size = read_int(binary_data + 4) + 8;

    if (!check_equals(binary_data + 8, FILE_ID_FORMAT)) {
        return FILE_ID_FORMAT_ERROR;
    }

    WavBlock blocks[16];
    uint8_t blocks_num;
    read_blocks(binary_data + 12, file->file_size - 12, blocks, &blocks_num);

    bool block_found = false;
    uint8_t wav_block_idx = 0;
    while (!block_found) {
        if (blocks[wav_block_idx].block_id == WAV_FILE_BLOCK_ID) {
            block_found = true;
            break;
        }
        wav_block_idx++;
    }

    if (!block_found) {
        return WAV_BLOCK_NOT_FOUND_ERROR;
    }

    block_found = false;
    uint8_t data_block_idx = 0;
    while (!block_found) {
        if (blocks[data_block_idx].block_id == DATA_BLOCK_ID) {
            block_found = true;
            break;
        }
        data_block_idx++;
    }

    uint8_t *wav_block_data = blocks[wav_block_idx].data;
    uint8_t *data_block_data = blocks[data_block_idx].data;

    uint16_t audio_format = read_short(wav_block_data);
    if (audio_format != 1) {
        return AUDIO_FORMAT_ERROR;
    }

    file->num_of_channels = read_short(wav_block_data + 2);
    file->frequency_hertz = read_int(wav_block_data + 4);
    file->bytes_per_second = read_int(wav_block_data + 8);
    file->bytes_per_block = read_short(wav_block_data + 12);
    file->bits_per_sample = read_short(wav_block_data + 14);

    file->sound_data_size = blocks[data_block_idx].block_size;
    file->sound_data = data_block_data;

    return WAV_SUCCESS;
}

uint16_t read_short(const uint8_t *data) {
    return data[0] + 16 * 16 * data[1];
}

uint32_t read_int(const uint8_t *data) {
    return data[0] + 16 * 16 * data[1]
    + data[2] * 16 * 16 * 16 * 16
    + data[3] * 16 * 16 * 16 * 16 * 16 * 16;
}

_Bool check_equals(const uint8_t *data, uint32_t value) {
    return read_int(data) == value;
}

void read_blocks(uint8_t *data, uint32_t data_size, WavBlock *blocks, uint8_t *blocks_num) {
    uint8_t *pos = data;
    uint8_t curr_block_idx = 0;
    uint32_t block_id, block_size;
    while ((pos - data) < data_size) {
        block_id = read_int(pos);
        block_size = read_int(pos + 4);

        blocks[curr_block_idx++] = (WavBlock) {
            .data = pos + 8,
            .block_id = block_id,
            .block_size = block_size
        };

        pos += block_size + 8;
    }
    *blocks_num = curr_block_idx;
}