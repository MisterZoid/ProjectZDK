// battle_system.h
#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "math_utils.h" // For battlefield positioning
#include <stdbool.h>

// Elemental and Spiritual Types
typedef enum {
    ELEMENT_FIRE,
    ELEMENT_WATER,
    ELEMENT_EARTH,
    ELEMENT_WIND,
    ELEMENT_LIGHT,
    ELEMENT_DARK
} ElementType;

// Character Structure
typedef struct {
    const char* name;
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    ElementType element;
    Vector3 position; // Position on the battlefield
    bool isAutoBattle;
} Character;

// Skill Structure
typedef struct {
    const char* name;
    int power;
    ElementType element;
    float range;
    bool isTeamSkill;
} Skill;

// Battle State
typedef enum {
    BATTLE_STATE_ACTIVE,
    BATTLE_STATE_VICTORY,
    BATTLE_STATE_DEFEAT
} BattleState;

// Battle System Management
EXPORT void Battle_Init(Character* party, int partySize, Character* enemies, int enemySize);
EXPORT void Battle_Start();
EXPORT void Battle_End();
EXPORT BattleState Battle_GetState();

// Character Actions
EXPORT void Character_Attack(Character* attacker, Character* target);
EXPORT void Character_UseSkill(Character* user, Skill* skill, Character* targets[], int targetCount);
EXPORT void Character_Move(Character* character, Vector3 newPosition);
EXPORT void Character_SetAutoBattle(Character* character, bool autoBattle);

// Skill System
EXPORT Skill* Skill_Create(const char* name, int power, ElementType element, float range, bool isTeamSkill);
EXPORT void Skill_Destroy(Skill* skill);
EXPORT bool Skill_IsEffective(Skill* skill, Character* target);

#endif // BATTLE_SYSTEM_H

