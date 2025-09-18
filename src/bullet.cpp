#include "bullet.h"
#include "resource_manager.h"
#include <cmath>

Bullet::Bullet(Vector2 position, float heading, std::shared_ptr<Ship> owner) {

    this->texture = TextureManager::load("src/assets/kenneyshmup/Tiles/tile_0000.png");

    this->position = position;
    this->heading = heading;
    this->owner = owner;

    float rad_heading = heading * DEG2RAD;
    float cos_heading = std::cos(rad_heading);
    float sin_heading = std::sin(rad_heading);
    velocity = { speed*sin_heading, -speed*cos_heading };
}

Bullet::~Bullet() { }

void Bullet::Update() {
    float dt = GetFrameTime();
    position = { position.x + velocity.x * dt, position.y + velocity.y * dt };
}

void Bullet::Draw() {
    // DrawCircleV(position, 3.0f, YELLOW);
    Texture2D texture = *this->texture.get();

    DrawTexturePro(
        texture,
        Rectangle{0, 0, (float)texture.width, (float)texture.height},
        Rectangle{position.x, position.y, (float)texture.width, (float)texture.height},
        Vector2{(float)texture.width, (float)texture.height}, heading,
        WHITE
    );
}

Vector2 Bullet::GetPosition() {
    return position;
}

float Bullet::GetHeading() {
    return heading;
}