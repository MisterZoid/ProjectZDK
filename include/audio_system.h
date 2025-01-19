// audio_system.h
#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stddef.h>

// Audio Types
typedef enum {
    AUDIO_TYPE_MUSIC,
    AUDIO_TYPE_SOUND_EFFECT
} AudioType;

// Audio File Structure
typedef struct {
    const char* fileName;  // Path to the audio file
    AudioType type;        // Type of audio
    void* data;            // Platform-specific audio data
} AudioFile;

// Audio System Management
EXPORT bool AudioSystem_Init();
EXPORT void AudioSystem_Shutdown();

// Audio Playback
EXPORT bool Audio_Play(const char* fileName, AudioType type, bool loop);
EXPORT void Audio_Stop(const char* fileName);
EXPORT void Audio_StopAll();

// Audio Utilities
EXPORT void Audio_SetVolume(const char* fileName, float volume);
EXPORT void Audio_SetGlobalVolume(float volume);
EXPORT bool Audio_IsPlaying(const char* fileName);

#endif // AUDIO_SYSTEM_H

