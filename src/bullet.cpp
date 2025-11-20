#include "bullet.h"
#include "resource_manager.h"
#include <cmath>

Bullet::Bullet(Vector2 position, float heading, std::weak_ptr<Ship> owner) {

    this->texture = TextureManager::Load("src/assets/kenneyshmup/Tiles/tile_0000.png");

    this->position = position;
    this->heading = heading;
    this->owner = owner;

    float rad_heading = heading * DEG2RAD;
    float cos_heading = std::cos(rad_heading);
    float sin_heading = std::sin(rad_heading);
    velocity = { speed*sin_heading, -speed*cos_heading };

    collider = std::make_unique<CircleCollider>(position, 5.0f);
    collider->SetLayer(CollisionLayer::BULLET);
    collider->SetMask(static_cast<uint32_t>(CollisionLayer::ASTEROID) | static_cast<uint32_t>(CollisionLayer::SHIP));
}

Bullet::~Bullet() { }

void Bullet::Update() {
    float dt = GetFrameTime();
    position = { position.x + velocity.x * dt, position.y + velocity.y * dt };

    collider->SetPosition(position);
}

void Bullet::Draw() {

    Texture2D texture = *this->texture.get();

    DrawTexturePro(
        texture,
        Rectangle{0, 0, (float)texture.width, (float)texture.height},
        Rectangle{position.x, position.y, (float)texture.width, (float)texture.height},
        Vector2{(float)texture.width / 2.0f, (float)texture.height / 2.0f},
        heading,
        WHITE
    );
}

std::weak_ptr<Ship> Bullet::GetOwner() {
    return owner;
}

Vector2 Bullet::GetPosition() {
    return position;
}

float Bullet::GetHeading() {
    return heading;
}

Rectangle Bullet::GetRect() {
    return Rectangle{position.x, position.y, (float)texture->width, (float)texture->height};
}

CircleCollider& Bullet::GetCollider() {
    return *collider;
}