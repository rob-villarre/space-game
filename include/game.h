#ifndef GAME_H
#define GAME_H

#include "raylib.h"

class Game {
public:
  Game();
  ~Game();
  void Start();
  static void UpdateDrawFrame();
private:
  bool isRunning;
  void processInput();
  Vector2 screenSize;
};

#endif