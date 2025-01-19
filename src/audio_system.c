// audio_system.c
#include "audio_system.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

#define MAX_AUDIO_FILES 256

typedef struct {
    const char* fileName;
    AudioType type;
    Mix_Chunk* soundEffect;
    Mix_Music* music;
    bool isPlaying;
} LoadedAudio;

static LoadedAudio audioFiles[MAX_AUDIO_FILES];
static int audioFileCount = 0;
static float globalVolume = 1.0f;

// Initialize the audio system
bool AudioSystem_Init() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        printf("Failed to initialize SDL audio: %s\n", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        return false;
    }

    memset(audioFiles, 0, sizeof(audioFiles));
    printf("Audio system initialized.\n");
    return true;
}

// Shutdown the audio system
void AudioSystem_Shutdown() {
    for (int i = 0; i < audioFileCount; ++i) {
        if (audioFiles[i].music) {
            Mix_FreeMusic(audioFiles[i].music);
        }
        if (audioFiles[i].soundEffect) {
            Mix_FreeChunk(audioFiles[i].soundEffect);
        }
    }
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    printf("Audio system shut down.\n");
}

// Load an audio file
static LoadedAudio* LoadAudioFile(const char* fileName, AudioType type) {
    if (audioFileCount >= MAX_AUDIO_FILES) {
        printf("Error: Maximum number of audio files reached.\n");
        return NULL;
    }

    for (int i = 0; i < audioFileCount; ++i) {
        if (strcmp(audioFiles[i].fileName, fileName) == 0) {
            return &audioFiles[i];
        }
    }

    LoadedAudio* audio = &audioFiles[audioFileCount++];
    audio->fileName = strdup(fileName);
    audio->type = type;
    audio->isPlaying = false;

    if (type == AUDIO_TYPE_MUSIC) {
        audio->music = Mix_LoadMUS(fileName);
        if (!audio->music) {
            printf("Failed to load music: %s\n", Mix_GetError());
            return NULL;
        }
    }
    else if (type == AUDIO_TYPE_SOUND_EFFECT) {
        audio->soundEffect = Mix_LoadWAV(fileName);
        if (!audio->soundEffect) {
            printf("Failed to load sound effect: %s\n", Mix_GetError());
            return NULL;
        }
    }

    return audio;
}

// Play an audio file
bool Audio_Play(const char* fileName, AudioType type, bool loop) {
    LoadedAudio* audio = LoadAudioFile(fileName, type);
    if (!audio) return false;

    if (type == AUDIO_TYPE_MUSIC) {
        if (Mix_PlayMusic(audio->music, loop ? -1 : 1) == -1) {
            printf("Failed to play music: %s\n", Mix_GetError());
            return false;
        }
    }
    else if (type == AUDIO_TYPE_SOUND_EFFECT) {
        if (Mix_PlayChannel(-1, audio->soundEffect, loop ? -1 : 0) == -1) {
            printf("Failed to play sound effect: %s\n", Mix_GetError());
            return false;
        }
    }

    audio->isPlaying = true;
    return true;
}

// Stop an audio file
void Audio_Stop(const char* fileName) {
    for (int i = 0; i < audioFileCount; ++i) {
        if (strcmp(audioFiles[i].fileName, fileName) == 0) {
            if (audioFiles[i].type == AUDIO_TYPE_MUSIC) {
                Mix_HaltMusic();
            }
            else if (audioFiles[i].type == AUDIO_TYPE_SOUND_EFFECT) {
                Mix_HaltChannel(-1);
            }
            audioFiles[i].isPlaying = false;
            printf("Audio stopped: %s\n", fileName);
            return;
        }
    }
    printf("Audio not found: %s\n", fileName);
}

// Stop all audio
void Audio_StopAll() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    for (int i = 0; i < audioFileCount; ++i) {
        audioFiles[i].isPlaying = false;
    }
    printf("All audio stopped.\n");
}

// Set volume for a specific audio file
void Audio_SetVolume(const char* fileName, float volume) {
    for (int i = 0; i < audioFileCount; ++i) {
        if (strcmp(audioFiles[i].fileName, fileName) == 0) {
            int sdlVolume = (int)(volume * MIX_MAX_VOLUME);
            if (audioFiles[i].type == AUDIO_TYPE_MUSIC) {
                Mix_VolumeMusic(sdlVolume);
            }
            else if (audioFiles[i].type == AUDIO_TYPE_SOUND_EFFECT) {
                Mix_VolumeChunk(audioFiles[i].soundEffect, sdlVolume);
            }
            printf("Volume set for %s: %.2f\n", fileName, volume);
            return;
        }
    }
    printf("Audio not found: %s\n", fileName);
}

// Set global volume
void Audio_SetGlobalVolume(float volume) {
    globalVolume = volume;
    int sdlVolume = (int)(volume * MIX_MAX_VOLUME);
    Mix_Volume(-1, sdlVolume);
    Mix_VolumeMusic(sdlVolume);
    printf("Global volume set: %.2f\n", volume);
}

// Check if an audio file is playing
bool Audio_IsPlaying(const char* fileName) {
    for (int i = 0; i < audioFileCount; ++i) {
        if (strcmp(audioFiles[i].fileName, fileName) == 0) {
            return audioFiles[i].isPlaying;
        }
    }
    return false;
}
