// save_system.c
#include "save_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // For PC-specific file operations
#else
#include <dc/vmu.h>  // For Dreamcast VMU operations
#endif

static SavePlatform currentPlatform;

// Initialize the save system
bool SaveSystem_Init(SavePlatform platform) {
    currentPlatform = platform;
    printf("Save system initialized for platform: %s\n",
        platform == SAVE_PLATFORM_PC ? "PC" : "Dreamcast VMU");
    return true;
}

// Shutdown the save system
void SaveSystem_Shutdown() {
    printf("Save system shut down.\n");
}

// Create a save file
bool SaveFile_Create(const char* fileName, void* data, size_t size) {
    if (!fileName || !data || size == 0) return false;

#ifdef _WIN32
    FILE* file = fopen(fileName, "wb");
    if (!file) {
        printf("Failed to create save file: %s\n", fileName);
        return false;
    }
    fwrite(data, 1, size, file);
    fclose(file);
    printf("Save file created: %s\n", fileName);
#else
    // Dreamcast VMU save (example stub)
    printf("VMU save functionality is not implemented yet.\n");
#endif
    return true;
}

// Load a save file
SaveFile* SaveFile_Load(const char* fileName) {
    if (!fileName) return NULL;

#ifdef _WIN32
    FILE* file = fopen(fileName, "rb");
    if (!file) {
        printf("Failed to load save file: %s\n", fileName);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    void* data = malloc(fileSize);
    if (!data) {
        fclose(file);
        printf("Failed to allocate memory for save file: %s\n", fileName);
        return NULL;
    }

    fread(data, 1, fileSize, file);
    fclose(file);

    SaveFile* saveFile = (SaveFile*)malloc(sizeof(SaveFile));
    saveFile->fileName = strdup(fileName);
    saveFile->data = data;
    saveFile->size = fileSize;

    printf("Save file loaded: %s\n", fileName);
    return saveFile;
#else
    // Dreamcast VMU load (example stub)
    printf("VMU load functionality is not implemented yet.\n");
    return NULL;
#endif
}

// Delete a save file
bool SaveFile_Delete(const char* fileName) {
    if (!fileName) return false;

#ifdef _WIN32
    if (remove(fileName) == 0) {
        printf("Save file deleted: %s\n", fileName);
        return true;
    }
    else {
        printf("Failed to delete save file: %s\n", fileName);
        return false;
    }
#else
    // Dreamcast VMU delete (example stub)
    printf("VMU delete functionality is not implemented yet.\n");
    return false;
#endif
}

// Copy a save file
bool SaveFile_Copy(const char* sourceFileName, const char* destFileName) {
    if (!sourceFileName || !destFileName) return false;

#ifdef _WIN32
    FILE* source = fopen(sourceFileName, "rb");
    if (!source) {
        printf("Failed to open source file: %s\n", sourceFileName);
        return false;
    }

    FILE* dest = fopen(destFileName, "wb");
    if (!dest) {
        fclose(source);
        printf("Failed to create destination file: %s\n", destFileName);
        return false;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(source);
    fclose(dest);
    printf("Save file copied from %s to %s\n", sourceFileName, destFileName);
    return true;
#else
    // Dreamcast VMU copy (example stub)
    printf("VMU copy functionality is not implemented yet.\n");
    return false;
#endif
}

// Check if there's enough free space
bool SaveSystem_CheckSpace(size_t sizeNeeded) {
#ifdef _WIN32
    printf("Free space check not implemented for PC platform.\n");
    return true; // Assume enough space on PC for simplicity
#else
    // Dreamcast VMU free space check (example stub)
    printf("VMU space check not implemented yet.\n");
    return false;
#endif
}

// Get free space on the platform
size_t SaveSystem_GetFreeSpace() {
#ifdef _WIN32
    printf("Free space retrieval not implemented for PC platform.\n");
    return (size_t)-1; // Unlimited for simplicity
#else
    // Dreamcast VMU free space retrieval (example stub)
    printf("VMU space retrieval not implemented yet.\n");
    return 0;
#endif
}
