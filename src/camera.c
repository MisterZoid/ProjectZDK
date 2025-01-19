// camera.c
#include "camera.h"
#include <math.h>
#include <stdio.h>

// Constants
#define DEFAULT_ZOOM 1.0f
#define MIN_ZOOM 0.5f
#define MAX_ZOOM 2.0f
#define M_PI 3.14159265358979323846 // Define M_PI if not defined

// Camera Initialization
void Camera_Init(Camera* camera) {
    if (!camera) return;

    camera->x = 0.0f;
    camera->y = 0.0f;
    camera->z = 10.0f; // Elevated for isometric view
    camera->targetX = 0.0f;
    camera->targetY = 0.0f;
    camera->targetZ = 0.0f;
    camera->zoom = DEFAULT_ZOOM;
    camera->mode = CAMERA_MODE_ISOMETRIC;
    camera->currentAngle = 0;
}

void Camera_Reset(Camera* camera) {
    if (!camera) return;
    Camera_Init(camera);
}

// Camera Angle Control
void Camera_SetAngle(Camera* camera, int compassAngle) {
    if (!camera) return;

    compassAngle %= 8; // Normalize to 0-7
    camera->currentAngle = compassAngle;

    float angleRad = compassAngle * (M_PI / 4.0f); // Convert compass to radians
    camera->x = cosf(angleRad) * 10.0f;            // Adjust position based on angle
    camera->y = sinf(angleRad) * 10.0f;
}

// Camera Zoom Control
void Camera_Zoom(Camera* camera, float zoomLevel) {
    if (!camera) return;

    if (zoomLevel < MIN_ZOOM) zoomLevel = MIN_ZOOM;
    if (zoomLevel > MAX_ZOOM) zoomLevel = MAX_ZOOM;

    camera->zoom = zoomLevel;
}

// Camera Pan Control
void Camera_Pan(Camera* camera, float dx, float dy) {
    if (!camera) return;

    camera->x += dx;
    camera->y += dy;
}

// Cutscene Controls
void Camera_SetCutscenePosition(Camera* camera, float x, float y, float z,
    float targetX, float targetY, float targetZ) {
    if (!camera) return;

    camera->x = x;
    camera->y = y;
    camera->z = z;
    camera->targetX = targetX;
    camera->targetY = targetY;
    camera->targetZ = targetZ;
}

void Camera_SetMode(Camera* camera, CameraMode mode) {
    if (!camera) return;

    camera->mode = mode;
}

// Camera Update (Stub)
void Camera_Update(Camera* camera) {
    if (!camera) return;

    switch (camera->mode) {
    case CAMERA_MODE_ISOMETRIC:
        // Logic for isometric updates (if needed)
        break;

    case CAMERA_MODE_CUTSCENE:
        // Logic for cutscene updates (if needed)
        break;

    default:
        printf("Unknown camera mode!\n");
        break;
    }
}
