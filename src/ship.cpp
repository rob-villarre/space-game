#include "ship.h"
#include "raylib.h"
// #include "texture_manager.h"
#include "resource_manager.h"
#include <cmath>
#include <algorithm>
#include <iostream>

Ship::Ship() {
    texture = TextureManager::load(std::string("src/assets/kenneyshmup/Ships/ship_0000.png"));
    thrustTexture = TextureManager::load(std::string("src/assets/kenneyshmup/Tiles/tile_0000.png"));

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int textureWidth = texture->width;
    int textureHeight = texture->height;
    position = {screenWidth/2.0f - (textureWidth*4.0f)/2.0f, screenHeight/2.0f - (textureHeight*4.0f)/2.0f};
}

Ship::~Ship() {}

void Ship::Update() {

    float dt = GetFrameTime();
    turnRate = 0.0;
    thrust = 0.0;

    if (IsKeyDown(KEY_W)) {
        thrust = 150.0;
    }
    if (IsKeyDown(KEY_S)) {
        thrust = -150.0;
    }
    if (IsKeyDown(KEY_A)) {
        turnRate = -180.0;
    }
    if (IsKeyDown(KEY_D)) {
        turnRate = 180.0;
    }

    float drag = this->drag * dt;
    if (drag > std::abs(speed)) {
        speed = 0.0;
    } else {
        speed -= drag * std::copysign(1.0, speed);
    }

    // bound check thrust
    thrust = std::clamp(thrust, thrustRange[0], thrustRange[1]);

    speed += thrust * dt;

    speed = std::clamp(speed, -maxSpeed, maxSpeed);

    // bound check turn rate
    turnRate = std::clamp(turnRate, turnRateRange[0], turnRateRange[1]);

    heading += turnRate * dt;

    heading = std::fmod(heading, 360.0);
    if (heading < 0) {
        heading += 360.0;
    }

    // use speed magnitude to get velocity vector
    float headingRad = heading * PI / 180.0;
    velocity = {speed * std::sin(headingRad), speed * -std::cos(headingRad)};

    // update position based on velocity
    position = {position.x + velocity.x * dt, position.y + velocity.y * dt};


}

void Ship::Draw() {

    Texture2D texture = *this->texture.get();
    Texture2D thrustTexture = *this->thrustTexture.get();

    // Draw thrust
    if (thrust > 0) {
        float headingRad = heading * PI / 180.0;

        float engineOffset = texture.height;
        float engineX = position.x - std::sin(headingRad) * engineOffset;
        float engineY = position.y + std::cos(headingRad) * engineOffset;

        // Random length between 1.0 and 3.0
        float randomLength = 1.0f + GetRandomValue(0, 100) / 100.0f;

        DrawTexturePro(
            thrustTexture,
            Rectangle{0, 0, (float)thrustTexture.width, (float)thrustTexture.height},
            Rectangle{engineX, engineY, (float)thrustTexture.width * 2.0f, (float)thrustTexture.height * randomLength},
            Vector2{(float)thrustTexture.width, (float)thrustTexture.height}, heading,
            WHITE
        );
    }

    // Draw Ship
    DrawTexturePro(
        texture, 
        Rectangle{0, 0, (float)texture.width, (float)texture.height}, 
        Rectangle{position.x, position.y, (float)texture.width*2.0f, (float)texture.height*2.0f}, 
        Vector2{(float)texture.width, (float)texture.height}, heading,
        WHITE
    );
}
