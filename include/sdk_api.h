// sdk_api.h
#ifndef SDK_API_H
#define SDK_API_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

// Core Headers
#include "renderer.h"
#include "camera.h"
#include "math_utils.h"
#include "physics_system.h"
#include "shader_system.h"

// Game Systems
#include "battle_system.h"
#include "stats_system.h"
#include "items.h"
#include "skills.h"
#include "cutscenes.h"
#include "dialogue.h"
#include "map_system.h"
#include "ai_system.h"
#include "event_system.h"
#include "save_system.h"
#include "audio_system.h"

// SDK API Management
EXPORT bool SDK_Init();
EXPORT void SDK_Shutdown();
EXPORT void SDK_Update(float deltaTime);

#endif // SDK_API_H

