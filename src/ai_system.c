// ai_system.c
#include "ai_system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NPCS 256

static NPC* npcRegistry[MAX_NPCS];
static int npcCount = 0;

// Initialize the AI system
void AI_Init() {
    npcCount = 0;
    memset(npcRegistry, 0, sizeof(npcRegistry));
    printf("AI system initialized.\n");
}

// Shutdown the AI system
void AI_Shutdown() {
    for (int i = 0; i < npcCount; ++i) {
        AI_DestroyNPC(npcRegistry[i]);
    }
    npcCount = 0;
    printf("AI system shut down.\n");
}

// Create an NPC
NPC* AI_CreateNPC(const char* name, Vector3 position, NPCBehaviorType behavior) {
    if (npcCount >= MAX_NPCS) {
        printf("Error: Maximum NPC count reached.\n");
        return NULL;
    }

    NPC* npc = (NPC*)malloc(sizeof(NPC));
    if (!npc) return NULL;

    npc->name = strdup(name);
    npc->position = position;
    npc->targetPosition = position;
    npc->behavior = behavior;
    npc->speed = 1.0f; // Default speed
    npc->customBehavior = NULL;
    npc->shopInventory = NULL;
    npc->dialogue = NULL;

    npcRegistry[npcCount++] = npc;
    printf("NPC created: %s\n", name);
    return npc;
}

// Destroy an NPC
void AI_DestroyNPC(NPC* npc) {
    if (!npc) return;

    free((void*)npc->name);
    free((void*)npc->shopInventory);
    free((void*)npc->dialogue);
    free(npc);
}

// Set NPC behavior
void AI_SetBehavior(NPC* npc, NPCBehaviorType behavior, void (*customBehavior)(void* npc)) {
    if (!npc) return;

    npc->behavior = behavior;
    npc->customBehavior = customBehavior;
    printf("Behavior set for NPC: %s\n", npc->name);
}

// Update NPC
void AI_UpdateNPC(NPC* npc, float deltaTime) {
    if (!npc) return;

    switch (npc->behavior) {
    case NPC_BEHAVIOR_IDLE:
        // Do nothing
        break;

    case NPC_BEHAVIOR_WANDER:
        // Simple wandering logic
        if (Vector3_Distance(npc->position, npc->targetPosition) < 0.1f) {
            npc->targetPosition.x += (rand() % 3 - 1) * 5.0f;
            npc->targetPosition.z += (rand() % 3 - 1) * 5.0f;
        }
        npc->position = Vector3_Lerp(npc->position, npc->targetPosition, deltaTime * npc->speed);
        break;

    case NPC_BEHAVIOR_FOLLOW_PLAYER:
        // Example logic for following the player (stubbed out)
        printf("%s is following the player.\n", npc->name);
        break;

    case NPC_BEHAVIOR_GUARD:
        // Guard behavior can be implemented here
        printf("%s is guarding its position.\n", npc->name);
        break;

    case NPC_BEHAVIOR_SHOP:
        // Shop behavior
        printf("%s is ready to open the shop.\n", npc->name);
        break;

    case NPC_BEHAVIOR_CONVERSATION:
        // Conversation behavior
        printf("%s is ready for a conversation.\n", npc->name);
        break;

    case NPC_BEHAVIOR_CUSTOM:
        if (npc->customBehavior) {
            npc->customBehavior(npc);
        }
        break;
    }
}

// Update all NPCs
void AI_Update(float deltaTime) {
    for (int i = 0; i < npcCount; ++i) {
        AI_UpdateNPC(npcRegistry[i], deltaTime);
    }
}

// Start a conversation with an NPC
void AI_StartConversation(NPC* npc) {
    if (!npc || !npc->dialogue) return;

    printf("Conversation started with %s: %s\n", npc->name, npc->dialogue);
}

// Open a shop with an NPC
void AI_OpenShop(NPC* npc) {
    if (!npc || !npc->shopInventory) return;

    printf("Shop opened with %s. Inventory: %s\n", npc->name, npc->shopInventory);
}
