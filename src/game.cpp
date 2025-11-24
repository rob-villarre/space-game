#include "game.h"

#include <memory>
#include <string>

#include "bullet.h"
#include "collision_layer.h"
#include "raylib.h"
#include "resource_manager.h"
#include "world.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

Game::Game(Vector2 initScreenSize) {
  gameState = GameState::MENU;

  InitWindow(initScreenSize.x, initScreenSize.y, "Space Game");
  InitAudioDevice();
  World::Instance().Initialize();
};

Game::~Game(){};

void Game::Start() {
#if defined(PLATFORM_WEB)
  auto wrapper = [](void *game) {
    static_cast<Game *>(game)->UpdateDrawFrame();
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

  if (IsKeyPressed(KEY_ENTER)) {
    gameState = GameState::PAUSED;
  }

  std::shared_ptr<Ship> ship = World::Instance().GetShip();
  if (ship == nullptr || !ship->IsAlive()) {
    gameState = GameState::GAMEOVER;
  }
}

void Game::Draw() { World::Instance().Draw(); }

void Game::UpdateDrawFrame() {
  switch (gameState) {
    case GameState::MENU:
      Menu();
      break;
    case GameState::PLAYING:
      Playing();
      break;
    case GameState::PAUSED:
      Paused();
      break;
    case GameState::GAMEOVER:
      GameOver();
      break;
    default:
      break;
  }
};

void Game::Playing() {
  BeginDrawing();

  ClearBackground(BLACK);

  Update();

  CheckCollisions();

  Draw();

  EndDrawing();
}

void Game::GameOver() {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("GAME OVER - Press ENTER to Restart", GetScreenWidth() / 2 - 100,
           GetScreenHeight() / 2, 20, WHITE);
  if (IsKeyPressed(KEY_ENTER)) {
    // Reset the game world
    World::Instance().Reset();
    World::Instance().Initialize();
    gameState = GameState::PLAYING;
  }
  EndDrawing();
}

void Game::Paused() {
  BeginDrawing();
  ClearBackground(BLACK);
  Draw();
  DrawText("PAUSED - Press ENTER to Resume - Escape to Exit",
           GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 20, WHITE);
  if (IsKeyPressed(KEY_ENTER)) {
    gameState = GameState::PLAYING;
  }
  EndDrawing();
}

void Game::Menu() {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("MENU - Press ENTER to Start", GetScreenWidth() / 2 - 100,
           GetScreenHeight() / 2, 20, WHITE);
  if (IsKeyPressed(KEY_ENTER)) {
    gameState = GameState::PLAYING;
  }
  EndDrawing();
}

void Game::CheckCollisions() { World::Instance().CheckCollisions(); }