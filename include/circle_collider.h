#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "collider.h"
#include "raylib.h"

class CircleCollider : public Collider {
 private:
  float radius;

 protected:
  bool CollidesWith(const CircleCollider &circle) const override;
  bool CollidesWith(const RectangleCollider &rect) const override;

 public:
  CircleCollider(Vector2 position, float radius);

  bool CheckCollision(const Collider &other) const override;
  void DebugDraw(bool isColliding) const override;

  float GetRadius() const;

  void SetRadius(float radius);
};

#endif