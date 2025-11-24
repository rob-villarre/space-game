#ifndef GAME_H
#define GAME_H

#include <memory>

#include "asteroid.h"
#include "raylib.h"
#include "ship.h"

enum class GameState { MENU, PLAYING, PAUSED, GAMEOVER };

class Game {
 public:
  Game(Vector2 initScreenSize);
  ~Game();
  void Start();
  void Update();
  void CheckCollisions();
  void Draw();
  void UpdateDrawFrame();

  void Menu();
  void Paused();
  void GameOver();
  void Playing();

 private:
  bool isRunning;
  GameState gameState;
};

#endif