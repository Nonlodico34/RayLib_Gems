#pragma once
#include "imports.h"

class Particle
{
public:
    using EasingFunction = function<float(float)>;

    Particle(float radius);
    Particle(Texture2D *texture);
    void Update();
    void Draw() const;
    bool IsAlive() const;

    static float EaseLinear(float t);
    static float EaseInOutSine(float t);
    static float EaseInOutQuad(float t);

private:
    void Init();

public:
    Vector2 position;
    Vector2 velocity; // Velocità della particella

    float radius;
    Texture2D *texture;
    float friction;

    float lifetime;
    float startTime;

    Color color;

    // Easing (sovrascrivono valori costanti)
    EasingFunction scaleEasing;
    EasingFunction alphaEasing;
    EasingFunction speedEasing;
    EasingFunction angularEasing;
};

Particle::Particle(float radius)
{
    this->radius = radius;
    this->texture = nullptr;
    Init();
}

Particle::Particle(Texture2D *texture)
{
    this->radius = 0.0f;
    this->texture = texture;
    Init();
}

void Particle::Init()
{
    this->position = {0, 0};
    this->velocity = {0, 0}; // Inizializza velocità a 0
    this->friction = 0.98f;

    this->lifetime = 2.0f;
    this->startTime = GetTime();

    this->color = WHITE;

    // Default easing: linear
    this->scaleEasing = EaseLinear;
    this->alphaEasing = EaseLinear;
    this->speedEasing = EaseLinear;
    this->angularEasing = EaseLinear;
}

void Particle::Update()
{
    float dt = GetFrameTime();

    // Applicazione della friction per ridurre la velocità
    velocity.x *= friction;
    velocity.y *= friction;

    // Calcolo della nuova posizione
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void Particle::Draw() const
{
    float t = (GetTime() - startTime) / lifetime;
    if (t > 1.0f)
        t = 1.0f;

    float easedScale = scaleEasing ? scaleEasing(t) : 1.0f;
    float easedAlpha = alphaEasing ? alphaEasing(t) : 1.0f;
    float easedSpeed = speedEasing ? speedEasing(t) : 1.0f;
    float easedAngular = angularEasing ? angularEasing(t) : 0.0f;

    // Calcolo posizione dinamica basata sulla velocità
    Vector2 effectiveSpeed = {
        velocity.x * easedSpeed,
        velocity.y * easedSpeed};

    Vector2 pos = {
        position.x + effectiveSpeed.x * t * 60.0f,
        position.y + effectiveSpeed.y * t * 60.0f};

    float scale = easedScale;
    float rotation = easedAngular * t * 360.0f;

    Color drawColor = color;
    drawColor.a = (unsigned char)(easedAlpha * 255);

    if (texture != nullptr)
    {
        DrawTexturePro(
            *texture,
            {0.0f, 0.0f, (float)texture->width, (float)texture->height},
            {pos.x, pos.y, texture->width * scale, texture->height * scale},
            {texture->width * scale / 2.0f, texture->height * scale / 2.0f},
            rotation,
            drawColor);
    }
    else
    {
        DrawCircleV(pos, radius * scale, drawColor);
    }
}

bool Particle::IsAlive() const
{
    return GetTime() - startTime < lifetime;
}

float Particle::EaseLinear(float t)
{
    return t;
}

float Particle::EaseInOutSine(float t)
{
    return -(cosf(PI * t) - 1.0f) / 2.0f;
}

float Particle::EaseInOutQuad(float t)
{
    if (t < 0.5f)
        return 2.0f * t * t;
    else
        return -1.0f + (4.0f - 2.0f * t) * t;
}