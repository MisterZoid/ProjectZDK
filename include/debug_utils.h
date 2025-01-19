// debug_utils.h
#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include "math_utils.h" // For displaying position and transformation data

// Logging Functions
EXPORT void Log_Info(const char* message);
EXPORT void Log_Warning(const char* message);
EXPORT void Log_Error(const char* message);

// Debug Toggles
EXPORT void Debug_Enable();
EXPORT void Debug_Disable();
EXPORT bool Debug_IsEnabled();

// Display Functions
EXPORT void Debug_DisplayPosition(const char* label, Vector3 position);
EXPORT void Debug_DisplayMatrix(const char* label, Matrix4x4 matrix);
EXPORT void Debug_DisplayItem(const char* itemName, int itemID, int quantity);

// Test Functions
EXPORT void Debug_TestCode(const char* codeSnippet);
EXPORT void Debug_TestItemInteractions(int itemID);

#endif // DEBUG_UTILS_H

