#ifndef RECTANGLE_COLLIDER_H
#define RECTANGLE_COLLIDER_H

#include "collider.h"
#include "raylib.h"

class RectangleCollider: public Collider {
private:
    Vector2 size;
    float rotation;

protected:
    bool CollidesWith(const CircleCollider& circle) const override;
    bool CollidesWith(const RectangleCollider& rect) const override;


public:
    RectangleCollider(Vector2 position, Vector2 size, float rotation = 0.0f);

    bool CheckCollision(const Collider& other) const override;

    void DebugDraw(bool isColliding) const override;

    Rectangle GetRect() const;

    Vector2 GetSize() const;
    float GetRotation() const;

    void SetSize(const Vector2& size);
    void SetRotation(float rotation);

};

#endif