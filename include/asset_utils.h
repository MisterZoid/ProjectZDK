// asset_utils.h
#ifndef ASSET_UTILS_H
#define ASSET_UTILS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>
#include "file_utils.h" // Utilize file utilities for asset management

// Texture Asset Structure
typedef struct {
    uint32_t id;           // Texture ID
    int width;             // Texture width
    int height;            // Texture height
    const char* filepath;  // Path to the texture file
} TextureAsset;

// Audio Asset Structure
typedef struct {
    uint32_t id;           // Audio ID
    float duration;        // Duration in seconds
    const char* filepath;  // Path to the audio file
} AudioAsset;

// Asset Management Functions
EXPORT TextureAsset* Asset_LoadTexture(const char* filepath);
EXPORT void Asset_UnloadTexture(TextureAsset* texture);

EXPORT AudioAsset* Asset_LoadAudio(const char* filepath);
EXPORT void Asset_UnloadAudio(AudioAsset* audio);

EXPORT bool Asset_IsLoaded(const char* filepath);
EXPORT void Asset_UnloadAll();

#endif // ASSET_UTILS_H

