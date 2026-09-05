#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include "stm32f4xx.h"
#include "wav_file_reader.h"

#define AUDIO_FILES_LEN 4

typedef struct {
    I2S_HandleTypeDef *hi2s;
    WavFile files[4];
} AudioPlayer;

enum SoundEffect {
    START = 0,
    PONG = 1,
    SCORE = 2,
    ENEMY_SCORE = 3
};

void audio_player_init(AudioPlayer *player);
void audio_player_play(AudioPlayer *player, enum SoundEffect sound_effect);

#endif