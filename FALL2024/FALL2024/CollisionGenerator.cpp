#include "CollisionGenerator.h"
#include "AABB.h"
#include "OBB.h"
#include "Circle.h"

CollisionGenerator::CollisionGenerator() {
    initializeCollisionMatrix();
}

bool CollisionGenerator::generateContact(PhysicsBody* body1, PhysicsBody* body2, Contact& contact) {
    Shape* shape1 = body1->getShape();
    Shape* shape2 = body2->getShape();

    if (!shape1 || !shape2) return false;

    int type1 = static_cast<int>(shape1->getType());
    int type2 = static_cast<int>(shape2->getType());

    CollisionTest test = collisionTests[type1][type2];
    if (test) {
        if (test(shape1, shape2, contact)) {
            contact.bodies[0] = body1;
            contact.bodies[1] = body2;
            return true;
        }
    }
    return false;
}

bool CollisionGenerator::AABBvsAABB(const Shape* a, const Shape* b, Contact& contact) {
    const AABB* aabb1 = static_cast<const AABB*>(a);
    const AABB* aabb2 = static_cast<const AABB*>(b);

    // Check for overlap on each axis
    if (aabb1->getMax().x < aabb2->getMin().x || aabb1->getMin().x > aabb2->getMax().x ||
        aabb1->getMax().y < aabb2->getMin().y || aabb1->getMin().y > aabb2->getMax().y) 
    {
        return false;
    }

    // If overlap, calculate the contact point as the midpoint between AABBs
    contact.point = (aabb1->getCenter() + aabb2->getCenter()) * 0.5f;
    return true;
}

bool CollisionGenerator::OBBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
    const OBB* obb1 = static_cast<const OBB*>(a);
    const OBB* obb2 = static_cast<const OBB*>(b);

    // Axes to test: normals of obb1, obb2, and cross products of these axes
    std::vector<Vector3> axes = 
    {
        obb1->getRight(), obb1->getUp(),
        obb2->getRight(), obb2->getUp()
    };

    for (const auto& axis : axes) 
    {
        // Project both OBBs onto the axis
        float min1, max1, min2, max2;
        obb1->project(axis, min1, max1);
        obb2->project(axis, min2, max2);

        // Check for overlap
        if (max1 < min2 || max2 < min1) 
        {
            return false; // Separating axis found
        }
    }

    // If no separating axis is found, we have a collision
    contact.point = (obb1->getCenter() + obb2->getCenter()) * 0.5f;

    return true;
}

bool CollisionGenerator::AABBvsOBB(const Shape* a, const Shape* b, Contact& contact) {
    const AABB* aabb = static_cast<const AABB*>(a);
    const OBB* obb = static_cast<const OBB*>(b);

    // Axes to test: AABB's x, y axes and OBB's right, up axes
    std::vector<Vector3> axes = 
    {
        Vector3(1, 0, 0), Vector3(0, 1, 0),
        obb->getRight(), obb->getUp()
    };

    for (const auto& axis : axes) 
    {
        // Project both shapes onto the axis
        float minAABB, maxAABB;
        minAABB = aabb->getMin().x;
        maxAABB = aabb->getMax().x;
        minAABB = aabb->getMin().y;
        maxAABB = aabb->getMax().y;

        float  minOBB, maxOBB;
        obb->project(axis, minOBB, maxOBB);

        // Check for overlap
        if (maxAABB < minOBB || maxOBB < minAABB) {
            return false; // Separating axis found
        }
    }

    // If no separating axis is found, we have a collision
    contact.point = (aabb->getCenter() + obb->getCenter()) * 0.5f;
    return true;
}

bool CollisionGenerator::OBBvsAABB(const Shape* a, const Shape* b, Contact& contact) {
    return AABBvsOBB(b, a, contact);
}

