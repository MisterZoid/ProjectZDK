// camera.h
#ifndef CAMERA_H
#define CAMERA_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdint.h>

// Camera Modes
typedef enum {
    CAMERA_MODE_ISOMETRIC,  // Default isometric view
    CAMERA_MODE_CUTSCENE    // Dynamic cutscene view
} CameraMode;

// Camera Struct
typedef struct {
    float x, y, z;          // Camera position
    float targetX, targetY, targetZ; // Camera target position (focus point)
    float zoom;             // Zoom level
    CameraMode mode;        // Current camera mode
    int currentAngle;       // Current compass angle (0-7, N to NW)
    int width, height, depth; // Added width, height, depth fields
} Camera;

// Initialization & Reset
EXPORT void Camera_Init(Camera* camera);
EXPORT void Camera_Reset(Camera* camera);

// Camera Controls
EXPORT void Camera_SetAngle(Camera* camera, int compassAngle); // Set compass angle (0-7)
EXPORT void Camera_Zoom(Camera* camera, float zoomLevel);       // Adjust zoom level
EXPORT void Camera_Pan(Camera* camera, float dx, float dy);    // Pan camera

// Cutscene Controls
EXPORT void Camera_SetCutscenePosition(Camera* camera, float x, float y, float z,
    float targetX, float targetY, float targetZ);
EXPORT void Camera_SetMode(Camera* camera, CameraMode mode);

// Updates
EXPORT void Camera_Update(Camera* camera);

#endif // CAMERA_H
