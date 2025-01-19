// file_utils.h
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>
#include <stddef.h>

// File Utility Functions
EXPORT bool File_Exists(const char* filepath);
EXPORT size_t File_GetSize(const char* filepath);
EXPORT char* File_ReadAllText(const char* filepath);
EXPORT bool File_WriteAllText(const char* filepath, const char* content);
EXPORT bool File_ReadBinary(const char* filepath, void* buffer, size_t size);
EXPORT bool File_WriteBinary(const char* filepath, const void* buffer, size_t size);

#endif // FILE_UTILS_H
