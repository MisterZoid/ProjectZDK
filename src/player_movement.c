// player_movement.c
#include "player_movement.h"
#include <stdio.h>
#include <stdbool.h>

// Example collision detection function (stub)
bool CheckCollision(Vector3 newPosition) {
    // Placeholder logic: Replace with actual collision detection
    if (newPosition.x < 0 || newPosition.y < 0 || newPosition.z < 0) {
        printf("Collision detected at (%.2f, %.2f, %.2f)\n",
            newPosition.x, newPosition.y, newPosition.z);
        return true;
    }
    return false;
}

// Initialize the player
void Player_Init(Player* player) {
    if (!player) return;

    player->position = (Vector3){ 0.0f, 0.0f, 0.0f };
    player->direction = (Vector3){ 0.0f, 0.0f, 0.0f };
    player->speed = 0.0f;
    player->state = PLAYER_STATE_IDLE;

    printf("Player initialized at position (%.2f, %.2f, %.2f)\n",
        player->position.x, player->position.y, player->position.z);
}

// Set the player's movement state
void Player_SetState(Player* player, PlayerState state) {
    if (!player) return;

    player->state = state;

    switch (state) {
    case PLAYER_STATE_IDLE:
        player->speed = 0.0f;
        break;
    case PLAYER_STATE_WALKING:
        player->speed = 2.0f; // Example walking speed
        break;
    case PLAYER_STATE_RUNNING:
        player->speed = 5.0f; // Example running speed
        break;
    }

    printf("Player state set to %d with speed %.2f\n", state, player->speed);
}

// Move the player in a specified direction
void Player_Move(Player* player, Vector3 direction) {
    if (!player) return;

    player->direction = direction;
    player->direction = Vector3_Normalize(player->direction); // Ensure direction is normalized

    printf("Player moving in direction (%.2f, %.2f, %.2f)\n",
        player->direction.x, player->direction.y, player->direction.z);
}

// Update the player's position based on current state and direction
void Player_Update(Player* player) {
    if (!player) return;

    float deltaTime = Timer_GetDeltaTime();

    // Calculate new position based on speed and direction
    Vector3 displacement = Vector3_Scale(player->direction, player->speed * deltaTime);
    Vector3 newPosition = Vector3_Add(player->position, displacement);

    // Check for collisions before updating position
    if (!CheckCollision(newPosition)) {
        player->position = newPosition;
        printf("Player updated position to (%.2f, %.2f, %.2f)\n",
            player->position.x, player->position.y, player->position.z);
    }
    else {
        printf("Player position not updated due to collision.\n");
    }
}
