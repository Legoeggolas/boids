#include "../include/boid.hpp"

float const Boid::maximum_velocity = 2.5;
float const Boid::maximum_acceleration = 0.01;

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

void Boid::calculateRotation() {
    rotation = Vec2{0, -1}.Angle(velocity);

    if (rotation < 0) {
        rotation += 2 * PI;
    }
}

void Boid::draw() {
    float scale = 0.05F;
    Vec2 imgCentre{215, 583};
    imgCentre *= scale;

    calculateRotation();

    boid_texture.Draw(position + (imgCentre - imgCentre.Rotate(rotation)), (rotation / PI) * 180, scale, WHITE);
}

void Boid::update(std::vector<std::shared_ptr<Boid>> const &visibleBoids) {
    Vec2 avgVelocity = Vec2::Zero();
    Vec2 avgPosition = Vec2::Zero();
    Vec2 avgSeparation = Vec2::Zero();
    for (auto const &boid : visibleBoids) {
        avgVelocity += boid->velocity;
        avgPosition += boid->position;
        avgSeparation += (position - boid->position);
    }

    if (visibleBoids.size() > 0) {
        avgVelocity /= visibleBoids.size();
        avgPosition /= visibleBoids.size();
        avgSeparation /= visibleBoids.size();
    }

    Vec2 steeringAccel = Vec2::Zero().Add(avgPosition - position).Add(avgVelocity);
    steeringAccel -= velocity;

    if (steeringAccel.Length() > maximum_acceleration) {
        steeringAccel = steeringAccel.Normalize() * maximum_acceleration;
    }

    velocity += steeringAccel;

    if (velocity.Length() > maximum_velocity) {
        velocity = velocity.Normalize() * maximum_velocity;
    }

    position += velocity;

    float scale = 0.05F;
    Vec2 imgCentre{215, 583};
    imgCentre *= scale;

    Vec2 centrePos = position + imgCentre;

    // wrapping logic
    if (centrePos.x < 0) {
        position.x = GetScreenWidth() - imgCentre.x;
    }
    if (centrePos.x > GetScreenWidth()) {
        position.x = imgCentre.x / 2;
    }

    if (centrePos.y < 0) {
        position.y = GetScreenHeight() - imgCentre.y;
    }
    if (centrePos.y > GetScreenHeight()) {
        position.y = imgCentre.y / 2;
    }
}
