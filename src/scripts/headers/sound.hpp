#pragma once
#include <SDL3/SDL.h>

struct AudioSound
{
    // "wav" actually means .wav format
    SDL_AudioSpec wavSpec;
    Uint8* wavBuf;
    Uint32 wavLength = 0;
    SDL_AudioStream* stream;

    AudioSound(const char* path);
    ~AudioSound();
    void Play();
    void Volume(float gain);
};