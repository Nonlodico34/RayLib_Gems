#pragma once
#include "modules/imports.h"
#include "utils.h"

#define REGULAR_SCALE 3.1f
#define BIG_SCALE 4.f

class Item
{
public:
    Item(string type);
    void Update(bool picked);
    void Draw() const;
    void DrawShadow() const;
    void PickAnimation();

public:
    string type;
    Texture2D *texture;
    Vector2 position;
    Vector2 speed;
    float angle;
    float scale;
    float targetAngle;
    float targetScale;
    VerletObject *verlet;
};

Item::Item(string type)
{
    this->type = type;
    this->position.x = Random(0, GetScreenWidth());
    this->position.y = Random(0, GetScreenHeight());
    this->speed.x = 0;
    this->speed.y = 0;
    this->angle = 0;
    this->scale = REGULAR_SCALE;
    this->targetAngle = 0;
    this->targetScale = REGULAR_SCALE;
    this->texture = assetLoader.getTexture(type);
    this->verlet = new VerletObject(position, this->texture->width * REGULAR_SCALE / 2.f);
}

void Item::Update(bool picked)
{
    // Vai alla posizione del mouse
    if (picked)
    {
        verlet->active = false;
        targetScale = BIG_SCALE;
        Vector2 mousePosition = GetMousePosition();
        Vector2 difference = Vector2Subtract(mousePosition, position);
        position = Vector2Add(position, Vector2Scale(difference, 15.0f * GetFrameTime()));
    }
    else
    {
        if (!verlet->active)
        {
            verlet->active = true;
            verlet->Reset(position);
        }
        targetScale = REGULAR_SCALE;
        position = verlet->position;
    }

    // angle += 10 * GetFrameTime();
    // scale = 2 + sin(GetTime() * 2) / 10;

    float angleDifference = targetAngle - angle;
    if (angleDifference > 180.0f)
        angleDifference -= 360.0f;
    if (angleDifference < -180.0f)
        angleDifference += 360.0f;
    angle += angleDifference * 10.0f * GetFrameTime();

    float scaleDifference = targetScale - scale;
    scale += scaleDifference * 10.0f * GetFrameTime();
}

void Item::Draw() const
{
    DrawTexturePro(*texture,
                   Rectangle{0, 0, (float)texture->width, (float)texture->height},
                   Rectangle{position.x, position.y, (float)texture->width * scale, (float)texture->height * scale},
                   Vector2{(float)texture->width * scale / 2, (float)texture->height * scale / 2},
                   angle,
                   WHITE);
}

void Item::DrawShadow() const
{
    Color shadow = (Color){0, 0, 0, 80};

    // SHADOW
    DrawTexturePro(*texture,
                   Rectangle{0, 0, (float)texture->width, (float)texture->height},
                   Rectangle{position.x, position.y + 10, (float)texture->width * scale, (float)texture->height * scale},
                   Vector2{(float)texture->width * scale / 2, (float)texture->height * scale / 2},
                   angle,
                   shadow);
}

void Item::PickAnimation()
{
    float pitch = (float)Random(100, 250) / 100.f;
    float volume = pitch / 2.f;
    assetLoader.playSoundPro("gem_sound_" + to_string(Random(4, 5)), pitch, volume);

    targetAngle = Random(-30, 30);
}
