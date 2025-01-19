// memory_utils.c
#include "memory_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef DREAMCAST
#include <kos.h> // Dreamcast-specific memory management
#endif

// Standard Memory Management
void* Memory_Alloc(size_t size) {
#ifdef DREAMCAST
    return malloc(size); // Replace with specific Dreamcast allocation if needed
#else
    return malloc(size);
#endif
}

void Memory_Free(void* ptr) {
    if (ptr) {
#ifdef DREAMCAST
        free(ptr); // Replace with specific Dreamcast deallocation if needed
#else
        free(ptr);
#endif
    }
}

void Memory_Zero(void* ptr, size_t size) {
    if (ptr) {
        memset(ptr, 0, size);
    }
}

// Memory Pool Implementation
MemoryPool* MemoryPool_Create(size_t blockSize, size_t blockCount) {
    size_t poolSize = blockSize * blockCount;
    MemoryPool* pool = (MemoryPool*)Memory_Alloc(sizeof(MemoryPool));

    if (!pool) {
        printf("Failed to allocate memory pool structure.\n");
        return NULL;
    }

    pool->pool = Memory_Alloc(poolSize);
    if (!pool->pool) {
        printf("Failed to allocate memory pool.\n");
        Memory_Free(pool);
        return NULL;
    }

    pool->blockSize = blockSize;
    pool->poolSize = poolSize;
    pool->freeBlocks = (uint8_t*)Memory_Alloc(blockCount);

    if (!pool->freeBlocks) {
        printf("Failed to allocate free block bitmap.\n");
        Memory_Free(pool->pool);
        Memory_Free(pool);
        return NULL;
    }

    memset(pool->freeBlocks, 1, blockCount); // Mark all blocks as free
    return pool;
}

void MemoryPool_Destroy(MemoryPool* pool) {
    if (!pool) return;

    Memory_Free(pool->freeBlocks);
    Memory_Free(pool->pool);
    Memory_Free(pool);
}

void* MemoryPool_Allocate(MemoryPool* pool) {
    if (!pool) return NULL;

    for (size_t i = 0; i < pool->poolSize / pool->blockSize; i++) {
        if (pool->freeBlocks[i]) {
            pool->freeBlocks[i] = 0; // Mark block as used
            return (void*)((uint8_t*)pool->pool + i * pool->blockSize);
        }
    }

    printf("Memory pool exhausted.\n");
    return NULL;
}

void MemoryPool_Free(MemoryPool* pool, void* ptr) {
    if (!pool || !ptr) return;

    size_t offset = (uint8_t*)ptr - (uint8_t*)pool->pool;
    size_t index = offset / pool->blockSize;

    if (index < pool->poolSize / pool->blockSize) {
        pool->freeBlocks[index] = 1; // Mark block as free
    }
    else {
        printf("Invalid pointer passed to MemoryPool_Free.\n");
    }
}
