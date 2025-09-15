#ifndef SHIP_H
#define SHIP_H

#include "raylib.h"
#include <memory>

class Ship {
  private:
    std::shared_ptr<Texture2D> texture;

  public:
    Ship();
    ~Ship();

    void Update();
    void Draw();

};

#endif