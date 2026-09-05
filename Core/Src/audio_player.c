#include "audio_player.h"
#include "wav_file_reader.h"
#include "audio/start.wav.h"
#include "audio/pong.wav.h"
#include "audio/score.wav.h"
#include "audio/enemy_score.wav.h"
#include "i2s_interrupt_handler.h"
#include <string.h>

#define MIN(a, b) ((a < b) ? (a) : (b))

const uint8_t *get_data_by_sound_effect(enum SoundEffect effect);

void audio_player_init(AudioPlayer *player) {
    for (int i = 0; i < AUDIO_FILES_LEN; i++) {
        wav_load_file(player->files + i, get_data_by_sound_effect(i));
    }
}

void audio_player_play(AudioPlayer *player, enum SoundEffect sound_effect) {
    WavFile *file = player->files + sound_effect;
    uint16_t tmp_buff[AUDIO_BUFFER_SIZE];
    for (int i = 0; i < AUDIO_BUFFER_SIZE && i / 2 < file->sound_data_size; i += 2) {
        tmp_buff[i] = file->sound_data[i / 2];
        tmp_buff[i + 1] = file->sound_data[i / 2];
    }
    uint32_t init_slots = MIN(AUDIO_BUFFER_SIZE, 2 * file->sound_data_size);
    memcpy(audio_buffer, tmp_buff, init_slots * sizeof(uint16_t));

    audio_pos = MIN(AUDIO_BUFFER_SIZE / 2, file->sound_data_size);
    audio_data = file->sound_data;
    audio_data_len = file->sound_data_size;

    HAL_I2S_Transmit_DMA(player->hi2s, (uint16_t *) audio_buffer, AUDIO_BUFFER_SIZE);
}

const uint8_t *get_data_by_sound_effect(enum SoundEffect effect) {
    switch (effect) {
    case START:
        return start_wav;
    case PONG:
        return pong_wav;
    case SCORE:
        return score_wav;
    case ENEMY_SCORE:
        return enemy_score_wav;
    }
}