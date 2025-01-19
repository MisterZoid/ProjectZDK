// memory_utils.h
#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stddef.h>
#include <stdint.h>

// Memory Management Functions
EXPORT void* Memory_Alloc(size_t size);
EXPORT void Memory_Free(void* ptr);
EXPORT void Memory_Zero(void* ptr, size_t size);

// Memory Pool for Efficient Allocation
typedef struct MemoryPool {
    void* pool;      // Pointer to the memory pool
    size_t blockSize; // Size of each block
    size_t poolSize;  // Total size of the memory pool
    uint8_t* freeBlocks; // Bitmap to track free blocks
} MemoryPool;

EXPORT MemoryPool* MemoryPool_Create(size_t blockSize, size_t blockCount);
EXPORT void MemoryPool_Destroy(MemoryPool* pool);
EXPORT void* MemoryPool_Allocate(MemoryPool* pool);
EXPORT void MemoryPool_Free(MemoryPool* pool, void* ptr);

#endif // MEMORY_UTILS_H

