#include "game.h"
#include "raylib.h"
#include "texture_manager.h"
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
    ClearBackground(RAYWHITE);

    // Texture2D temp = *texture.get();
    // // DrawTexturePro(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
    // DrawTexturePro(temp, 
    //   Rectangle{0, 0, (float)temp.width, (float)temp.height}, 
    //   Rectangle{screenWidth/2.0f - (temp.width*4.0f)/2.0f, screenHeight/2.0f - (temp.height*4.0f)/2.0f, (float)temp.width*4.0f, (float)temp.height*4.0f}, 
    //   Vector2{0, 0}, 0, WHITE);
    Update();
    
    Draw();
    #if defined(PLATFORM_WEB)
        DrawText("Congrats!", 190, 200, 20, LIGHTGRAY);
    #else
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    #endif
    EndDrawing();
};