#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "ship.h"
#include "asteroid.h"
#include <memory>

class Game {
public:
  Game(Vector2 initScreenSize);
  ~Game();
  void Start();
  void Update();
  void CheckCollisions();
  void Draw();
  void UpdateDrawFrame();
private:
  bool isRunning;
  std::unique_ptr<Ship> ship;
  std::unique_ptr<Asteroid> asteroid;
};

#endif