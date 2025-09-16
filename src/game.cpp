#include "game.h"
#include "raylib.h"
// #include "texture_manager.h"
#include "resource_manager.h"
#include <memory>
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

Game::Game(Vector2 screenSize) {
    this->screenSize = screenSize;

    InitWindow(screenSize.x, screenSize.y, "raylib [core] example - basic window");

    this->ship = std::make_unique<Ship>();
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

    CloseWindow();
}

void Game::Update() {
    ship.get()->Update();
}

void Game::Draw() {
    ship.get()->Draw();
}

void Game::UpdateDrawFrame() {
    BeginDrawing();
    ClearBackground(BLACK);

    Update();

    Draw();
    #if defined(PLATFORM_WEB)
        DrawText("Congrats!", 190, 200, 20, LIGHTGRAY);
    #else
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    #endif
    EndDrawing();
};