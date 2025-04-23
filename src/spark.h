#pragma once
#include "modules/imports.h"

class Spark : public Particle
{
public:
    Spark(Vector2 position, float maxRandOffest, Texture2D *texture);
};

Spark::Spark(Vector2 position, float maxRandOffest, Texture2D *texture) : Particle(texture)
{
    position += Vector2Scale(Vector2Normalize(Vector2{RandomF(-1, 1), RandomF(-1, 1)}), RandomF(-maxRandOffest, maxRandOffest));
    this->position = position;

    this->lifetime = 0.6f;
    this->friction = 0.9f;
    this->velocity = {RandomF(-10, 10), RandomF(-10, 10)};
    this->scaleEasing = [](float t)
    { return sin(t * PI) * 4; };
    this->alphaEasing = [](float t)
    { return 1; };
}