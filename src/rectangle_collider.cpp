#include "rectangle_collider.h"
#include "circle_collider.h"
#include "raylib.h"


RectangleCollider::RectangleCollider(Vector2 position, Vector2 size, float rotation)
    : position(position), size(size), rotation(rotation) {}

bool RectangleCollider::CheckCollision(const Collider& other) const {
    return other.CollidesWith(*this);
}

bool RectangleCollider::CollidesWith(const CircleCollider& circle) const {
    return CheckCollisionCircleRec(
        circle.GetPosition(),
        circle.GetRadius(),
        GetRect()
    );
}

bool RectangleCollider::CollidesWith(const RectangleCollider& rect) const {
    return CheckCollisionRecs(
        GetRect(),
        rect.GetRect()
    );
}

void RectangleCollider::DebugDraw(bool isColliding) const {
    Color color = isColliding ? RED : GREEN;
    DrawRectanglePro(GetRect(), GetSize(), rotation, color);
}

Rectangle RectangleCollider::GetRect() const {
    return { position.x, position.y, size.x, size.y };
}

Vector2 RectangleCollider::GetPosition() const {
    return position;
}

Vector2 RectangleCollider::GetSize() const {
    return size;
}

float RectangleCollider::GetRotation() const {
    return rotation;
}

void RectangleCollider::SetPosition(const Vector2& position) {
    this->position = position;
}

void RectangleCollider::SetSize(const Vector2& size) {
    this->size = size;
}

void RectangleCollider::SetRotation(float rotation) {
    this->rotation = rotation;
}