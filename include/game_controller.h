// game_controller.h
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>

// Supported Controller Types
typedef enum {
    CONTROLLER_TYPE_DREAMCAST,
    CONTROLLER_TYPE_KEYBOARD_MOUSE,
    CONTROLLER_TYPE_XBOX,
    CONTROLLER_TYPE_PLAYSTATION
} ControllerType;

// Controller State
typedef struct {
    bool up;
    bool down;
    bool left;
    bool right;
    bool buttonA;
    bool buttonB;
    bool buttonX;
    bool buttonY;
    bool start;
    float analogX; // -1.0 (left) to 1.0 (right)
    float analogY; // -1.0 (down) to 1.0 (up)
} ControllerState;

// Controller Management Functions
EXPORT void Controller_Init(ControllerType type);
EXPORT void Controller_Shutdown();
EXPORT void Controller_Update(ControllerState* state);
EXPORT ControllerType Controller_GetType();

#endif // GAME_CONTROLLER_H

