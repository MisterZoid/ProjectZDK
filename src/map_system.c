// map_system.c
#include "map_system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Map* activeMap = NULL;

// Initialize the map system
bool MapSystem_Init() {
    printf("Map system initialized.\n");
    return true;
}

// Shutdown the map system
void MapSystem_Shutdown() {
    if (activeMap) {
        Map_Unload(activeMap);
    }
    printf("Map system shut down.\n");
}

// Load a map
Map* Map_Load(const char* name, const char* modelPath) {
    if (!name || !modelPath) return NULL;

    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) return NULL;

    map->name = strdup(name);
    map->modelPath = strdup(modelPath);
    map->modelData = NULL; // Load actual model data here
    map->isLoaded = true;
    map->npcs = NULL;
    map->npcCount = 0;
    map->items = NULL;
    map->itemCount = 0;
    map->events = NULL;
    map->eventCount = 0;

    printf("Map '%s' loaded from '%s'.\n", name, modelPath);
    return map;
}

// Unload a map
void Map_Unload(Map* map) {
    if (!map) return;

    free((void*)map->name);
    free((void*)map->modelPath);

    // Unload assets
    for (int i = 0; i < map->npcCount; ++i) {
        AI_DestroyNPC(map->npcs[i]);
    }
    free(map->npcs);

    for (int i = 0; i < map->itemCount; ++i) {
        Item_Destroy(map->items[i]);
    }
    free(map->items);

    free(map->events); // Events should be dynamically allocated elsewhere

    free(map);
    printf("Map unloaded.\n");
}

// Render a map
void Map_Render(Map* map) {
    if (!map || !map->isLoaded) return;
    printf("Rendering map '%s'.\n", map->name);
    // Call renderer to render the model
}

// Set the active map
void Map_SetActive(Map* map) {
    if (activeMap) {
        Map_Unload(activeMap);
    }
    activeMap = map;
    printf("Active map set to '%s'.\n", map->name);
}

// Get the active map
Map* Map_GetActive() {
    return activeMap;
}

// Add an NPC to the map
bool Map_AddNPC(Map* map, NPC* npc) {
    if (!map || !npc) return false;

    map->npcs = (NPC**)realloc(map->npcs, sizeof(NPC*) * (map->npcCount + 1));
    map->npcs[map->npcCount++] = npc;
    printf("NPC '%s' added to map '%s'.\n", npc->name, map->name);
    return true;
}

// Add an item to the map
bool Map_AddItem(Map* map, Item* item) {
    if (!map || !item) return false;

    map->items = (Item**)realloc(map->items, sizeof(Item*) * (map->itemCount + 1));
    map->items[map->itemCount++] = item;
    printf("Item '%s' added to map '%s'.\n", item->name, map->name);
    return true;
}

// Add an event to the map
bool Map_AddEvent(Map* map, Event* event) {
    if (!map || !event) return false;

    map->events = (Event**)realloc(map->events, sizeof(Event*) * (map->eventCount + 1));
    map->events[map->eventCount++] = event;
    printf("Event added to map '%s'.\n", map->name);
    return true;
}

// Remove an NPC from the map
void Map_RemoveNPC(Map* map, NPC* npc) {
    if (!map || !npc) return;

    for (int i = 0; i < map->npcCount; ++i) {
        if (map->npcs[i] == npc) {
            map->npcs[i] = map->npcs[--map->npcCount];
            map->npcs = (NPC**)realloc(map->npcs, sizeof(NPC*) * map->npcCount);
            printf("NPC '%s' removed from map '%s'.\n", npc->name, map->name);
            return;
        }
    }
}

// Remove an item from the map
void Map_RemoveItem(Map* map, Item* item) {
    if (!map || !item) return;

    for (int i = 0; i < map->itemCount; ++i) {
        if (map->items[i] == item) {
            map->items[i] = map->items[--map->itemCount];
            map->items = (Item**)realloc(map->items, sizeof(Item*) * map->itemCount);
            printf("Item '%s' removed from map '%s'.\n", item->name, map->name);
            return;
        }
    }
}

// Remove an event from the map
void Map_RemoveEvent(Map* map, Event* event) {
    if (!map || !event) return;

    for (int i = 0; i < map->eventCount; ++i) {
        if (map->events[i] == event) {
            map->events[i] = map->events[--map->eventCount];
            map->events = (Event**)realloc(map->events, sizeof(Event*) * map->eventCount);
            printf("Event removed from map '%s'.\n", map->name);
            return;
        }
    }
}

// Debug render for SDK integration
void Map_DebugRender(Map* map) {
    if (!map) return;
    printf("Debug rendering map '%s'.\n", map->name);
    // Implement debug visualization here
}
