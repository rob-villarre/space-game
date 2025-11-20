#include "world.h"

World& World::Instance() {
    static World instance;
    return instance;
}

void World::Draw() {
    if (ship) {
        ship->Draw();
    }
    for (const auto& asteroid : asteroids) {
        asteroid->Draw();
    }
    for (const auto& bullet : bullets) {
        bullet->Draw();
    }
}

void World::Update() {
    if (ship) {
        ship->Update();
    }
    for (const auto& asteroid : asteroids) {
        asteroid->Update();
    }
    for (auto it = bullets.begin(); it != bullets.end();) {
        (*it)->Update();
        // Remove bullets that are off-screen
        Vector2 bulletPos = (*it)->GetPosition();
        if (bulletPos.x < -50 || bulletPos.x > GetScreenWidth() + 50 || 
            bulletPos.y < -50 || bulletPos.y > GetScreenHeight() + 50) {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }
}

void World::CheckCollisions() {
    // Check bullet-asteroid collisions
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletErased = false;
        CircleCollider& bulletCollider = (*bulletIt)->GetCollider();

        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end() && !bulletErased;) {
            CircleCollider& asteroidCollider = (*asteroidIt)->GetCollider();

            if (bulletCollider.CheckCollision(asteroidCollider)) {
                float asteroidRadius = (*asteroidIt)->GetRadius();
                Vector2 asteroidPos = (*asteroidIt)->GetPosition();

                // Collision detected, erase both bullet and asteroid
                asteroidIt = asteroids.erase(asteroidIt);
                bulletIt = bullets.erase(bulletIt);
                bulletErased = true;
                
                //make 2 new smaller asteroids if the asteroid is large enough
                if (asteroidRadius > 10.0f) {
                    float newRadius = asteroidRadius / 2.0f;
                    World::Instance().Instantiate<Asteroid>(asteroidPos, 50.0f, GetRandomValue(0, 360), newRadius);
                    World::Instance().Instantiate<Asteroid>(asteroidPos, 50.0f, GetRandomValue(0, 360), newRadius);
                }
                

            } else {
                ++asteroidIt;
            }
        }

        if (!bulletErased) {
            ++bulletIt;
        }
    }

    // Additional collision checks (e.g., ship-asteroid) can be added here
}