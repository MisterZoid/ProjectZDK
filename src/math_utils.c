// math_utils.c
#include "math_utils.h"
#include "camera.h"  // For integrating with the camera system
#include "renderer.h" // For integrating with the renderer system

// Angle Conversions
float DegToRad(float degrees) {
    return degrees * (PI / 180.0f);
}

float RadToDeg(float radians) {
    return radians * (180.0f / PI);
}

// Interpolation
float Lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float SmoothStep(float edge0, float edge1, float x) {
    if (x < edge0) return 0.0f;
    if (x > edge1) return 1.0f;
    x = (x - edge0) / (edge1 - edge0);
    return x * x * (3.0f - 2.0f * x);
}

// Vector Operations
Vector3 Vector3_Add(Vector3 a, Vector3 b) {
    return (Vector3) { a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 Vector3_Scale(Vector3 v, float scale) {
    return (Vector3) { v.x* scale, v.y* scale, v.z* scale };
}

float Vector3_Dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3_Cross(Vector3 a, Vector3 b) {
    return (Vector3) {
        a.y* b.z - a.z * b.y,
            a.z* b.x - a.x * b.z,
            a.x* b.y - a.y * b.x
    };
}

float Vector3_Length(Vector3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 Vector3_Normalize(Vector3 v) {
    float length = Vector3_Length(v);
    if (length == 0.0f) {
        return (Vector3) { 0.0f, 0.0f, 0.0f };
    }
    return Vector3_Scale(v, 1.0f / length);
}

// Matrix Operations
Matrix4x4 Matrix4x4_Identity() {
    Matrix4x4 mat = { 0 };
    for (int i = 0; i < 4; i++) {
        mat.m[i][i] = 1.0f;
    }
    return mat;
}

Matrix4x4 Matrix4x4_Scale(float sx, float sy, float sz) {
    Matrix4x4 mat = Matrix4x4_Identity();
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.m[2][2] = sz;
    return mat;
}

Matrix4x4 Matrix4x4_RotateX(float angle) {
    Matrix4x4 mat = Matrix4x4_Identity();
    float c = cosf(angle);
    float s = sinf(angle);
    mat.m[1][1] = c;
    mat.m[1][2] = -s;
    mat.m[2][1] = s;
    mat.m[2][2] = c;
    return mat;
}

Matrix4x4 Matrix4x4_RotateY(float angle) {
    Matrix4x4 mat = Matrix4x4_Identity();
    float c = cosf(angle);
    float s = sinf(angle);
    mat.m[0][0] = c;
    mat.m[0][2] = s;
    mat.m[2][0] = -s;
    mat.m[2][2] = c;
    return mat;
}

Matrix4x4 Matrix4x4_RotateZ(float angle) {
    Matrix4x4 mat = Matrix4x4_Identity();
    float c = cosf(angle);
    float s = sinf(angle);
    mat.m[0][0] = c;
    mat.m[0][1] = -s;
    mat.m[1][0] = s;
    mat.m[1][1] = c;
    return mat;
}

Matrix4x4 Matrix4x4_Translate(float tx, float ty, float tz) {
    Matrix4x4 mat = Matrix4x4_Identity();
    mat.m[3][0] = tx;
    mat.m[3][1] = ty;
    mat.m[3][2] = tz;
    return mat;
}

Matrix4x4 Matrix4x4_Multiply(Matrix4x4 a, Matrix4x4 b) {
    Matrix4x4 result = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

Vector3 Matrix4x4_TransformVector(Matrix4x4 mat, Vector3 vec) {
    Vector3 result = {
        mat.m[0][0] * vec.x + mat.m[1][0] * vec.y + mat.m[2][0] * vec.z + mat.m[3][0],
        mat.m[0][1] * vec.x + mat.m[1][1] * vec.y + mat.m[2][1] * vec.z + mat.m[3][1],
        mat.m[0][2] * vec.x + mat.m[1][2] * vec.y + mat.m[2][2] * vec.z + mat.m[3][2]
    };
    return result;
}

// Example Integration Functions
void ApplyTransformationToCamera(Camera* camera, Matrix4x4 transform) {
    if (!camera) return;

    Vector3 position = { camera->x, camera->y, camera->z };
    Vector3 transformedPosition = Matrix4x4_TransformVector(transform, position);

    camera->x = transformedPosition.x;
    camera->y = transformedPosition.y;
    camera->z = transformedPosition.z;
}

void ApplyTransformationToRenderer(Matrix4x4 transform) {
    Renderer_SetTransform(transform); // Assuming Renderer has a set transform function
}
