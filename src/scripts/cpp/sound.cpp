#include "sound.hpp"

AudioSound::AudioSound(const char* path)
{
    SDL_Init(SDL_INIT_AUDIO);
    if(!SDL_LoadWAV(path, &wavSpec, &wavBuf, &wavLength))
    {
        SDL_Log("Error loading sound. Please, make sure you loaded sound correctly: %s", SDL_GetError());
        return;
    }
    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wavSpec, NULL, NULL);
    if(!stream)
    {
        SDL_Log("Cannot init audio stream: %s", SDL_GetError());
        return;
    }
    SDL_ResumeAudioStreamDevice(stream);

}
AudioSound::~AudioSound()
{
    if(stream) SDL_DestroyAudioStream(stream);
    if(wavBuf) SDL_free(wavBuf);
}

void AudioSound::Play()
{
    if(stream)
    {
        SDL_ClearAudioStream(stream);
        SDL_PutAudioStreamData(stream, wavBuf, wavLength);
    }
}
void AudioSound::Volume(float gain)
{
    if(stream)
    {
        SDL_SetAudioStreamGain(stream, gain);
    }
}