#include "game.h"
#include "raylib.h"
#include "resource_manager.h"
#include "collision_layer.h"
#include "bullet.h"
#include <memory>
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


Game::Game(Vector2 initScreenSize) {

    InitWindow(initScreenSize.x, initScreenSize.y, "Space Game");
    InitAudioDevice();


    this->ship = std::make_unique<Ship>();
    this->asteroid = std::make_unique<Asteroid>(Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}, 20.0f, 30.0f, 5.0f);
};

Game::~Game() {};

void Game::Start() {
    #if defined(PLATFORM_WEB)
        auto wrapper = [](void* game) { 
            static_cast<Game*>(game)->UpdateDrawFrame();
        };
        emscripten_set_main_loop_arg(wrapper, this, 0, 1);
    #else
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
    #endif

    CloseAudioDevice();
    CloseWindow();
}

void Game::Update() {
    ship.get()->Update();
    asteroid.get()->Update();
}

void Game::Draw() {
    ship.get()->Draw();
    asteroid.get()->Draw();
}

void Game::UpdateDrawFrame() {
    BeginDrawing();

    ClearBackground(BLACK);

    Update();

    CheckCollisions();

    Draw();

    EndDrawing();
};

void Game::CheckCollisions() {
    for (std::unique_ptr<Bullet>& b : ship->GetBullets()) {

        if (!canCollide(
            b->GetCollider().GetLayer(), asteroid->GetCollider().GetLayer(),
            b->GetCollider().GetMask(), asteroid->GetCollider().GetMask())
        ) {
            continue;
        }

        bool isColliding = b->GetCollider().CheckCollision(asteroid->GetCollider());
        if (!isColliding) {
            b->GetCollider().DebugDraw(false);
            continue;
        }

        if (isColliding) {
            asteroid->GetCollider().DebugDraw(true);
            b->GetCollider().DebugDraw(true);
        }
    }
}