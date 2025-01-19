// time_utils.c
#include "time_utils.h"
#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

static clock_t startTime;
static clock_t frameStartTime;
static float deltaTime = 0.0f;
static int targetFPS = 60;
static float currentFPS = 0.0f;

// Start the timer
void Timer_Start() {
    startTime = clock();
    frameStartTime = clock();
    deltaTime = 0.0f;
    currentFPS = 0.0f;
}

// Get the time elapsed since the last frame
float Timer_GetDeltaTime() {
    return deltaTime;
}

// Delay for a specified number of milliseconds
void Timer_Delay(uint32_t milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

// Set the target frames per second
void Timer_SetTargetFPS(int fps) {
    targetFPS = fps;
}

// Begin tracking a frame
void Timer_BeginFrame() {
    frameStartTime = clock();
}

// End tracking a frame and apply frame rate control
void Timer_EndFrame() {
    clock_t frameEndTime = clock();
    deltaTime = (float)(frameEndTime - frameStartTime) / CLOCKS_PER_SEC;

    // Calculate current FPS
    if (deltaTime > 0.0f) {
        currentFPS = 1.0f / deltaTime;
    }

    // Frame rate control
    float targetFrameTime = 1.0f / targetFPS;
    if (deltaTime < targetFrameTime) {
        Timer_Delay((uint32_t)((targetFrameTime - deltaTime) * 1000));
    }
}

// Get the current frames per second
float Timer_GetCurrentFPS() {
    return currentFPS;
}
