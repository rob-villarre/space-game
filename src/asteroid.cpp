#include "asteroid.h"
#include <cmath>

Asteroid::Asteroid(Vector2 position, float speed, float angle, float radius) : position(position), speed(speed), angle(angle), radius(radius) {
    float speedScaler = 2.0f + (4.0f - radius) / 4.0f;
    maxSpeed = 60.0f * speedScaler;

    childCount = 3;

    mass = radius * radius * PI * 0.25f;

    velocity = {
        speed*std::cos(angle * DEG2RAD),
        speed*std::sin(angle * DEG2RAD)
    };

    angle = GetRandomValue(0, 360);
    turnRate = GetRandomValue(-100, 100);

    collider = std::make_unique<CircleCollider>(position, radius);
    collider->SetLayer(CollisionLayer::ASTEROID);
    collider->SetMask(static_cast<uint32_t>(CollisionLayer::BULLET) | static_cast<uint32_t>(CollisionLayer::SHIP));
}

Asteroid::~Asteroid() { }

void Asteroid::Update() {
    float dt = GetFrameTime();
    position = {
        position.x + velocity.x * dt,
        position.y + velocity.y * dt
    };

    angle += dt * turnRate;

    collider->SetPosition(position);
}

void Asteroid::Draw() {
    DrawCircleV(position, radius, WHITE);
}

float Asteroid::GetRadius() {
    return radius;
}

Vector2 Asteroid::GetPosition() {
    return position;
}

CircleCollider& Asteroid::GetCollider() {
    return *collider;
}