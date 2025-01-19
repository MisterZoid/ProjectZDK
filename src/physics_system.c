// physics_system.c
#include "physics_system.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_PHYSICS_OBJECTS 1024

static PhysicsObject* physicsObjects[MAX_PHYSICS_OBJECTS];
static int physicsObjectCount = 0;

// Initialize the physics system
void PhysicsSystem_Init() {
    physicsObjectCount = 0;
    memset(physicsObjects, 0, sizeof(physicsObjects));
    printf("Physics system initialized.\n");
}

// Shutdown the physics system
void PhysicsSystem_Shutdown() {
    for (int i = 0; i < physicsObjectCount; ++i) {
        PhysicsObject_Destroy(physicsObjects[i]);
    }
    physicsObjectCount = 0;
    printf("Physics system shut down.\n");
}

// Update the physics system
void PhysicsSystem_Update(float deltaTime) {
    for (int i = 0; i < physicsObjectCount; ++i) {
        PhysicsObject_Update(physicsObjects[i], deltaTime);
    }
}

// Create a physics object
PhysicsObject* PhysicsObject_Create(Vector3 position, CollisionShape shape, bool isStatic) {
    if (physicsObjectCount >= MAX_PHYSICS_OBJECTS) {
        printf("Error: Maximum physics objects reached.\n");
        return NULL;
    }

    PhysicsObject* object = (PhysicsObject*)malloc(sizeof(PhysicsObject));
    if (!object) return NULL;

    object->position = position;
    object->velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    object->acceleration = (Vector3){ 0.0f, 0.0f, 0.0f };
    object->shape = shape;
    object->isStatic = isStatic;

    physicsObjects[physicsObjectCount++] = object;
    printf("Physics object created at position (%.2f, %.2f, %.2f).\n", position.x, position.y, position.z);
    return object;
}

// Destroy a physics object
void PhysicsObject_Destroy(PhysicsObject* object) {
    if (!object) return;

    for (int i = 0; i < physicsObjectCount; ++i) {
        if (physicsObjects[i] == object) {
            physicsObjects[i] = physicsObjects[--physicsObjectCount];
            physicsObjects[physicsObjectCount] = NULL;
            break;
        }
    }
    free(object);
    printf("Physics object destroyed.\n");
}

// Apply a force to a physics object
void PhysicsObject_ApplyForce(PhysicsObject* object, Vector3 force) {
    if (!object || object->isStatic) return;

    object->acceleration = Vector3_Add(object->acceleration, force);
    printf("Force applied: (%.2f, %.2f, %.2f).\n", force.x, force.y, force.z);
}

// Update a physics object
void PhysicsObject_Update(PhysicsObject* object, float deltaTime) {
    if (!object || object->isStatic) return;

    // Update velocity and position using simple Euler integration
    object->velocity = Vector3_Add(object->velocity, Vector3_Scale(object->acceleration, deltaTime));
    object->position = Vector3_Add(object->position, Vector3_Scale(object->velocity, deltaTime));

    // Reset acceleration
    object->acceleration = (Vector3){ 0.0f, 0.0f, 0.0f };

    printf("Physics object updated: Position (%.2f, %.2f, %.2f).\n",
        object->position.x, object->position.y, object->position.z);
}

// Check collision between two shapes
bool Physics_CheckCollision(CollisionShape* shape1, CollisionShape* shape2) {
    if (!shape1 || !shape2) return false;

    // Example: Box collision (simple AABB check)
    if (shape1->type == COLLISION_SHAPE_BOX && shape2->type == COLLISION_SHAPE_BOX) {
        return !(shape1->position.x + shape1->size.x < shape2->position.x ||
            shape1->position.x > shape2->position.x + shape2->size.x ||
            shape1->position.y + shape1->size.y < shape2->position.y ||
            shape1->position.y > shape2->position.y + shape2->size.y ||
            shape1->position.z + shape1->size.z < shape2->position.z ||
            shape1->position.z > shape2->position.z + shape2->size.z);
    }

    // Add more collision checks (sphere, capsule, etc.) as needed
    return false;
}

// Perform a raycast
bool Physics_Raycast(Vector3 origin, Vector3 direction, float maxDistance, Vector3* hitPoint) {
    // Example: Simplistic raycast placeholder
    printf("Raycast performed from origin (%.2f, %.2f, %.2f).\n", origin.x, origin.y, origin.z);
    if (hitPoint) {
        *hitPoint = Vector3_Add(origin, Vector3_Scale(direction, maxDistance));
    }
    return true;
}
