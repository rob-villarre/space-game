#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "ship.h"
#include <memory>

class Game {
public:
  Game(Vector2 screenSize);
  ~Game();
  void Start();
  void Update();
  void Draw();
  void UpdateDrawFrame();
private:
  bool isRunning;
  void processInput();
  Vector2 screenSize;
  std::unique_ptr<Ship> ship;

};

#endif