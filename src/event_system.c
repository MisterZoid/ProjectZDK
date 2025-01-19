// event_system.c
#include "event_system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_CALLBACKS 32

// Callback registration structure
typedef struct {
    EventType type;
    EventCallback callback;
} EventCallbackEntry;

static EventCallbackEntry gEventCallbacks[MAX_CALLBACKS];
static int gCallbackCount = 0;

// Initialize the event system
void EventSystem_Init() {
    gCallbackCount = 0;
    memset(gEventCallbacks, 0, sizeof(gEventCallbacks));
    printf("Event system initialized.\n");
}

// Shutdown the event system
void EventSystem_Shutdown() {
    gCallbackCount = 0;
    printf("Event system shut down.\n");
}

// Register a callback for a specific event type
bool EventSystem_RegisterCallback(EventType type, EventCallback callback) {
    if (gCallbackCount >= MAX_CALLBACKS) {
        printf("Error: Maximum number of event callbacks reached.\n");
        return false;
    }

    gEventCallbacks[gCallbackCount++] = (EventCallbackEntry){ type, callback };
    printf("Callback registered for event type %d.\n", type);
    return true;
}

// Unregister a callback for a specific event type
void EventSystem_UnregisterCallback(EventType type, EventCallback callback) {
    for (int i = 0; i < gCallbackCount; ++i) {
        if (gEventCallbacks[i].type == type && gEventCallbacks[i].callback == callback) {
            gEventCallbacks[i] = gEventCallbacks[--gCallbackCount];
            printf("Callback unregistered for event type %d.\n", type);
            return;
        }
    }
    printf("Warning: Callback not found for event type %d.\n", type);
}

// Trigger an event
void EventSystem_TriggerEvent(Event* event) {
    if (!event) return;

    printf("Event triggered: type %d.\n", event->type);
    for (int i = 0; i < gCallbackCount; ++i) {
        if (gEventCallbacks[i].type == event->type) {
            gEventCallbacks[i].callback(event);
        }
    }
}

// Utilities for creating events
Event Event_CreateDialogue(const char* dialogueText) {
    return (Event) {
        .type = EVENT_TYPE_DIALOGUE,
            .data.dialogueEvent = { .dialogueText = dialogueText }
    };
}

Event Event_CreateCutscene(const char* cutsceneName) {
    return (Event) {
        .type = EVENT_TYPE_CUTSCENE,
            .data.cutsceneEvent = { .cutsceneName = cutsceneName }
    };
}

Event Event_CreateItemGained(const char* itemName, int quantity) {
    return (Event) {
        .type = EVENT_TYPE_ITEM_GAINED,
            .data.itemGainedEvent = { .itemName = itemName, .quantity = quantity }
    };
}

Event Event_CreateBattleTriggered(const char* enemyGroupName) {
    return (Event) {
        .type = EVENT_TYPE_BATTLE_TRIGGERED,
            .data.battleTriggeredEvent = { .enemyGroupName = enemyGroupName }
    };
}

Event Event_CreateCustom(void* customData) {
    return (Event) {
        .type = EVENT_TYPE_CUSTOM,
            .data.customEvent = { .customData = customData }
    };
}
