// ai_system.h
#ifndef AI_SYSTEM_H
#define AI_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "math_utils.h" // For positions and movement
#include "battle_system.h" // For enemy AI in battle
#include <stdbool.h>

// NPC Behavior Types
typedef enum {
    NPC_BEHAVIOR_IDLE,
    NPC_BEHAVIOR_WANDER,
    NPC_BEHAVIOR_FOLLOW_PLAYER,
    NPC_BEHAVIOR_GUARD,
    NPC_BEHAVIOR_SHOP,
    NPC_BEHAVIOR_CONVERSATION,
    NPC_BEHAVIOR_CUSTOM
} NPCBehaviorType;

// NPC Structure
typedef struct {
    const char* name;         // NPC name
    Vector3 position;         // Current position
    Vector3 targetPosition;   // Target position for movement
    NPCBehaviorType behavior; // Current behavior
    float speed;              // Movement speed
    void (*customBehavior)(void* npc); // Custom behavior function
    const char* shopInventory; // Shop inventory data (if applicable)
    const char* dialogue;      // Dialogue data (if applicable)
} NPC;

// AI System Management
EXPORT void AI_Init();
EXPORT void AI_Shutdown();
EXPORT void AI_Update(float deltaTime);

// NPC Management
EXPORT NPC* AI_CreateNPC(const char* name, Vector3 position, NPCBehaviorType behavior);
EXPORT void AI_DestroyNPC(NPC* npc);
EXPORT void AI_SetBehavior(NPC* npc, NPCBehaviorType behavior, void (*customBehavior)(void* npc));
EXPORT void AI_UpdateNPC(NPC* npc, float deltaTime);

// NPC Interactions
EXPORT void AI_StartConversation(NPC* npc);
EXPORT void AI_OpenShop(NPC* npc);

#endif // AI_SYSTEM_H

