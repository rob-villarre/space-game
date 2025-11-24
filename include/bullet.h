#ifndef BULLET_H
#define BULLET_H

#include <memory>

#include "circle_collider.h"
#include "entity.h"
#include "raylib.h"
#include "ship.h"

class Bullet : public Entity {
 private:
  Vector2 position;
  float heading;
  std::weak_ptr<Ship> owner;
  std::shared_ptr<Texture2D> texture;

  float speed = 800.0f;
  float mass = 1.0f;
  Vector2 velocity;

  std::unique_ptr<CircleCollider> collider;

 public:
  Bullet(Vector2 position, float heading, std::weak_ptr<Ship> owner);
  ~Bullet();

  void Update() override;
  void Draw() override;
  void OnCollision(Entity &other) override{};

  std::weak_ptr<Ship> GetOwner();
  Vector2 GetPosition();
  float GetHeading();
  Rectangle GetRect();
  CircleCollider &GetCollider();
};

#endif