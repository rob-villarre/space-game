#include "world.h"
#include <algorithm>

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
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); bulletIt++) {
        CircleCollider& bulletCollider = (*bulletIt)->GetCollider();

        int sizeBefore = asteroids.size();
        for (auto asteroidIt = asteroids.begin(); asteroidIt != asteroids.end(); asteroidIt++) {
            CircleCollider& asteroidCollider = (*asteroidIt)->GetCollider();

            if (bulletCollider.CheckCollision(asteroidCollider)) {
                (*asteroidIt)->SetAlive(false);
                (*bulletIt)->SetAlive(false);
            }
        }
    }

    size_t size = asteroids.size();
    for (size_t i = 0; i < size; i++) {
        Asteroid* asteroid = asteroids[i].get();
        if (!asteroid->IsAlive()) {
            asteroid->OnDestroy();
        }
    } 

    // Remove destroyed asteroids
    auto remove_it = std::remove_if(asteroids.begin(), asteroids.end(),
        [](const std::unique_ptr<Asteroid>& asteroid) {
            return !asteroid->IsAlive();
        });

    asteroids.erase(remove_it, asteroids.end());

    // Remove destroyed bullets
    auto remove_bullets_it = std::remove_if(bullets.begin(), bullets.end(),
        [](const std::unique_ptr<Bullet>& bullet) {
            return !bullet->IsAlive();
        });

    bullets.erase(remove_bullets_it, bullets.end());

    // Additional collision checks (e.g., ship-asteroid) can be added here
}