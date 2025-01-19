// shader_system.c
#include "shader_system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <dc/pvr.h> // Dreamcast-specific header for PVR rendering
#endif

// Shader System Initialization
bool ShaderSystem_Init() {
#ifdef _WIN32
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("GLEW initialization failed: %s\n", glewGetErrorString(err));
        return false;
    }
    printf("Shader system initialized for modern hardware.\n");
#else
    printf("Shader system initialized for Dreamcast hardware.\n");
#endif
    return true;
}

// Shader System Shutdown
void ShaderSystem_Shutdown() {
    printf("Shader system shut down.\n");
}

// Create a shader
Shader* Shader_Create(const char* name, ShaderType type, const char* source) {
    if (!name || !source) return NULL;

    Shader* shader = (Shader*)malloc(sizeof(Shader));
    if (!shader) return NULL;

    shader->name = strdup(name);
    shader->type = type;
    shader->source = strdup(source);
    shader->platformData = NULL;

#ifdef _WIN32
    if (!Shader_CompileForModernHardware(shader)) {
        printf("Failed to compile shader: %s\n", name);
        free((void*)shader->name);
        free((void*)shader->source);
        free(shader);
        return NULL;
    }
#else
    printf("Shader %s created for Dreamcast (compilation skipped).\n", name);
#endif
    return shader;
}

// Destroy a shader
void Shader_Destroy(Shader* shader) {
    if (!shader) return;

#ifdef _WIN32
    if (shader->platformData) {
        glDeleteShader((GLuint)(intptr_t)shader->platformData);
    }
#else
    // Dreamcast-specific cleanup (if any)
#endif

    free((void*)shader->name);
    free((void*)shader->source);
    free(shader);
}

// Create a shader program
ShaderProgram* ShaderProgram_Create(const char* name, Shader* vertexShader, Shader* fragmentShader) {
    if (!name || !vertexShader || !fragmentShader) return NULL;

    ShaderProgram* program = (ShaderProgram*)malloc(sizeof(ShaderProgram));
    if (!program) return NULL;

    program->name = strdup(name);
    program->vertexShader = vertexShader;
    program->fragmentShader = fragmentShader;
    program->platformProgram = NULL;

#ifdef _WIN32
    GLuint programID = glCreateProgram();
    glAttachShader(programID, (GLuint)(intptr_t)vertexShader->platformData);
    glAttachShader(programID, (GLuint)(intptr_t)fragmentShader->platformData);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        printf("Shader program linking failed: %s\n", infoLog);
        free((void*)program->name);
        free(program);
        return NULL;
    }

    program->platformProgram = (void*)(intptr_t)programID;
    printf("Shader program %s created for modern hardware.\n", name);
#else
    printf("Shader program %s created for Dreamcast (linking skipped).\n", name);
#endif

    return program;
}

// Destroy a shader program
void ShaderProgram_Destroy(ShaderProgram* program) {
    if (!program) return;

#ifdef _WIN32
    if (program->platformProgram) {
        glDeleteProgram((GLuint)(intptr_t)program->platformProgram);
    }
#else
    // Dreamcast-specific cleanup (if any)
#endif

    free((void*)program->name);
    free(program);
}

// Use a shader program
void ShaderProgram_Use(ShaderProgram* program) {
    if (!program) return;

#ifdef _WIN32
    glUseProgram((GLuint)(intptr_t)program->platformProgram);
#else
    // Dreamcast-specific setup (if any)
    printf("Using shader program %s (Dreamcast-specific behavior).\n", program->name);
#endif
}

// Load a shader for Dreamcast
bool Shader_LoadForDreamcast(Shader* shader, const char* dreamcastPath) {
    if (!shader || !dreamcastPath) return false;

    // Example stub for Dreamcast-specific shader loading
    printf("Loaded shader %s from %s for Dreamcast.\n", shader->name, dreamcastPath);
    return true;
}

// Compile a shader for modern hardware
bool Shader_CompileForModernHardware(Shader* shader) {
#ifdef _WIN32
    GLuint shaderID = (shader->type == SHADER_TYPE_VERTEX) ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);
    const char* source = shader->source;
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        printf("Shader compilation failed (%s): %s\n", shader->name, infoLog);
        return false;
    }

    shader->platformData = (void*)(intptr_t)shaderID;
    printf("Shader %s compiled successfully for modern hardware.\n", shader->name);
    return true;
#else
    return false;
#endif
}
