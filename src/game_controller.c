// game_controller.c
#include "game_controller.h"
#include <stdio.h>

#ifdef DREAMCAST
#include <dc/maple.h>
#include <dc/maple/controller.h>
#else
#include <SDL2/SDL.h>
#endif

static ControllerType currentControllerType;

// Initialize the controller
void Controller_Init(ControllerType type) {
    currentControllerType = type;

#ifdef DREAMCAST
    printf("Initializing Dreamcast controller...\n");
    maple_init();
#else
    if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) != 0) {
        printf("Failed to initialize SDL for controllers: %s\n", SDL_GetError());
    }
    else {
        printf("SDL controller support initialized.\n");
    }
#endif
}

// Shut down the controller
void Controller_Shutdown() {
#ifdef DREAMCAST
    // No specific shutdown needed for Dreamcast
#else
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
#endif
    printf("Controller shutdown complete.\n");
}

// Get the current controller type
ControllerType Controller_GetType() {
    return currentControllerType;
}

// Update the controller state
void Controller_Update(ControllerState* state) {
    if (!state) return;

#ifdef DREAMCAST
    maple_device_t* dev = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);
    if (dev) {
        cont_state_t* dcState = (cont_state_t*)maple_dev_status(dev);
        if (dcState) {
            state->up = !(dcState->buttons & CONT_DPAD_UP);
            state->down = !(dcState->buttons & CONT_DPAD_DOWN);
            state->left = !(dcState->buttons & CONT_DPAD_LEFT);
            state->right = !(dcState->buttons & CONT_DPAD_RIGHT);
            state->buttonA = !(dcState->buttons & CONT_A);
            state->buttonB = !(dcState->buttons & CONT_B);
            state->buttonX = !(dcState->buttons & CONT_X);
            state->buttonY = !(dcState->buttons & CONT_Y);
            state->start = !(dcState->buttons & CONT_START);
            state->analogX = dcState->joyx / 128.0f;
            state->analogY = dcState->joyy / 128.0f;
        }
    }
#else
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_CONTROLLERAXISMOTION) {
            if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                state->analogX = event.caxis.value / 32767.0f;
            }
            else if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY) {
                state->analogY = event.caxis.value / 32767.0f;
            }
        }
        else if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERBUTTONUP) {
            bool isPressed = (event.type == SDL_CONTROLLERBUTTONDOWN);
            switch (event.cbutton.button) {
            case SDL_CONTROLLER_BUTTON_A:
                state->buttonA = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_B:
                state->buttonB = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_X:
                state->buttonX = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_Y:
                state->buttonY = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                state->up = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                state->down = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                state->left = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                state->right = isPressed;
                break;
            case SDL_CONTROLLER_BUTTON_START:
                state->start = isPressed;
                break;
            }
        }
    }
#endif
}
