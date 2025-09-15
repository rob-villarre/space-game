#include "game.h"
#include "raylib.h"
#include "texture_manager.h"
#include <memory>
#include <string>

#if defined(PLATFORM_WEB)
  #include <emscripten/emscripten.h>
#endif

const int screenWidth = 1600;
const int screenHeight = 900;

Game::Game() {};
Game::~Game() {};

void Game::UpdateDrawFrame() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  Texture2D texture = TextureManager::load(std::string("src/assets/kenneyshmup/Ships/ship_0000.png"));

  // DrawTexturePro(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
  DrawTexturePro(texture, 
    Rectangle{0, 0, (float)texture.width, (float)texture.height}, 
    Rectangle{screenWidth/2.0f - (texture.width*4.0f)/2.0f, screenHeight/2.0f - (texture.height*4.0f)/2.0f, (float)texture.width*4.0f, (float)texture.height*4.0f}, 
    Vector2{0, 0}, 0, WHITE);

  #if defined(PLATFORM_WEB)
    DrawText("Congrats!", 190, 200, 20, LIGHTGRAY);
  #else
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
  #endif
  EndDrawing();
};