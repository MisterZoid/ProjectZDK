// items.h
#ifndef ITEMS_H
#define ITEMS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>

// Item Rarity
typedef enum {
    ITEM_RARITY_COMMON,
    ITEM_RARITY_UNCOMMON,
    ITEM_RARITY_RARE,
    ITEM_RARITY_LEGENDARY,
    ITEM_RARITY_RELIC
} ItemRarity;

// Item Types
typedef enum {
    ITEM_TYPE_CONSUMABLE,
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_ARMOR,
    ITEM_TYPE_ACCESSORY
} ItemType;

// Item Structure
typedef struct {
    const char* name;        // Item name
    ItemType type;           // Type of the item
    ItemRarity rarity;       // Rarity of the item
    int value;               // Value in in-game currency
    const char* description; // Description of the item
    int effectPower;         // Power of the item's effect (if applicable)
    int durability;          // Durability for weapons/armor (if applicable)
} Item;

// Item Management
EXPORT Item* Item_Create(const char* name, ItemType type, ItemRarity rarity,
    int value, const char* description,
    int effectPower, int durability);
EXPORT void Item_Destroy(Item* item);
EXPORT bool Item_Register(Item* item);
EXPORT void Item_Unregister(Item* item);
EXPORT Item* Item_GetByName(const char* name);
EXPORT void Item_Display(const Item* item);

// Predefined Items
EXPORT void Items_AddStandardItems();

#endif // ITEMS_H

