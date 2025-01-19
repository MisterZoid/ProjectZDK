// map_system.h
#ifndef MAP_SYSTEM_H
#define MAP_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "renderer.h" // For rendering 3D models
#include "camera.h"   // For viewing and navigation
#include "ai_system.h" // For NPC management
#include "items.h"    // For item placement
#include "event_system.h" // For event triggers
#include <stdbool.h>

// Map Structure
typedef struct {
    const char* name;          // Name of the map
    const char* modelPath;     // Path to the 3D model file
    void* modelData;           // Loaded 3D model data (platform-specific)
    bool isLoaded;             // Is the map currently loaded?

    NPC** npcs;                // List of NPCs on the map
    int npcCount;              // Number of NPCs

    Item** items;              // List of items on the map
    int itemCount;             // Number of items

    Event** events;            // List of events on the map
    int eventCount;            // Number of events
} Map;

// Map System Management
EXPORT bool MapSystem_Init();
EXPORT void MapSystem_Shutdown();

// Map Management
EXPORT Map* Map_Load(const char* name, const char* modelPath);
EXPORT void Map_Unload(Map* map);
EXPORT void Map_Render(Map* map);
EXPORT void Map_SetActive(Map* map);
EXPORT Map* Map_GetActive();

// Asset Management on Maps
EXPORT bool Map_AddNPC(Map* map, NPC* npc);
EXPORT bool Map_AddItem(Map* map, Item* item);
EXPORT bool Map_AddEvent(Map* map, Event* event);
EXPORT void Map_RemoveNPC(Map* map, NPC* npc);
EXPORT void Map_RemoveItem(Map* map, Item* item);
EXPORT void Map_RemoveEvent(Map* map, Event* event);

// Utilities for SDK
EXPORT const char* Map_GetName(Map* map);
EXPORT bool Map_IsLoaded(Map* map);
EXPORT void Map_DebugRender(Map* map);

#endif // MAP_SYSTEM_H

