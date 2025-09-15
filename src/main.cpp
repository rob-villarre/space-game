#include "raylib.h"
#include "game.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

const int screenWidth = 1600;
const int screenHeight = 900;

int main() {

    Game game;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(game.UpdateDrawFrame, 0, 1);
    #else
        SetTargetFPS(60);

        while (!WindowShouldClose()) {
            game.UpdateDrawFrame();
        }
    #endif

    CloseWindow();

    return 0;
}