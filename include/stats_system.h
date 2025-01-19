// stats_system.h
#ifndef STATS_SYSTEM_H
#define STATS_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stdint.h>

// Stat Parameters
typedef struct {
    int hp;     // Health Points
    int sp;     // Skill Points
    int atk;    // Attack
    int def;    // Defense
    int spd;    // Speed
    int res;    // Resistance
    int intel;  // Intelligence
    int luck;   // Luck
} Stats;

// Character Level and Stats
typedef struct {
    int level;      // Character level (1-99)
    Stats baseStats; // Base stats of the character
    Stats currentStats; // Current stats (can be buffed or debuffed)
} CharacterStats;

// Constants
#define MAX_LEVEL 99
#define MAX_STAT_VALUE 99999

// Initialization
EXPORT void Stats_Init(CharacterStats* stats, int level, Stats baseStats);

// Level Up
EXPORT void Stats_LevelUp(CharacterStats* stats);

// Utility Functions
EXPORT bool Stats_IsMaxLevel(CharacterStats* stats);
EXPORT bool Stats_IsStatMaxed(int stat);
EXPORT void Stats_Display(const CharacterStats* stats);

#endif // STATS_SYSTEM_H

