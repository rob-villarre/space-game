#ifndef SHIP_H
#define SHIP_H

#include "raylib.h"
#include "entity.h"
#include <memory>
#include <vector>

class Bullet;

class Ship : public Entity, public std::enable_shared_from_this<Ship> {
  private:
    std::shared_ptr<Texture2D> texture;
    std::shared_ptr<Texture2D> thrustTexture;
    std::shared_ptr<Music> thrustSound;
    std::shared_ptr<Sound> fireSound;
    Vector2 position = {0, 0};
    Vector2 velocity = {0, 0};
    float speed = 0.0;
    float turnRate = 0.0;
    float thrust = 0.0;
    float heading = 0.0;

    const std::vector<float> thrustRange = { -480.0, 480.0 };
    const std::vector<float> turnRateRange = { -180.0, 180.0 };
    const float maxSpeed = 240.0;
    const float drag = 80.0;
    const float radius = 20.0;
    const float mass = 300.0;

    float thrustFlameLength = 0.5f;
    float flameTimer = 0.0f;
    bool isThrustSoundPlaying = false;
    bool isFading = false;
    float fadeTimer = 0.0f;
    const float fadeTime = 0.3f;

    std::vector<std::unique_ptr<Bullet>> bullets;
    float lastFireTime = 0.0f;
    const float fireRate = 0.4f;

    void FireBullet();

  public:
    Ship();
    ~Ship();

    void Update() override;
    void Draw() override;

};

#endif