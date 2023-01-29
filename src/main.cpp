#include <iostream>
#include <random>

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

    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_real_distribution<double> magnitudeRoll{0.00, 10.00},
        directionRoll{0, 2 * PI};
    std::uniform_real_distribution<float> xRoll{0, screenWidth}, yRoll{0, screenHeight};

    std::vector<std::shared_ptr<Boid>> boids;

    for (size_t i = 0; i < 100; i++) {
        Vec2 pos{xRoll(engine), yRoll(engine)};
        Vec2 vel{cosf(directionRoll(engine)), sinf(directionRoll(engine))};
        vel = vel.Normalize() * magnitudeRoll(engine);

        boids.push_back(std::shared_ptr<Boid>(new Boid(pos, vel, Vec2::Zero())));
    }

    while (!window.ShouldClose()) {
        BeginDrawing();
        window.ClearBackground(WHITE);

        for (auto &boid : boids) {
            boid->update(boids);

            boid->draw();
        }
        EndDrawing();
    }

    return 0;
}
