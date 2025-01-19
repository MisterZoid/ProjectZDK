// player_movement.h
#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "math_utils.h" // For position and vector operations
#include "time_utils.h" // For delta time calculations

// Player Movement States
typedef enum {
    PLAYER_STATE_IDLE,
    PLAYER_STATE_WALKING,
    PLAYER_STATE_RUNNING
} PlayerState;

// Player Structure
typedef struct {
    Vector3 position;  // Player's current position
    Vector3 direction; // Direction of movement
    float speed;       // Current speed
    PlayerState state; // Current movement state
} Player;

// Initialization and State Management
EXPORT void Player_Init(Player* player);
EXPORT void Player_SetState(Player* player, PlayerState state);

// Movement Functions
EXPORT void Player_Move(Player* player, Vector3 direction);
EXPORT void Player_Update(Player* player);

#endif // PLAYER_MOVEMENT_H

