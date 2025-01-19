#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <math.h>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

// Math Constants
#define PI 3.14159265358979323846

// Angle Conversions
EXPORT float DegToRad(float degrees);
EXPORT float RadToDeg(float radians);

// Interpolation
EXPORT float Lerp(float a, float b, float t);
EXPORT float SmoothStep(float edge0, float edge1, float x);

// Vector3 Structure
typedef struct {
    float x, y, z;
} Vector3;

// Vector Operations
EXPORT Vector3 Vector3_Add(Vector3 a, Vector3 b);
EXPORT Vector3 Vector3_Scale(Vector3 v, float scale);
EXPORT float Vector3_Dot(Vector3 a, Vector3 b);
EXPORT Vector3 Vector3_Cross(Vector3 a, Vector3 b);
EXPORT float Vector3_Length(Vector3 v);
EXPORT Vector3 Vector3_Normalize(Vector3 v);

// Matrix4x4 Structure
typedef struct {
    float m[16];
} Matrix4x4;

// Matrix Operations
EXPORT Matrix4x4 Matrix4x4_Identity();
EXPORT Matrix4x4 Matrix4x4_Translate(float x, float y, float z);
EXPORT Matrix4x4 Matrix4x4_Rotate(float angle, float x, float y, float z);
EXPORT Matrix4x4 Matrix4x4_Scale(float x, float y, float z);
EXPORT Vector3 Matrix4x4_TransformVector(Matrix4x4 matrix, Vector3 vector);

#endif // MATH_UTILS_H
