#ifndef BOID_HPP
#define BOID_HPP

#include <memory>
#include <vector>

#include "../include/raylib/raylib-cpp.hpp"

using Vec2 = raylib::Vector2;

class Boid {
   public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    static float const maximum_velocity;
    static float const maximum_acceleration;

    raylib::Texture boid_texture;
    float rotation;

    Boid();
    Boid(Vec2 _pos);
    Boid(Vec2 _pos, Vec2 _vel, Vec2 _accel);

    void draw();
    void update(std::vector<std::shared_ptr<Boid>> const &visibleBoids);

   private:
    void calculateRotation();
};

#endif
