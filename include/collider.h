#ifndef COLLIDER_H
#define COLLIDER_H

#include "collision_layer.h"
#include "raylib.h"

class Collider {
 public:
  virtual ~Collider() = default;

  virtual bool CheckCollision(const Collider &other) const = 0;
  virtual void DebugDraw(bool isColliding) const = 0;

  void SetPosition(const Vector2 &position) { this->position = position; }

  Vector2 GetPosition() const { return position; }

  void SetLayer(CollisionLayer layer) { this->layer = layer; }

  CollisionLayer GetLayer() const { return layer; }

  void SetMask(uint32_t mask) { this->mask = mask; }

  uint32_t GetMask() const { return mask; }

 protected:
  Vector2 position;
  CollisionLayer layer;
  uint32_t mask;

  Collider(Vector2 position)
      : position(position), layer(CollisionLayer::NONE), mask(0){};

  virtual bool CollidesWith(const class CircleCollider &circle) const = 0;
  virtual bool CollidesWith(const class RectangleCollider &rect) const = 0;

  friend class CircleCollider;
  friend class RectangleCollider;
};

#endif