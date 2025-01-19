// dialogue.c
#include "dialogue.h"
#include <string.h>
#include <stdlib.h>

// SDL and font variables
static SDL_Renderer* gRenderer = NULL;
static TTF_Font* gFont = NULL;

// Dialogue state
static char* gCurrentText = NULL;
static bool gIsActive = false;
static SDL_Rect gDialogueBox = { 0, 0, 0, 0 };

// Initialize the dialogue system
bool Dialogue_Init(SDL_Renderer* renderer, const char* fontPath, int fontSize) {
    if (!renderer || !fontPath) return false;

    gRenderer = renderer;

    if (TTF_Init() == -1) {
        printf("Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        return false;
    }

    gFont = TTF_OpenFont(fontPath, fontSize);
    if (!gFont) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return false;
    }

    // Set up dialogue box dimensions (example)
    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
    gDialogueBox.x = 50;
    gDialogueBox.y = screenHeight - 150;
    gDialogueBox.w = screenWidth - 100;
    gDialogueBox.h = 100;

    return true;
}

// Shut down the dialogue system
void Dialogue_Shutdown() {
    if (gFont) {
        TTF_CloseFont(gFont);
        gFont = NULL;
    }
    TTF_Quit();

    if (gCurrentText) {
        free(gCurrentText);
        gCurrentText = NULL;
    }

    gRenderer = NULL;
}

// Show a dialogue
void Dialogue_Show(const char* text) {
    if (!text || !gRenderer || !gFont) return;

    if (gCurrentText) {
        free(gCurrentText);
    }

    gCurrentText = strdup(text);
    gIsActive = true;

    printf("Dialogue shown: %s\n", gCurrentText);
}

// Update dialogue state
void Dialogue_Update(float deltaTime) {
    // Placeholder: Add logic for text scrolling or timed updates
    if (!gIsActive) return;
}

// Render the dialogue box
void Dialogue_Render() {
    if (!gIsActive || !gRenderer || !gFont || !gCurrentText) return;

    // Draw the dialogue box background
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 128, 200); // Blue gradient
    SDL_RenderFillRect(gRenderer, &gDialogueBox);

    // Draw the border
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); // White border
    SDL_RenderDrawRect(gRenderer, &gDialogueBox);

    // Render the text
    SDL_Color textColor = { 255, 255, 255, 255 }; // White text
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(gFont, gCurrentText, textColor, gDialogueBox.w - 20);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (textTexture) {
            SDL_Rect textRect = { gDialogueBox.x + 10, gDialogueBox.y + 10, textSurface->w, textSurface->h };
            SDL_RenderCopy(gRenderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

// Check if a dialogue is active
bool Dialogue_IsActive() {
    return gIsActive;
}
