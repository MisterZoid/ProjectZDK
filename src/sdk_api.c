// sdk_api.c
#include "sdk_api.h"
#include <stdio.h>
#include <stdbool.h> // Include stdbool.h for bool type

// Forward declarations of the initialization functions
bool Renderer_Init();
bool ShaderSystem_Init();
void Camera_Init(int width, int height); // Updated function signature
void MathUtils_Init();
void PhysicsSystem_Init();
bool BattleSystem_Init();
void StatsSystem_Init();
void Skills_Init();
bool CutsceneSystem_Init();
void Dialogue_Init();
void MapSystem_Init();
void AI_Init();
void EventSystem_Init();
bool SaveSystem_Init(int platform);
bool AudioSystem_Init();

// Forward declarations of the shutdown functions
void EventSystem_Shutdown();
void AI_Shutdown();
void MapSystem_Shutdown();
void Dialogue_Shutdown();
void CutsceneSystem_Shutdown();
void StatsSystem_Shutdown();
void BattleSystem_Shutdown();
void PhysicsSystem_Shutdown();
void ShaderSystem_Shutdown();
void Renderer_Shutdown();
void AudioSystem_Shutdown();
void SaveSystem_Shutdown();

// Forward declarations of the update functions
void Camera_Update(float deltaTime);
void PhysicsSystem_Update(float deltaTime);
void MapSystem_Update(float deltaTime);
void AI_Update(float deltaTime);
void Dialogue_Update(float deltaTime);
void CutsceneSystem_Update(float deltaTime);
void BattleSystem_Update(float deltaTime);
void AudioSystem_Update(float deltaTime);

// Initialize the SDK and its subsystems
bool SDK_Init() {
    printf("Initializing SDK...\n");

    // Initialize Core Systems
    if (!Renderer_Init()) {
        printf("Failed to initialize Renderer.\n");
        return false;
    }
    if (!ShaderSystem_Init()) {
        printf("Failed to initialize Shader System.\n");
        return false;
    }
    Camera_Init(1920, 1080); // Pass appropriate arguments
    MathUtils_Init();
    PhysicsSystem_Init();

    // Initialize Game Systems
    if (!BattleSystem_Init()) {
        printf("Failed to initialize Battle System.\n");
        return false;
    }
    StatsSystem_Init();
    Skills_Init();
    if (!CutsceneSystem_Init()) {
        printf("Failed to initialize Cutscene System.\n");
        return false;
    }
    Dialogue_Init();
    MapSystem_Init();
    AI_Init();
    EventSystem_Init();

    // Initialize Utilities
    if (!SaveSystem_Init(SAVE_PLATFORM_PC)) { // Default to PC
        printf("Failed to initialize Save System.\n");
        return false;
    }
    if (!AudioSystem_Init()) {
        printf("Failed to initialize Audio System.\n");
        return false;
    }

    printf("SDK initialized successfully.\n");
    return true;
}

// Shutdown the SDK and its subsystems
void SDK_Shutdown() {
    printf("Shutting down SDK...\n");

    // Shutdown Game Systems
    EventSystem_Shutdown();
    AI_Shutdown();
    MapSystem_Shutdown();
    Dialogue_Shutdown();
    CutsceneSystem_Shutdown();
    StatsSystem_Shutdown();
    BattleSystem_Shutdown();

    // Shutdown Core Systems
    PhysicsSystem_Shutdown();
    ShaderSystem_Shutdown();
    Renderer_Shutdown();

    // Shutdown Utilities
    AudioSystem_Shutdown();
    SaveSystem_Shutdown();

    printf("SDK shut down successfully.\n");
}

// Update the SDK subsystems
void SDK_Update(float deltaTime) {
    // Update subsystems
    Camera_Update(deltaTime);
    PhysicsSystem_Update(deltaTime);
    MapSystem_Update(deltaTime);
    AI_Update(deltaTime);
    Dialogue_Update(deltaTime);
    CutsceneSystem_Update(deltaTime);
    BattleSystem_Update(deltaTime);
    AudioSystem_Update(deltaTime);

    printf("SDK updated with deltaTime: %.2f\n", deltaTime);
}
