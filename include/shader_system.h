// shader_system.h
#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <stdbool.h>

// Shader Types
typedef enum {
    SHADER_TYPE_VERTEX,
    SHADER_TYPE_FRAGMENT
} ShaderType;

// Shader Structure
typedef struct {
    const char* name;     // Shader name
    ShaderType type;      // Vertex or Fragment shader
    const char* source;   // Shader source code (for modern hardware)
    void* platformData;   // Platform-specific shader data (e.g., Dreamcast PVR data)
} Shader;

// Shader Program Structure
typedef struct {
    const char* name;     // Program name
    Shader* vertexShader; // Vertex shader
    Shader* fragmentShader; // Fragment shader
    void* platformProgram;  // Platform-specific program data
} ShaderProgram;

// Shader System Management
EXPORT bool ShaderSystem_Init();
EXPORT void ShaderSystem_Shutdown();

// Shader Management
EXPORT Shader* Shader_Create(const char* name, ShaderType type, const char* source);
EXPORT void Shader_Destroy(Shader* shader);

// Shader Program Management
EXPORT ShaderProgram* ShaderProgram_Create(const char* name, Shader* vertexShader, Shader* fragmentShader);
EXPORT void ShaderProgram_Destroy(ShaderProgram* program);
EXPORT void ShaderProgram_Use(ShaderProgram* program);

// Platform-Specific Utilities
EXPORT bool Shader_LoadForDreamcast(Shader* shader, const char* dreamcastPath);
EXPORT bool Shader_CompileForModernHardware(Shader* shader);

#endif // SHADER_SYSTEM_H

