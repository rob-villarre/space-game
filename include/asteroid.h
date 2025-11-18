#ifndef ASTEROID_H
#define ASTEROID_H

#include "raylib.h"
#include "circle_collider.h"
#include <memory>
#include <tuple>

class Asteroid {
private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float maxSpeed;
    int childCount;
    float mass;
    float radius;
    float angle;
    float turnRate;
    int size;
    std::shared_ptr<Texture2D> texture;
    std::unique_ptr<CircleCollider> collider;

public:
    Asteroid(Vector2 position, float speed, float angle, float size);
    ~Asteroid();
    void Update();
    void Draw();
    float GetRadius();
    Vector2 GetPosition();

    CircleCollider& GetCollider();

};

#endif