#include "AABB.h"
#include <iostream>

AABB::AABB( const Vector3& min,
            const Vector3& max)
    : localMin(min), localMax(max),
    worldMin(min), worldMax(max) {}

Shape::Type AABB::getType() const { 
    return Type::AABB; 
}

void AABB::update(Transform& transform){
    // Compute the local center of the AABB
    Vector3 localCenter = (localMin + localMax) * 0.5f;

    // Get the transform's world position
    Vector3 worldCenter = transform.getPosition();

    // Extract the scale from the transform
    Vector3 scale = transform.getScale();

    // Adjust the half extents based on the scale
    Vector3 localHalfExtents = (localMax - localMin) * 0.5f;
    Vector3 worldHalfExtents = Vector3(
        localHalfExtents.x * std::abs(scale.x),
        localHalfExtents.y * std::abs(scale.y),
        0.0f // Only for 2D
    );

    // Compute world min and max
    worldMin = worldCenter - worldHalfExtents;
    worldMax = worldCenter + worldHalfExtents;
}

// Utility functions
Vector3 AABB::getMin()          const { return worldMin; }
Vector3 AABB::getMax()          const { return worldMax; }
Vector3 AABB::getCenter()       const { return (worldMin + worldMax) * 0.5f; }
Vector3 AABB::getHalfExtents()  const { return (worldMax - worldMin) * 0.5f; }
float   AABB::getWidth()        const { return worldMax.x - worldMin.x; }
float   AABB::getHeight()       const { return worldMax.y - worldMin.y; }
