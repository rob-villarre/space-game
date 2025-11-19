#include "circle_collider.h"
#include "rectangle_collider.h"
#include "raylib.h"

CircleCollider::CircleCollider(Vector2 position, float radius)
    : Collider(position), radius(radius) {}

bool CircleCollider::CheckCollision(const Collider& other) const {
    return other.CollidesWith(*this);
}

bool CircleCollider::CollidesWith(const CircleCollider& circle) const {
    return CheckCollisionCircles(
        GetPosition(),
        GetRadius(),
        circle.GetPosition(),
        circle.GetRadius()
    );
}

bool CircleCollider::CollidesWith(const RectangleCollider& rect) const {
    return CheckCollisionCircleRec(
        GetPosition(),
        GetRadius(),
        rect.GetRect()
    );
}

void CircleCollider::DebugDraw(bool isColliding) const {
    Color color = isColliding ? RED : GREEN;
    DrawCircleV(GetPosition(), GetRadius(), color);
}

float CircleCollider::GetRadius() const {
    return radius;
}

void CircleCollider::SetRadius(float radius) {
    this->radius = radius;
}