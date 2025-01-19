// save_system.h
#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stddef.h>

// Save System Platforms
typedef enum {
    SAVE_PLATFORM_PC,
    SAVE_PLATFORM_DREAMCAST_VMU
} SavePlatform;

// Save File Structure
typedef struct {
    const char* fileName; // File name
    void* data;           // Save data
    size_t size;          // Size of save data
} SaveFile;

// Save System Management
EXPORT bool SaveSystem_Init(SavePlatform platform);
EXPORT void SaveSystem_Shutdown();

// Save File Management
EXPORT bool SaveFile_Create(const char* fileName, void* data, size_t size);
EXPORT SaveFile* SaveFile_Load(const char* fileName);
EXPORT bool SaveFile_Delete(const char* fileName);
EXPORT bool SaveFile_Copy(const char* sourceFileName, const char* destFileName);

// Platform-Specific Utilities
EXPORT bool SaveSystem_CheckSpace(size_t sizeNeeded);
EXPORT size_t SaveSystem_GetFreeSpace();

#endif // SAVE_SYSTEM_H

