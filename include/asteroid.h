#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#include "entity.h"
#include "circle_collider.h"
#include <memory>
#include <tuple>

class Asteroid : public Entity {
private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float maxSpeed;
    int childCount;
    float mass;
    float angle;
    float radius;
    float turnRate;
    std::shared_ptr<Texture2D> texture;
    std::unique_ptr<CircleCollider> collider;

public:
    Asteroid(Vector2 position, float speed, float angle, float radius);
    ~Asteroid();
    void Update() override;
    void Draw() override;
    float GetRadius();
    Vector2 GetPosition();

    CircleCollider& GetCollider();

};

#endif