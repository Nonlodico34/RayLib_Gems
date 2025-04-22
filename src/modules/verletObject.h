#pragma once
#include "imports.h"

#define DRAG 0.9f

class VerletObject
{
public:
    Vector2 position;
    float radius;
    bool active;

private:
    Vector2 position_old;
    Vector2 acceleration;

public:
    VerletObject();
    VerletObject(Vector2 pos, float radius);
    void UpdatePosition(float dt);
    void Accelerate(Vector2 acc);
    void Reset(Vector2 pos);
};

VerletObject::VerletObject()
{
    this->position = {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    this->position_old = position;
    this->acceleration = {0, 0};
    this->radius = 100;
    this->active = true;
}

VerletObject::VerletObject(Vector2 pos, float radius)
{
    this->position = pos;
    this->position_old = position;
    this->acceleration = {0, 0};
    this->radius = radius;
    this->active = true;
}

void VerletObject::UpdatePosition(float dt)
{
    Vector2 velocity = position - position_old;
    position_old = position;
    velocity *= DRAG;
    position += velocity + acceleration * dt * dt;
    acceleration = {0, 0};
}

void VerletObject::Accelerate(Vector2 acc)
{
    acceleration += acc;
}

void VerletObject::Reset(Vector2 pos)
{
    position = pos;
    position_old = position;
    acceleration = {0, 0};
}