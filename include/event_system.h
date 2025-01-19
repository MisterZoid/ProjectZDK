// event_system.h
#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>

// Event Types
typedef enum {
    EVENT_TYPE_DIALOGUE,
    EVENT_TYPE_CUTSCENE,
    EVENT_TYPE_ITEM_GAINED,
    EVENT_TYPE_BATTLE_TRIGGERED,
    EVENT_TYPE_CUSTOM
} EventType;

// Event Data
typedef struct {
    EventType type;
    union {
        struct { const char* dialogueText; } dialogueEvent;
        struct { const char* cutsceneName; } cutsceneEvent;
        struct { const char* itemName; int quantity; } itemGainedEvent;
        struct { const char* enemyGroupName; } battleTriggeredEvent;
        struct { void* customData; } customEvent;
    } data;
} Event;

// Event Callback Function
typedef void (*EventCallback)(Event* event);

// Event System Management
EXPORT void EventSystem_Init();
EXPORT void EventSystem_Shutdown();
EXPORT bool EventSystem_RegisterCallback(EventType type, EventCallback callback);
EXPORT void EventSystem_UnregisterCallback(EventType type, EventCallback callback);
EXPORT void EventSystem_TriggerEvent(Event* event);

// Utilities for SDK
EXPORT Event Event_CreateDialogue(const char* dialogueText);
EXPORT Event Event_CreateCutscene(const char* cutsceneName);
EXPORT Event Event_CreateItemGained(const char* itemName, int quantity);
EXPORT Event Event_CreateBattleTriggered(const char* enemyGroupName);
EXPORT Event Event_CreateCustom(void* customData);

#endif // EVENT_SYSTEM_H

