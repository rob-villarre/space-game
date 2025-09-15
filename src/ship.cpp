#include "ship.h"
#include "texture_manager.h"

Ship::Ship() {
  texture = TextureManager::load(std::string("src/assets/kenneyshmup/Ships/ship_0000.png"));
}

Ship::~Ship() {}

void Ship::Update() {

}

void Ship::Draw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Texture2D texture = *this->texture.get();
    DrawTexturePro(texture, 
    Rectangle{0, 0, (float)texture.width, (float)texture.height}, 
    Rectangle{screenWidth/2.0f - (texture.width*4.0f)/2.0f, screenHeight/2.0f - (texture.height*4.0f)/2.0f, (float)texture.width*4.0f, (float)texture.height*4.0f}, 
    Vector2{0, 0}, 0, WHITE);
}
