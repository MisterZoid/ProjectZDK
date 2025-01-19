// skills.c
#include "skills.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_SKILLS 256

static Skill* skillRegistry[MAX_SKILLS];
static int skillCount = 0;

// Create a new skill
Skill* Skills_Create(const char* name, SkillType type, int power, ElementType element,
    float range, bool isAOE, const char* description) {
    Skill* skill = (Skill*)malloc(sizeof(Skill));
    if (!skill) return NULL;

    skill->name = strdup(name);
    skill->type = type;
    skill->power = power;
    skill->element = element;
    skill->range = range;
    skill->isAOE = isAOE;
    skill->description = strdup(description);
    skill->fusionIDs[0] = -1;
    skill->fusionIDs[1] = -1;

    return skill;
}

// Destroy a skill
void Skills_Destroy(Skill* skill) {
    if (!skill) return;

    free((void*)skill->name);
    free((void*)skill->description);
    free(skill);
}

// Register a skill
bool Skills_Register(Skill* skill) {
    if (!skill || skillCount >= MAX_SKILLS) return false;

    skillRegistry[skillCount++] = skill;
    printf("Registered skill: %s\n", skill->name);
    return true;
}

// Unregister a skill
void Skills_Unregister(Skill* skill) {
    if (!skill) return;

    for (int i = 0; i < skillCount; i++) {
        if (skillRegistry[i] == skill) {
            skillRegistry[i] = skillRegistry[--skillCount];
            printf("Unregistered skill: %s\n", skill->name);
            break;
        }
    }
}

// Get a skill by name
Skill* Skills_GetByName(const char* name) {
    for (int i = 0; i < skillCount; i++) {
        if (strcmp(skillRegistry[i]->name, name) == 0) {
            return skillRegistry[i];
        }
    }
    return NULL;
}

// Add predefined standard skills
void Skills_AddStandardSkills() {
    Skills_Register(Skills_Create("Fireball", SKILL_TYPE_ELEMENTAL, 50, ELEMENT_FIRE, 10.0f, false, "A basic fire attack."));
    Skills_Register(Skills_Create("Water Surge", SKILL_TYPE_ELEMENTAL, 45, ELEMENT_WATER, 10.0f, false, "A basic water attack."));
    Skills_Register(Skills_Create("Earthquake", SKILL_TYPE_ELEMENTAL, 60, ELEMENT_EARTH, 5.0f, true, "A powerful earth attack."));
    Skills_Register(Skills_Create("Wind Slash", SKILL_TYPE_ELEMENTAL, 40, ELEMENT_WIND, 10.0f, false, "A fast wind attack."));
    Skills_Register(Skills_Create("Holy Light", SKILL_TYPE_SPIRITUAL, 70, ELEMENT_LIGHT, 8.0f, false, "A light-based healing skill."));
    Skills_Register(Skills_Create("Shadow Strike", SKILL_TYPE_SPIRITUAL, 65, ELEMENT_DARK, 8.0f, false, "A dark stealth attack."));
}

// Add a fusion skill
void Skills_AddFusionSkill(const char* name, int skillID1, int skillID2) {
    if (skillID1 < 0 || skillID1 >= skillCount || skillID2 < 0 || skillID2 >= skillCount) return;

    Skill* skill = Skills_Create(name, SKILL_TYPE_FUSION, 100, ELEMENT_FIRE, 12.0f, true, "A powerful fusion skill.");
    skill->fusionIDs[0] = skillID1;
    skill->fusionIDs[1] = skillID2;
    Skills_Register(skill);

    printf("Added fusion skill: %s combining %s and %s\n", name,
        skillRegistry[skillID1]->name, skillRegistry[skillID2]->name);
}
