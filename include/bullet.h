#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"
#include "ship.h"
#include <memory>

class Bullet {
private:
    Vector2 position;
    float heading;
    std::shared_ptr<Ship> owner;
    std::shared_ptr<Texture2D> texture;

    float speed = 800.0f;
    float mass = 1.0f;
    Vector2 velocity;

    
public:
    Bullet(Vector2 position, float heading, std::shared_ptr<Ship> owner);
    ~Bullet();

    void Update();
    void Draw();

    Vector2 GetPosition();
    float GetHeading();
};

#endif