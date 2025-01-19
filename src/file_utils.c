// file_utils.c
#include "file_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DREAMCAST
#include <kos.h> // Dreamcast-specific file I/O
#else
#include <sys/stat.h> // For checking file existence and size on PC
#endif

// Check if a file exists
bool File_Exists(const char* filepath) {
#ifdef DREAMCAST
    FILE* file = fopen(filepath, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
#else
    struct stat buffer;
    return (stat(filepath, &buffer) == 0);
#endif
}

// Get the size of a file
size_t File_GetSize(const char* filepath) {
#ifdef DREAMCAST
    FILE* file = fopen(filepath, "r");
    if (!file) return 0;
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fclose(file);
    return size;
#else
    struct stat buffer;
    if (stat(filepath, &buffer) == 0) {
        return buffer.st_size;
    }
    return 0;
#endif
}

// Read all text from a file
char* File_ReadAllText(const char* filepath) {
    size_t size = File_GetSize(filepath);
    if (size == 0) return NULL;

    FILE* file = fopen(filepath, "r");
    if (!file) return NULL;

    char* content = (char*)malloc(size + 1);
    if (!content) {
        fclose(file);
        return NULL;
    }

    fread(content, 1, size, file);
    content[size] = '\0';

    fclose(file);
    return content;
}

// Write text to a file
bool File_WriteAllText(const char* filepath, const char* content) {
    FILE* file = fopen(filepath, "w");
    if (!file) return false;

    fprintf(file, "%s", content);
    fclose(file);
    return true;
}

// Read binary data from a file
bool File_ReadBinary(const char* filepath, void* buffer, size_t size) {
    FILE* file = fopen(filepath, "rb");
    if (!file) return false;

    fread(buffer, 1, size, file);
    fclose(file);
    return true;
}

// Write binary data to a file
bool File_WriteBinary(const char* filepath, const void* buffer, size_t size) {
    FILE* file = fopen(filepath, "wb");
    if (!file) return false;

    fwrite(buffer, 1, size, file);
    fclose(file);
    return true;
}
