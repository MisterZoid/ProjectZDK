// stats_system.c
#include "stats_system.h"
#include <stdio.h>
#include <string.h>

// Initialize character stats
void Stats_Init(CharacterStats* stats, int level, Stats baseStats) {
    if (!stats) return;

    stats->level = (level > 0 && level <= MAX_LEVEL) ? level : 1;
    stats->baseStats = baseStats;
    stats->currentStats = baseStats;

    printf("Character stats initialized at level %d.\n", stats->level);
}

// Level up a character
void Stats_LevelUp(CharacterStats* stats) {
    if (!stats || stats->level >= MAX_LEVEL) return;

    stats->level++;

    // Increase base stats on level up (example scaling)
    stats->baseStats.hp += 10;
    stats->baseStats.sp += 5;
    stats->baseStats.atk += 2;
    stats->baseStats.def += 2;
    stats->baseStats.spd += 1;
    stats->baseStats.res += 2;
    stats->baseStats.intel += 3;
    stats->baseStats.luck += 1;

    // Ensure stats do not exceed the cap
    if (stats->baseStats.hp > MAX_STAT_VALUE) stats->baseStats.hp = MAX_STAT_VALUE;
    if (stats->baseStats.sp > MAX_STAT_VALUE) stats->baseStats.sp = MAX_STAT_VALUE;
    if (stats->baseStats.atk > MAX_STAT_VALUE) stats->baseStats.atk = MAX_STAT_VALUE;
    if (stats->baseStats.def > MAX_STAT_VALUE) stats->baseStats.def = MAX_STAT_VALUE;
    if (stats->baseStats.spd > MAX_STAT_VALUE) stats->baseStats.spd = MAX_STAT_VALUE;
    if (stats->baseStats.res > MAX_STAT_VALUE) stats->baseStats.res = MAX_STAT_VALUE;
    if (stats->baseStats.intel > MAX_STAT_VALUE) stats->baseStats.intel = MAX_STAT_VALUE;
    if (stats->baseStats.luck > MAX_STAT_VALUE) stats->baseStats.luck = MAX_STAT_VALUE;

    // Update current stats to match base stats (remove buffs/debuffs)
    stats->currentStats = stats->baseStats;

    printf("Character leveled up to level %d.\n", stats->level);
}

// Apply a temporary buff to a stat
void Stats_ApplyBuff(CharacterStats* stats, const char* statName, int value) {
    if (!stats || !statName) return;

    if (strcmp(statName, "hp") == 0) {
        stats->currentStats.hp += value;
        if (stats->currentStats.hp > stats->baseStats.hp) {
            stats->currentStats.hp = stats->baseStats.hp;
        }
    }
    else if (strcmp(statName, "sp") == 0) {
        stats->currentStats.sp += value;
        if (stats->currentStats.sp > stats->baseStats.sp) {
            stats->currentStats.sp = stats->baseStats.sp;
        }
    }
    else if (strcmp(statName, "atk") == 0) {
        stats->currentStats.atk += value;
    }
    else if (strcmp(statName, "def") == 0) {
        stats->currentStats.def += value;
    }
    else if (strcmp(statName, "spd") == 0) {
        stats->currentStats.spd += value;
    }
    else if (strcmp(statName, "res") == 0) {
        stats->currentStats.res += value;
    }
    else if (strcmp(statName, "intel") == 0) {
        stats->currentStats.intel += value;
    }
    else if (strcmp(statName, "luck") == 0) {
        stats->currentStats.luck += value;
    }

    printf("Buff applied to %s: %+d\n", statName, value);
}

// Apply a temporary debuff to a stat
void Stats_ApplyDebuff(CharacterStats* stats, const char* statName, int value) {
    if (!stats || !statName) return;

    if (strcmp(statName, "hp") == 0) {
        stats->currentStats.hp -= value;
        if (stats->currentStats.hp < 0) {
            stats->currentStats.hp = 0;
        }
    }
    else if (strcmp(statName, "sp") == 0) {
        stats->currentStats.sp -= value;
        if (stats->currentStats.sp < 0) {
            stats->currentStats.sp = 0;
        }
    }
    else if (strcmp(statName, "atk") == 0) {
        stats->currentStats.atk -= value;
    }
    else if (strcmp(statName, "def") == 0) {
        stats->currentStats.def -= value;
    }
    else if (strcmp(statName, "spd") == 0) {
        stats->currentStats.spd -= value;
    }
    else if (strcmp(statName, "res") == 0) {
        stats->currentStats.res -= value;
    }
    else if (strcmp(statName, "intel") == 0) {
        stats->currentStats.intel -= value;
    }
    else if (strcmp(statName, "luck") == 0) {
        stats->currentStats.luck -= value;
    }

    printf("Debuff applied to %s: %d\n", statName, value);
}

// Check if character is at max level
bool Stats_IsMaxLevel(CharacterStats* stats) {
    return stats && stats->level >= MAX_LEVEL;
}

// Check if a stat is maxed
bool Stats_IsStatMaxed(int stat) {
    return stat >= MAX_STAT_VALUE;
}

// Display character stats
void Stats_Display(const CharacterStats* stats) {
    if (!stats) return;

    printf("Level: %d\n", stats->level);
    printf("HP: %d / %d\n", stats->currentStats.hp, stats->baseStats.hp);
    printf("SP: %d / %d\n", stats->currentStats.sp, stats->baseStats.sp);
    printf("ATK: %d\n", stats->currentStats.atk);
    printf("DEF: %d\n", stats->currentStats.def);
    printf("SPD: %d\n", stats->currentStats.spd);
    printf("RES: %d\n", stats->currentStats.res);
    printf("INT: %d\n", stats->currentStats.intel);
    printf("LCK: %d\n", stats->currentStats.luck);
}
