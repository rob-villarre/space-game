#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "collider.h"
#include "raylib.h"

class CircleCollider: public Collider {
private:
    Vector2 position;
    float radius;
public:

    CircleCollider(Vector2 position, float radius);

    bool CheckCollision(const Collider& other) const override;

    bool CollidesWith(const CircleCollider& circle) const override;
    bool CollidesWith(const RectangleCollider& rect) const override;
    void DebugDraw(bool isColliding) const override;

    float GetRadius() const;
    Vector2 GetPosition() const;

    void SetPosition(const Vector2& position);
    void SetRadius(float radius);

};

#endif