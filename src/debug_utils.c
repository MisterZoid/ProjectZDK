// debug_utils.c
#include "debug_utils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#endif

static bool debugEnabled = false;
static clock_t lastFrameTime = 0;
static int frameCount = 0;
static float fps = 0.0f;

// Logging Functions
void Log_Info(const char* message) {
    if (debugEnabled) {
        printf("[INFO]: %s\n", message);
    }
}

void Log_Warning(const char* message) {
    if (debugEnabled) {
        printf("[WARNING]: %s\n", message);
    }
}

void Log_Error(const char* message) {
    if (debugEnabled) {
        printf("[ERROR]: %s\n", message);
    }
}

// Debug Toggles
void Debug_Enable() {
    debugEnabled = true;
    printf("Debugging enabled.\n");
    lastFrameTime = clock();
    frameCount = 0;
    fps = 0.0f;
}

void Debug_Disable() {
    debugEnabled = false;
    printf("Debugging disabled.\n");
}

bool Debug_IsEnabled() {
    return debugEnabled;
}

// Performance Metrics
void Debug_UpdateFrameMetrics() {
    if (!debugEnabled) return;

    clock_t currentTime = clock();
    frameCount++;
    double elapsedTime = (double)(currentTime - lastFrameTime) / CLOCKS_PER_SEC;

    if (elapsedTime >= 1.0) {
        fps = frameCount / elapsedTime;
        frameCount = 0;
        lastFrameTime = currentTime;
    }
}

void Debug_DisplayFrameRate() {
    if (!debugEnabled) return;
    printf("FPS: %.2f\n", fps);
}

void Debug_DisplayMemoryUsage() {
    if (!debugEnabled) return;
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memInfo;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo))) {
        printf("Memory Usage: %lu KB\n", memInfo.WorkingSetSize / 1024);
    }
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        printf("Memory Usage: %ld KB\n", usage.ru_maxrss);
    }
#endif
}

void Debug_DisplayCPUUsage() {
    if (!debugEnabled) return;
#ifdef _WIN32
    FILETIME idleTime, kernelTime, userTime;
    if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        printf("CPU Usage: Kernel and User times captured.\n");
    }
#else
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0) {
        printf("CPU Time: User = %ld.%06lds, System = %ld.%06lds\n",
            usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
            usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    }
#endif
}

// Display Functions
void Debug_DisplayPosition(const char* label, Vector3 position) {
    if (!debugEnabled) return;
    printf("%s: (x: %.2f, y: %.2f, z: %.2f)\n", label, position.x, position.y, position.z);
}

void Debug_DisplayMatrix(const char* label, Matrix4x4 matrix) {
    if (!debugEnabled) return;
    printf("%s:\n", label);
    for (int i = 0; i < 4; i++) {
        printf("  [%.2f %.2f %.2f %.2f]\n", matrix.m[i][0], matrix.m[i][1], matrix.m[i][2], matrix.m[i][3]);
    }
}

void Debug_DisplayItem(const char* itemName, int itemID, int quantity) {
    if (!debugEnabled) return;
    printf("Item: %s (ID: %d), Quantity: %d\n", itemName, itemID, quantity);
}

// Test Functions
void Debug_TestCode(const char* codeSnippet) {
    if (!debugEnabled) return;
    printf("Testing code snippet:\n%s\n", codeSnippet);
    // Future expansion: Interpret and execute snippets dynamically
}

void Debug_TestItemInteractions(int itemID) {
    if (!debugEnabled) return;
    printf("Testing interactions with item ID: %d\n", itemID);
    // Placeholder for actual interaction tests
}

void Debug_TestInput() {
    if (!debugEnabled) return;
    printf("Testing input system...\n");
    // Placeholder for input testing logic
    printf("Input test complete.\n");
}

void Debug_TestAnimations(const char* animationName) {
    if (!debugEnabled) return;
    printf("Testing animation: %s\n", animationName);
    // Placeholder for animation testing logic
    printf("Animation test complete.\n");
}

void Debug_TestMapLoading(const char* mapName) {
    if (!debugEnabled) return;
    printf("Testing map loading: %s\n", mapName);
    // Placeholder for map loading test logic
    printf("Map loading test complete.\n");
}

void Debug_TestSceneSetup(const char* sceneName) {
    if (!debugEnabled) return;
    printf("Testing scene setup: %s\n", sceneName);
    // Placeholder for scene setup test logic
    printf("Scene setup test complete.\n");
}
