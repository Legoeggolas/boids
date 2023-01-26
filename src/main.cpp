#include <iostream>

#include "../include/boid.hpp"

int main() {
    int const screenWidth = 1920;
    int const screenHeight = 1080;
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    raylib::Window window(screenWidth, screenHeight, "nanomachines son");
    SetTargetFPS(60);

#ifdef CN
    CPRINT("Window created\n");
#endif

    Boid boid(Vec2{screenWidth / 2, screenHeight / 2});
    std::cout << boid.velocity.GetX() << std::endl;

    while (!window.ShouldClose()) {
        BeginDrawing();
        window.ClearBackground(WHITE);

        boid.draw();
        EndDrawing();
    }

    return 0;
}
