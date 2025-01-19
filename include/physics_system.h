// physics_system.h
#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include "math_utils.h" // For vector operations
#include <stdbool.h>

// Collision Shape Types
typedef enum {
    COLLISION_SHAPE_BOX,
    COLLISION_SHAPE_SPHERE,
    COLLISION_SHAPE_CAPSULE
} CollisionShapeType;

// Collision Shape
typedef struct {
    CollisionShapeType type;
    Vector3 position;  // Position of the shape
    Vector3 size;      // Dimensions (box: width/height/depth, sphere: radius, capsule: height/radius)
} CollisionShape;

// Physics Object
typedef struct {
    Vector3 position;    // Current position
    Vector3 velocity;    // Current velocity
    Vector3 acceleration; // Current acceleration
    CollisionShape shape; // Collision shape
    bool isStatic;       // True if the object does not move
} PhysicsObject;

// Physics System Management
EXPORT void PhysicsSystem_Init();
EXPORT void PhysicsSystem_Shutdown();
EXPORT void PhysicsSystem_Update(float deltaTime);

// Physics Object Management
EXPORT PhysicsObject* PhysicsObject_Create(Vector3 position, CollisionShape shape, bool isStatic);
EXPORT void PhysicsObject_Destroy(PhysicsObject* object);
EXPORT void PhysicsObject_ApplyForce(PhysicsObject* object, Vector3 force);
EXPORT void PhysicsObject_Update(PhysicsObject* object, float deltaTime);

// Collision Detection
EXPORT bool Physics_CheckCollision(CollisionShape* shape1, CollisionShape* shape2);
EXPORT bool Physics_Raycast(Vector3 origin, Vector3 direction, float maxDistance, Vector3* hitPoint);

#endif // PHYSICS_SYSTEM_H

