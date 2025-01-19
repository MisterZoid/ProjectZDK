// cutscenes.h
#ifndef CUTSCENES_H
#define CUTSCENES_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "camera.h" // For camera movement and effects
#include "dialogue.h" // For handling dialogue during cutscenes
#include "math_utils.h" // For positions and transformations
#include <stdbool.h>

// Cutscene Action Types
typedef enum {
    CUTSCENE_ACTION_CAMERA_MOVE,
    CUTSCENE_ACTION_CAMERA_ZOOM,
    CUTSCENE_ACTION_DIALOGUE,
    CUTSCENE_ACTION_WAIT
} CutsceneActionType;

// Cutscene Action
typedef struct {
    CutsceneActionType type;
    union {
        struct { Vector3 position; float duration; } cameraMove; // Camera movement
        struct { float zoomLevel; float duration; } cameraZoom;  // Camera zoom
        struct { const char* text; } dialogue;                  // Dialogue text
        struct { float duration; } wait;                       // Wait duration
    } data;
} CutsceneAction;

// Cutscene Structure
typedef struct {
    const char* name;         // Cutscene name
    CutsceneAction* actions;  // List of actions
    int actionCount;          // Number of actions
    int currentActionIndex;   // Current action being executed
    bool isRunning;           // Is the cutscene running
} Cutscene;

// Cutscene Management
EXPORT Cutscene* Cutscene_Create(const char* name, CutsceneAction* actions, int actionCount);
EXPORT void Cutscene_Destroy(Cutscene* cutscene);
EXPORT void Cutscene_Start(Cutscene* cutscene);
EXPORT void Cutscene_Update(Cutscene* cutscene, float deltaTime);
EXPORT bool Cutscene_IsRunning(Cutscene* cutscene);

// Utilities for SDK
EXPORT CutsceneAction CutsceneAction_CreateCameraMove(Vector3 position, float duration);
EXPORT CutsceneAction CutsceneAction_CreateCameraZoom(float zoomLevel, float duration);
EXPORT CutsceneAction CutsceneAction_CreateDialogue(const char* text);
EXPORT CutsceneAction CutsceneAction_CreateWait(float duration);

#endif // CUTSCENES_H

