#include "game.h"
#include "raylib.h"
#include "resource_manager.h"
#include "collision_layer.h"
#include "bullet.h"
#include "world.h"
#include <memory>
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


Game::Game(Vector2 initScreenSize) {

    InitWindow(initScreenSize.x, initScreenSize.y, "Space Game");
    InitAudioDevice();

    World::Instance().Initialize();
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
    World::Instance().Update();
}

void Game::Draw() {
    World::Instance().Draw();
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
    World::Instance().CheckCollisions();
}