// dialogue.h
#ifndef DIALOGUE_H
#define DIALOGUE_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Dialogue System Initialization and Cleanup
EXPORT bool Dialogue_Init(SDL_Renderer* renderer, const char* fontPath, int fontSize);
EXPORT void Dialogue_Shutdown();

// Dialogue Display
EXPORT void Dialogue_Show(const char* text);
EXPORT void Dialogue_Update(float deltaTime);
EXPORT void Dialogue_Render();
EXPORT bool Dialogue_IsActive();

#endif // DIALOGUE_H

