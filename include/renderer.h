// renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "math_utils.h" // For matrix and vector operations
#include "shader_system.h" // For shader management
#include <stdbool.h>

// Renderer Initialization and Shutdown
EXPORT bool Renderer_Init();
EXPORT void Renderer_Shutdown();

// Rendering Settings
EXPORT void Renderer_SetViewport(int x, int y, int width, int height);
EXPORT void Renderer_SetClearColor(float r, float g, float b, float a);
EXPORT void Renderer_Clear();

// Rendering Operations
EXPORT void Renderer_BeginFrame();
EXPORT void Renderer_EndFrame();

// 3D Model Rendering
EXPORT bool Renderer_LoadModel(const char* modelPath, void** modelData);
EXPORT void Renderer_UnloadModel(void* modelData);
EXPORT void Renderer_RenderModel(void* modelData, Matrix4 transform);

// 2D Sprite Rendering
EXPORT bool Renderer_LoadSprite(const char* texturePath, void** spriteData);
EXPORT void Renderer_UnloadSprite(void* spriteData);
EXPORT void Renderer_RenderSprite(void* spriteData, Vector2 position, float rotation, Vector2 scale);

#endif // RENDERER_H
