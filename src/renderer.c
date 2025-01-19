// renderer.c
#include "renderer.h"
#include "math_utils.h" // Use math utilities for transformations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef DREAMCAST
#include <dc/pvr.h>
#else
#include <GL/gl.h>
#endif

// Texture structure for Dreamcast and fallback
typedef struct {
    uint32_t id;         // Texture ID
    int width;           // Texture width
    int height;          // Texture height
    char filepath[256];  // Path to the texture file
} Texture;

// State variables
static float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
static Texture textureRegistry[1024]; // Example texture storage
static uint32_t nextTextureID = 1;
static Matrix4x4 currentTransform = { 0 }; // Global transform for the renderer

// Initialization
void Renderer_Init() {
#ifdef DREAMCAST
    pvr_init_params_t params = {
        .opb_sizes = {PVR_BINSIZE_16, PVR_BINSIZE_16, PVR_BINSIZE_16, PVR_BINSIZE_16},
        .vertex_buf_size = 512 * 1024,
        .dma_enabled = 1
    };
    if (pvr_init(&params) < 0) {
        printf("Failed to initialize Dreamcast PVR.\n");
    }
#else
    printf("Initializing OpenGL context...\n");
    glEnable(GL_TEXTURE_2D);
    currentTransform = Matrix4x4_Identity();
#endif
}

void Renderer_Shutdown() {
#ifdef DREAMCAST
    pvr_shutdown();
#else
    printf("Shutting down OpenGL context...\n");
#endif
}

// Scene Management
void Renderer_BeginScene() {
#ifdef DREAMCAST
    pvr_wait_ready();
    pvr_scene_begin();
#else
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}

void Renderer_EndScene() {
#ifdef DREAMCAST
    pvr_scene_finish();
#else
    // Swap buffers in modern rendering context
#endif
}

// Transformations
void Renderer_SetTransform(Matrix4x4 transform) {
    currentTransform = transform;
#ifdef DREAMCAST
    // Apply transformation logic for Dreamcast if needed
#else
    // Apply transformation for OpenGL (e.g., glLoadMatrixf)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMultMatrixf((const float*)transform.m);
#endif
}

// Drawing Primitives
void Renderer_DrawTriangle(float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3, uint32_t color) {
#ifdef DREAMCAST
    // Dreamcast-specific triangle rendering
#else
    glBegin(GL_TRIANGLES);
    glColor4ub((color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

    Vector3 v1 = Matrix4x4_TransformVector(currentTransform, (Vector3) { x1, y1, z1 });
    Vector3 v2 = Matrix4x4_TransformVector(currentTransform, (Vector3) { x2, y2, z2 });
    Vector3 v3 = Matrix4x4_TransformVector(currentTransform, (Vector3) { x3, y3, z3 });

    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
#endif
}

void Renderer_DrawQuad(float x1, float y1, float z1,
    float x2, float y2, float z2,
    float x3, float y3, float z3,
    float x4, float y4, float z4, uint32_t color) {
    Renderer_DrawTriangle(x1, y1, z1, x2, y2, z2, x3, y3, z3, color);
    Renderer_DrawTriangle(x1, y1, z1, x3, y3, z3, x4, y4, z4, color);
}

// Sprite Rendering
void Renderer_DrawSprite(float x, float y, float width, float height,
    uint32_t textureID, uint32_t color) {
    Texture* texture = &textureRegistry[textureID];
    if (!texture || texture->id == 0) return;

#ifdef DREAMCAST
    // Dreamcast-specific sprite rendering
#else
    glBindTexture(GL_TEXTURE_2D, (GLuint)texture->id);
    glColor4ub((color >> 24) & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

    Vector3 topLeft = Matrix4x4_TransformVector(currentTransform, (Vector3) { x, y, 0 });
    Vector3 topRight = Matrix4x4_TransformVector(currentTransform, (Vector3) { x + width, y, 0 });
    Vector3 bottomLeft = Matrix4x4_TransformVector(currentTransform, (Vector3) { x, y + height, 0 });
    Vector3 bottomRight = Matrix4x4_TransformVector(currentTransform, (Vector3) { x + width, y + height, 0 });

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(topLeft.x, topLeft.y, topLeft.z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(topRight.x, topRight.y, topRight.z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(bottomRight.x, bottomRight.y, bottomRight.z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(bottomLeft.x, bottomLeft.y, bottomLeft.z);
    glEnd();
#endif
}

// Texture Management
uint32_t Renderer_LoadTexture(const char* filepath, int filtering, int wrapping) {
    Texture* texture = &textureRegistry[nextTextureID];

    strncpy(texture->filepath, filepath, sizeof(texture->filepath));
    texture->id = nextTextureID;

#ifdef DREAMCAST
    // Dreamcast texture loading
    pvr_ptr_t tex = pvr_mem_malloc(256 * 256 * 2); // Example allocation
    pvr_txr_load_kimg(tex, filepath);
    texture->id = (uint32_t)tex;

#else
    // OpenGL texture loading
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Load the image using a library like stb_image or SOIL (not included in this example)
    // Example: Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapping);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapping);

    texture->id = texID;
#endif

    nextTextureID++;
    return texture->id;
}

void Renderer_UnloadTexture(uint32_t textureID) {
    Texture* texture = &textureRegistry[textureID];
    if (!texture || texture->id == 0) return;

#ifdef DREAMCAST
    // Dreamcast-specific unload
    pvr_mem_free((pvr_ptr_t)texture->id);
#else
    // OpenGL-specific unload
    glDeleteTextures(1, (GLuint*)&texture->id);
#endif

    memset(texture, 0, sizeof(Texture));
}

// Utility Functions
void Renderer_SetClearColor(float r, float g, float b, float a) {
    clearColor[0] = r;
    clearColor[1] = g;
    clearColor[2] = b;
    clearColor[3] = a;
#ifdef DREAMCAST
    // No direct equivalent in Dreamcast; handled elsewhere
#else
    glClearColor(r, g, b, a);
#endif
}

void Renderer_Clear() {
#ifdef DREAMCAST
    // Dreamcast-specific clear call
#else
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}

// Debug
void Renderer_PrintStats() {
#ifdef DREAMCAST
    // Print Dreamcast-specific performance stats
#else
    printf("Renderer stats: OpenGL fallback.\n");
#endif
}
