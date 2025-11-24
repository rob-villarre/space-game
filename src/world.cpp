#include "world.h"

#include <algorithm>

World &World::Instance() {
  static World instance;
  return instance;
}

void World::Initialize() {
  World::Instance().Instantiate<Ship>();
  World::Instance().Instantiate<Asteroid>(
      Vector2{GetScreenWidth() / 4.0f, GetScreenHeight() / 4.0f}, 20.0f, 30.0f,
      100.0f);
}

void World::Reset() {
  asteroids.clear();
  bullets.clear();
  ship.reset();
}

void World::Draw() {
  if (ship) {
    ship->Draw();
  }
  for (const auto &asteroid : asteroids) {
    asteroid->Draw();
  }
  for (const auto &bullet : bullets) {
    bullet->Draw();
  }
}

void World::Update() {
  if (ship) {
    ship->Update();
  }
  for (const auto &asteroid : asteroids) {
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
    CircleCollider &bulletCollider = (*bulletIt)->GetCollider();

    size_t asteroidsSize = asteroids.size();
    for (size_t i = 0; i < asteroidsSize; i++) {
      Asteroid *asteroid = asteroids[i].get();

      CircleCollider &asteroidCollider = asteroid->GetCollider();
      if (bulletCollider.CheckCollision(asteroidCollider)) {
        asteroid->SetAlive(false);
        (*bulletIt)->SetAlive(false);
        asteroid->OnDestroy();
        break;
      }
    }
  }

  // Check ship-asteroid collisions
  if (ship) {
    CircleCollider &shipCollider = ship->GetCollider();
    for (const auto &asteroid : asteroids) {
      CircleCollider &asteroidCollider = asteroid->GetCollider();
      if (shipCollider.CheckCollision(asteroidCollider)) {
        ship->SetAlive(false);
        // Handle ship destruction (e.g., end game, respawn, etc.)
        break;
      }
    }
  }

  if (ship && !ship->IsAlive()) {
    // Handle ship destruction logic here if needed
    ship.reset();
  }

  // Remove destroyed asteroids
  auto remove_it =
      std::remove_if(asteroids.begin(), asteroids.end(),
                     [](const std::unique_ptr<Asteroid> &asteroid) {
                       return !asteroid->IsAlive();
                     });

  asteroids.erase(remove_it, asteroids.end());

  // Remove destroyed bullets
  auto remove_bullets_it = std::remove_if(
      bullets.begin(), bullets.end(),
      [](const std::unique_ptr<Bullet> &bullet) { return !bullet->IsAlive(); });

  bullets.erase(remove_bullets_it, bullets.end());

  // Additional collision checks (e.g., ship-asteroid) can be added here
}