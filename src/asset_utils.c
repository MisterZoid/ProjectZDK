// asset_utils.c
#include "asset_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DREAMCAST
#include <kos.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

// Asset Tracking
#define MAX_ASSETS 1024
static TextureAsset textureAssets[MAX_ASSETS];
static AudioAsset audioAssets[MAX_ASSETS];
static int textureCount = 0;
static int audioCount = 0;

// Helper Function: Find Asset
static bool FindAsset(const char* filepath) {
    for (int i = 0; i < textureCount; i++) {
        if (strcmp(textureAssets[i].filepath, filepath) == 0) {
            return true;
        }
    }
    for (int i = 0; i < audioCount; i++) {
        if (strcmp(audioAssets[i].filepath, filepath) == 0) {
            return true;
        }
    }
    return false;
}

// Texture Asset Management
TextureAsset* Asset_LoadTexture(const char* filepath) {
    if (FindAsset(filepath)) {
        printf("Texture already loaded: %s\n", filepath);
        return NULL;
    }

    if (textureCount >= MAX_ASSETS) {
        printf("Texture asset limit reached.\n");
        return NULL;
    }

    TextureAsset* texture = &textureAssets[textureCount++];
    texture->filepath = filepath;

#ifdef DREAMCAST
    // Load texture for Dreamcast
    pvr_ptr_t tex = pvr_mem_malloc(256 * 256 * 2); // Example allocation
    pvr_txr_load_kimg(tex, filepath);
    texture->id = (uint32_t)tex;
    texture->width = 256; // Example dimensions
    texture->height = 256;
#else
    // Load texture for SDL2
    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface) {
        printf("Failed to load texture: %s\n", filepath);
        return NULL;
    }
    texture->width = surface->w;
    texture->height = surface->h;
    texture->id = (uint32_t)surface; // Using surface as a stand-in for the ID
#endif

    return texture;
}

void Asset_UnloadTexture(TextureAsset* texture) {
    if (!texture || texture->id == 0) return;

#ifdef DREAMCAST
    // Unload Dreamcast texture
    pvr_mem_free((pvr_ptr_t)texture->id);
#else
    // Unload SDL2 texture
    SDL_FreeSurface((SDL_Surface*)texture->id);
#endif

    memset(texture, 0, sizeof(TextureAsset));
}

// Audio Asset Management
AudioAsset* Asset_LoadAudio(const char* filepath) {
    if (FindAsset(filepath)) {
        printf("Audio already loaded: %s\n", filepath);
        return NULL;
    }

    if (audioCount >= MAX_ASSETS) {
        printf("Audio asset limit reached.\n");
        return NULL;
    }

    AudioAsset* audio = &audioAssets[audioCount++];
    audio->filepath = filepath;

#ifdef DREAMCAST
    // Load audio for Dreamcast (placeholder)
    audio->id = 1; // Placeholder ID
    audio->duration = 0.0f; // Placeholder duration
#else
    // Load audio for SDL2
    Mix_Chunk* chunk = Mix_LoadWAV(filepath);
    if (!chunk) {
        printf("Failed to load audio: %s\n", filepath);
        return NULL;
    }
    audio->id = (uint32_t)chunk;
    audio->duration = 0.0f; // SDL2 does not provide duration directly
#endif

    return audio;
}

void Asset_UnloadAudio(AudioAsset* audio) {
    if (!audio || audio->id == 0) return;

#ifdef DREAMCAST
    // Unload Dreamcast audio (placeholder)
#else
    // Unload SDL2 audio
    Mix_FreeChunk((Mix_Chunk*)audio->id);
#endif

    memset(audio, 0, sizeof(AudioAsset));
}

// Asset Management
bool Asset_IsLoaded(const char* filepath) {
    return FindAsset(filepath);
}

void Asset_UnloadAll() {
    for (int i = 0; i < textureCount; i++) {
        Asset_UnloadTexture(&textureAssets[i]);
    }
    textureCount = 0;

    for (int i = 0; i < audioCount; i++) {
        Asset_UnloadAudio(&audioAssets[i]);
    }
    audioCount = 0;
}
