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
    /*
    float const hypotenuse = 200;

    Vec2 reverseDir = velocity.Normalize().Negate();
    Vec2 hypotA = (position + (reverseDir.Rotate(PI / 12) * hypotenuse));
    Vec2 hypotB = (position + (reverseDir.Rotate(-PI / 12) * hypotenuse));

    auto const lineColor = raylib::Color::Black();


    position.DrawLine(hypotA, 20, lineColor);
    position.DrawLine(hypotB, 20, lineColor);
    hypotA.DrawLine(hypotB, 20, lineColor);
    */

    float scale = 0.05F;
    Vec2 imgCentre{215, 583};
    imgCentre *= scale;

    //! Taking rotation against {0, 1} normalizes the coordinates to a regular Cartesian Quadrant
    rotation = velocity.Angle(Vec2{0, 1});

    boid_texture.Draw(position + (imgCentre - imgCentre.Rotate(rotation)), (rotation / PI) * 180, scale, WHITE);

    // rotation += PI / 60;
}
