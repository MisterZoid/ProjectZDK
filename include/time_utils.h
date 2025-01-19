// time_utils.h
#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdint.h>

// Timing Functions
EXPORT void Timer_Start();
EXPORT float Timer_GetDeltaTime();
EXPORT void Timer_Delay(uint32_t milliseconds);

// Frame Rate Control
EXPORT void Timer_SetTargetFPS(int fps);
EXPORT void Timer_BeginFrame();
EXPORT void Timer_EndFrame();
EXPORT float Timer_GetCurrentFPS();

#endif // TIME_UTILS_H

