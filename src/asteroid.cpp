#include "asteroid.h"

#include <cmath>

#include "world.h"

Asteroid::Asteroid(Vector2 position, float speed, float angle, float radius)
    : position(position), speed(speed), angle(angle), radius(radius) {
  float speedScaler = 2.0f + (4.0f - radius) / 4.0f;
  maxSpeed = 60.0f * speedScaler;

  mass = radius * radius * PI * 0.25f;

  childCount = GetRandomValue(2, 5);

  velocity = {speed * std::cos(angle * DEG2RAD),
              speed * std::sin(angle * DEG2RAD)};

  angle = GetRandomValue(0, 360);
  turnRate = GetRandomValue(-100, 100);

  collider = std::make_unique<CircleCollider>(position, radius);
  collider->SetLayer(CollisionLayer::ASTEROID);
  collider->SetMask(static_cast<uint32_t>(CollisionLayer::BULLET) |
                    static_cast<uint32_t>(CollisionLayer::SHIP));
}

Asteroid::~Asteroid() {}

void Asteroid::Update() {
  float dt = GetFrameTime();
  position = {position.x + velocity.x * dt, position.y + velocity.y * dt};

  angle += dt * turnRate;

  collider->SetPosition(position);
}

void Asteroid::Draw() { DrawCircleV(position, radius, WHITE); }

void Asteroid::OnCollision(Entity &other) {
  // TODO: play sound, spawn particles, etc.
}

void Asteroid::OnDestroy() {
  // Split into smaller asteroids if large enough
  if (radius > 15.0f) {
    float newRadius = radius / 2.0f;

    // Spawn multiple smaller asteroids at offset positions
    for (int i = 0; i < childCount; i++) {
      float offsetAngle = (360.0f / childCount) * i;
      Vector2 offset = {
          position.x + std::cos(offsetAngle * DEG2RAD) * newRadius,
          position.y + std::sin(offsetAngle * DEG2RAD) * newRadius};

      World::Instance().Instantiate<Asteroid>(
          offset,
          speed * 1.2f,  // Make them slightly faster
          GetRandomValue(0, 360), newRadius);
    }
  }
}

float Asteroid::GetRadius() { return radius; }

Vector2 Asteroid::GetPosition() { return position; }

CircleCollider &Asteroid::GetCollider() { return *collider; }