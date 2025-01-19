// battle_system.c
#include "battle_system.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Character* party = NULL;
static int partySize = 0;
static Character* enemies = NULL;
static int enemySize = 0;
static BattleState currentBattleState = BATTLE_STATE_ACTIVE;

// Initialize the battle system
void Battle_Init(Character* partyMembers, int sizeParty, Character* enemyMembers, int sizeEnemies) {
    party = partyMembers;
    partySize = sizeParty;
    enemies = enemyMembers;
    enemySize = sizeEnemies;
    currentBattleState = BATTLE_STATE_ACTIVE;

    printf("Battle initialized with %d party members and %d enemies.\n", partySize, enemySize);
}

// Start the battle
void Battle_Start() {
    printf("Battle started!\n");
}

// End the battle
void Battle_End() {
    printf("Battle ended!\n");
}

// Get the current battle state
BattleState Battle_GetState() {
    return currentBattleState;
}

// Character performs a basic attack
void Character_Attack(Character* attacker, Character* target) {
    if (!attacker || !target) return;

    int damage = 10; // Example base damage
    target->health -= damage;
    if (target->health <= 0) {
        target->health = 0;
        printf("%s defeated %s!\n", attacker->name, target->name);
    }
    else {
        printf("%s attacked %s for %d damage. %s has %d health left.\n",
            attacker->name, target->name, damage, target->name, target->health);
    }
}

// Character uses a skill
void Character_UseSkill(Character* user, Skill* skill, Character* targets[], int targetCount) {
    if (!user || !skill || !targets || targetCount <= 0) return;

    printf("%s used skill %s!\n", user->name, skill->name);
    for (int i = 0; i < targetCount; i++) {
        Character* target = targets[i];
        if (Skill_IsEffective(skill, target)) {
            int damage = skill->power;
            target->health -= damage;
            if (target->health <= 0) {
                target->health = 0;
                printf("%s defeated %s with %s!\n", user->name, target->name, skill->name);
            }
            else {
                printf("%s hit %s for %d damage with %s. %s has %d health left.\n",
                    user->name, target->name, damage, skill->name, target->name, target->health);
            }
        }
        else {
            printf("%s's skill %s was not effective against %s.\n", user->name, skill->name, target->name);
        }
    }
}

// Move a character to a new position
void Character_Move(Character* character, Vector3 newPosition) {
    if (!character) return;
    character->position = newPosition;
    printf("%s moved to position (%.2f, %.2f, %.2f).\n",
        character->name, newPosition.x, newPosition.y, newPosition.z);
}

// Toggle auto-battle mode for a character
void Character_SetAutoBattle(Character* character, bool autoBattle) {
    if (!character) return;
    character->isAutoBattle = autoBattle;
    printf("%s auto-battle mode %s.\n",
        character->name, autoBattle ? "enabled" : "disabled");
}

// Create a skill
Skill* Skill_Create(const char* name, int power, ElementType element, float range, bool isTeamSkill) {
    Skill* skill = (Skill*)malloc(sizeof(Skill));
    if (!skill) return NULL;

    skill->name = strdup(name);
    skill->power = power;
    skill->element = element;
    skill->range = range;
    skill->isTeamSkill = isTeamSkill;

    return skill;
}

// Destroy a skill
void Skill_Destroy(Skill* skill) {
    if (!skill) return;
    free((void*)skill->name);
    free(skill);
}

// Check if a skill is effective against a target
bool Skill_IsEffective(Skill* skill, Character* target) {
    if (!skill || !target) return false;

    // Example effectiveness logic
    if ((skill->element == ELEMENT_FIRE && target->element == ELEMENT_WIND) ||
        (skill->element == ELEMENT_WATER && target->element == ELEMENT_FIRE)) {
        return true;
    }
    return false;
}
