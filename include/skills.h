// skills.h
#ifndef SKILLS_H
#define SKILLS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "stats_system.h" // For character stats
#include "battle_system.h" // For skill targeting and effectiveness
#include <stdbool.h>
#include <stdint.h>

// Skill Types
typedef enum {
    SKILL_TYPE_ELEMENTAL,
    SKILL_TYPE_SPIRITUAL,
    SKILL_TYPE_FUSION
} SkillType;

// Skill Definition
typedef struct {
    const char* name;      // Skill name
    SkillType type;        // Skill type
    int power;             // Base power
    ElementType element;   // Associated element (if applicable)
    float range;           // Range of the skill
    bool isAOE;            // Is it an area-of-effect skill?
    const char* description; // Skill description for UI
    int fusionIDs[2];      // Skill IDs required for fusion (if applicable)
} Skill;

// Skill Management
EXPORT Skill* Skills_Create(const char* name, SkillType type, int power, ElementType element,
    float range, bool isAOE, const char* description);
EXPORT void Skills_Destroy(Skill* skill);
EXPORT Skill* Skills_GetByName(const char* name);
EXPORT bool Skills_Register(Skill* skill);
EXPORT void Skills_Unregister(Skill* skill);

// Predefined Skills
EXPORT void Skills_AddStandardSkills();
EXPORT void Skills_AddFusionSkill(const char* name, int skillID1, int skillID2);

#endif // SKILLS_H

