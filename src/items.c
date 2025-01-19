// items.c
#include "items.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_ITEMS 256

static Item* itemRegistry[MAX_ITEMS];
static int itemCount = 0;

// Create a new item
Item* Item_Create(const char* name, ItemType type, ItemRarity rarity,
    int value, const char* description, int effectPower, int durability) {
    Item* item = (Item*)malloc(sizeof(Item));
    if (!item) return NULL;

    item->name = strdup(name);
    item->type = type;
    item->rarity = rarity;
    item->value = value;
    item->description = strdup(description);
    item->effectPower = effectPower;
    item->durability = durability;

    return item;
}

// Destroy an item
void Item_Destroy(Item* item) {
    if (!item) return;

    free((void*)item->name);
    free((void*)item->description);
    free(item);
}

// Register an item
bool Item_Register(Item* item) {
    if (!item || itemCount >= MAX_ITEMS) return false;

    itemRegistry[itemCount++] = item;
    printf("Registered item: %s\n", item->name);
    return true;
}

// Unregister an item
void Item_Unregister(Item* item) {
    if (!item) return;

    for (int i = 0; i < itemCount; i++) {
        if (itemRegistry[i] == item) {
            itemRegistry[i] = itemRegistry[--itemCount];
            printf("Unregistered item: %s\n", item->name);
            break;
        }
    }
}

// Get an item by name
Item* Item_GetByName(const char* name) {
    for (int i = 0; i < itemCount; i++) {
        if (strcmp(itemRegistry[i]->name, name) == 0) {
            return itemRegistry[i];
        }
    }
    return NULL;
}

// Display an item's information
void Item_Display(const Item* item) {
    if (!item) return;

    const char* rarityNames[] = { "Common", "Uncommon", "Rare", "Legendary", "Relic" };
    const char* typeNames[] = { "Consumable", "Weapon", "Armor", "Accessory" };

    printf("Name: %s\n", item->name);
    printf("Type: %s\n", typeNames[item->type]);
    printf("Rarity: %s\n", rarityNames[item->rarity]);
    printf("Value: %d\n", item->value);
    printf("Description: %s\n", item->description);
    if (item->effectPower > 0) {
        printf("Effect Power: %d\n", item->effectPower);
    }
    if (item->durability > 0) {
        printf("Durability: %d\n", item->durability);
    }
}

// Add predefined items
void Items_AddStandardItems() {
    Item_Register(Item_Create("Potion", ITEM_TYPE_CONSUMABLE, ITEM_RARITY_COMMON, 50, "Restores 50 HP.", 50, 0));
    Item_Register(Item_Create("Hi-Potion", ITEM_TYPE_CONSUMABLE, ITEM_RARITY_UNCOMMON, 200, "Restores 200 HP.", 200, 0));
    Item_Register(Item_Create("Iron Sword", ITEM_TYPE_WEAPON, ITEM_RARITY_COMMON, 300, "A basic iron sword.", 25, 100));
    Item_Register(Item_Create("Steel Armor", ITEM_TYPE_ARMOR, ITEM_RARITY_UNCOMMON, 500, "Provides decent protection.", 0, 200));
    Item_Register(Item_Create("Amulet of Luck", ITEM_TYPE_ACCESSORY, ITEM_RARITY_RARE, 1000, "Increases luck by 10.", 10, 0));
    Item_Register(Item_Create("Phoenix Feather", ITEM_TYPE_CONSUMABLE, ITEM_RARITY_LEGENDARY, 5000, "Revives a fallen ally.", 0, 0));
    Item_Register(Item_Create("Excalibur", ITEM_TYPE_WEAPON, ITEM_RARITY_RELIC, 10000, "A legendary sword of great power.", 100, 500));
}
