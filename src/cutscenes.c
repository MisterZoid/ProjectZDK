// cutscenes.c
#include "cutscenes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Create a new cutscene
Cutscene* Cutscene_Create(const char* name, CutsceneAction* actions, int actionCount) {
    Cutscene* cutscene = (Cutscene*)malloc(sizeof(Cutscene));
    if (!cutscene) return NULL;

    cutscene->name = strdup(name);
    cutscene->actions = (CutsceneAction*)malloc(sizeof(CutsceneAction) * actionCount);
    if (!cutscene->actions) {
        free((void*)cutscene->name);
        free(cutscene);
        return NULL;
    }

    memcpy(cutscene->actions, actions, sizeof(CutsceneAction) * actionCount);
    cutscene->actionCount = actionCount;
    cutscene->currentActionIndex = 0;
    cutscene->isRunning = false;

    return cutscene;
}

// Destroy a cutscene
void Cutscene_Destroy(Cutscene* cutscene) {
    if (!cutscene) return;

    free((void*)cutscene->name);
    free(cutscene->actions);
    free(cutscene);
}

// Start a cutscene
void Cutscene_Start(Cutscene* cutscene) {
    if (!cutscene) return;

    cutscene->isRunning = true;
    cutscene->currentActionIndex = 0;
    printf("Cutscene '%s' started.\n", cutscene->name);
}

// Update a cutscene
void Cutscene_Update(Cutscene* cutscene, float deltaTime) {
    if (!cutscene || !cutscene->isRunning || cutscene->currentActionIndex >= cutscene->actionCount) {
        cutscene->isRunning = false;
        return;
    }

    CutsceneAction* currentAction = &cutscene->actions[cutscene->currentActionIndex];

    switch (currentAction->type) {
    case CUTSCENE_ACTION_CAMERA_MOVE:
        Camera_MoveTo(currentAction->data.cameraMove.position, currentAction->data.cameraMove.duration);
        printf("Camera moving to (%.2f, %.2f, %.2f) over %.2f seconds.\n",
            currentAction->data.cameraMove.position.x,
            currentAction->data.cameraMove.position.y,
            currentAction->data.cameraMove.position.z,
            currentAction->data.cameraMove.duration);
        break;

    case CUTSCENE_ACTION_CAMERA_ZOOM:
        Camera_SetZoom(currentAction->data.cameraZoom.zoomLevel, currentAction->data.cameraZoom.duration);
        printf("Camera zooming to %.2f over %.2f seconds.\n",
            currentAction->data.cameraZoom.zoomLevel,
            currentAction->data.cameraZoom.duration);
        break;

    case CUTSCENE_ACTION_DIALOGUE:
        Dialogue_Show(currentAction->data.dialogue.text);
        printf("Displaying dialogue: '%s'\n", currentAction->data.dialogue.text);
        break;

    case CUTSCENE_ACTION_WAIT:
        printf("Waiting for %.2f seconds.\n", currentAction->data.wait.duration);
        break;
    }

    // Move to the next action
    cutscene->currentActionIndex++;
    if (cutscene->currentActionIndex >= cutscene->actionCount) {
        cutscene->isRunning = false;
        printf("Cutscene '%s' ended.\n", cutscene->name);
    }
}

// Check if a cutscene is running
bool Cutscene_IsRunning(Cutscene* cutscene) {
    return cutscene && cutscene->isRunning;
}

// Utility functions to create actions
CutsceneAction CutsceneAction_CreateCameraMove(Vector3 position, float duration) {
    CutsceneAction action = { .type = CUTSCENE_ACTION_CAMERA_MOVE };
    action.data.cameraMove.position = position;
    action.data.cameraMove.duration = duration;
    return action;
}

CutsceneAction CutsceneAction_CreateCameraZoom(float zoomLevel, float duration) {
    CutsceneAction action = { .type = CUTSCENE_ACTION_CAMERA_ZOOM };
    action.data.cameraZoom.zoomLevel = zoomLevel;
    action.data.cameraZoom.duration = duration;
    return action;
}

CutsceneAction CutsceneAction_CreateDialogue(const char* text) {
    CutsceneAction action = { .type = CUTSCENE_ACTION_DIALOGUE };
    action.data.dialogue.text = strdup(text);
    return action;
}

CutsceneAction CutsceneAction_CreateWait(float duration) {
    CutsceneAction action = { .type = CUTSCENE_ACTION_WAIT };
    action.data.wait.duration = duration;
    return action;
}