void CollisionGenerator::initializeCollisionMatrix() {
    // Initialize all to nullptr
    for (auto& row : collisionTests)
        for (auto& test : row)
            test = nullptr;

    int AABB = static_cast<int>(Shape::Type::AABB);
    int OBB = static_cast<int>(Shape::Type::OBB);
    int Circle = static_cast<int>(Shape::Type::Circle);

    // Set up existing collision tests
    collisionTests[AABB][AABB] = &CollisionGenerator::AABBvsAABB;
    collisionTests[OBB][OBB] = &CollisionGenerator::OBBvsOBB;
    collisionTests[AABB][OBB] = &CollisionGenerator::AABBvsOBB;
    collisionTests[OBB][AABB] = &CollisionGenerator::OBBvsAABB;
    collisionTests[Circle][Circle] = &CollisionGenerator::CirclevsCircle;
    collisionTests[Circle][AABB] = &CollisionGenerator::CirclevsAABB;
    collisionTests[AABB][Circle] = &CollisionGenerator::AABBvsCircle;
    collisionTests[Circle][OBB] = &CollisionGenerator::CirclevsOBB;
    collisionTests[OBB][Circle] = &CollisionGenerator::OBBvsCircle;

}

bool CollisionGenerator::CirclevsCircle(const Shape* a, const Shape* b, Contact& contact) {
    const Circle* circle1 = static_cast<const Circle*>(a);
    const Circle* circle2 = static_cast<const Circle*>(b);

    Vector3 diff = circle2->getCenter() - circle1->getCenter();
    float distSquared = diff.magnitudSquared();
    float radiusSum = circle1->getRadius() + circle2->getRadius();

    if (distSquared <= radiusSum * radiusSum) {
        contact.point = circle1->getCenter() + diff * 0.5f;
        return true;
    }
    return false;
}

bool CollisionGenerator::CirclevsAABB(const Shape* a, const Shape* b, Contact& contact) {
    const Circle* circle = static_cast<const Circle*>(a);
    const AABB* aabb = static_cast<const AABB*>(b);

    // Find closest point on AABB to circle center
    Vector3 closestPoint;
    Vector3 circleCenter = circle->getCenter();

    // For each axis, clamp circle center to AABB bounds
    closestPoint.x = std::max(aabb->getMin().x, std::min(circleCenter.x, aabb->getMax().x));
    closestPoint.y = std::max(aabb->getMin().y, std::min(circleCenter.y, aabb->getMax().y));

    // Check if closest point is within circle's radius
    Vector3 diff = circleCenter - closestPoint;
    float distSquared = diff.magnitudSquared();

    if (distSquared <= circle->getRadius() * circle->getRadius()) {
        contact.point = closestPoint;
        return true;
    }
    return false;
}

bool CollisionGenerator::AABBvsCircle(const Shape* a, const Shape* b, Contact& contact) {
    return CirclevsAABB(b, a, contact);
}

bool CollisionGenerator::CirclevsOBB(const Shape* a, const Shape* b, Contact& contact) {
    const Circle* circle = static_cast<const Circle*>(a);
    const OBB* obb = static_cast<const OBB*>(b);

    // Convert circle center to OBB's local space
    Vector3 circleCenter = circle->getCenter() - obb->getCenter();

    // Get local space position using OBB's axes
    Vector3 localCenter(
        circleCenter.dot(obb->getRight()),
        circleCenter.dot(obb->getUp()),
        0.0f
    );

    // Find closest point in local space (clamp to OBB bounds)
    Vector3 closestPoint;
    closestPoint.x = std::max(-obb->getHalfExtents().x,
        std::min(localCenter.x, obb->getHalfExtents().x));
    closestPoint.y = std::max(-obb->getHalfExtents().y,
        std::min(localCenter.y, obb->getHalfExtents().y));

    // Convert back to world space
    Vector3 worldClosest = obb->getCenter() +
        obb->getRight() * closestPoint.x +
        obb->getUp() * closestPoint.y;

    // Check if closest point is within circle's radius
    Vector3 diff = circle->getCenter() - worldClosest;
    float distSquared = diff.magnitudSquared();

    if (distSquared <= circle->getRadius() * circle->getRadius()) {
        contact.point = worldClosest;
        return true;
    }
    return false;
}

bool CollisionGenerator::OBBvsCircle(const Shape* a, const Shape* b, Contact& contact) {
    return CirclevsOBB(b, a, contact);
}