#ifndef COLLIDER_H
#define COLLIDER_H

class Collider {
public:
    virtual ~Collider() = default;

    virtual bool CheckCollision(const Collider& other) const = 0;

    virtual bool CollidesWith(const class CircleCollider& circle) const = 0;
    virtual bool CollidesWith(const class RectangleCollider& rect) const = 0;

    virtual void DebugDraw(bool isColliding) const = 0;
};

#endif