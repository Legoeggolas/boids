#include "../include/boid.hpp"

float const Boid::maximum_velocity = 10;
float const Boid::maximum_acceleration = 5;

Boid::Boid() : Boid(Vec2::Zero(), Vec2::One().Normalize(), Vec2::Zero()) {
}

Boid::Boid(Vec2 _pos) : Boid() {
    position = _pos;
}

Boid::Boid(Vec2 _pos, Vec2 _vel, Vec2 _accel) {
    position = _pos;
    velocity = _vel;
    acceleration = _accel;

    boid_texture = raylib::Texture("../../images/boid.png");
    rotation = 0;
}

void Boid::draw() {
    float scale = 0.05F;
    Vec2 imgCentre{215, 583};
    imgCentre *= scale;

    //! Taking rotation against {0, 1} normalizes the coordinates to a regular Cartesian Quadrant
    rotation = velocity.Angle(Vec2{0, 0}.Normalize()) + PI;

    boid_texture.Draw(position + (imgCentre - imgCentre.Rotate(rotation)), (rotation / PI) * 180, scale, WHITE);
}
