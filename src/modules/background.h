#pragma once
#include "imports.h"

class Background
{
public:
    Background();
    Background(Texture2D *texture);
    void Draw() const;

public:
    Texture2D *texture;
    Vector2 offset;
    float scale;
};

Background::Background()
{
    this->texture = nullptr;
    this->offset = {0, 0};
    this->scale = 1;
}

Background::Background(Texture2D *texture)
{
    this->texture = texture;
    this->offset = {0, 0};
    this->scale = 1;
}

void Background::Draw() const
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float texWidth = texture->width * scale;
    float texHeight = texture->height * scale;

    // Offset normalizzato (scorrimento continuo)
    float normOffsetX = fmodf(offset.x, texWidth);
    if (normOffsetX > 0)
        normOffsetX -= texWidth; // per evitare un buco a sinistra

    float normOffsetY = fmodf(offset.y, texHeight);
    if (normOffsetY > 0)
        normOffsetY -= texHeight; // per evitare un buco in alto

    // Ripeti la texture per coprire tutta la finestra
    for (float y = normOffsetY; y < screenHeight; y += texHeight)
    {
        for (float x = normOffsetX; x < screenWidth; x += texWidth)
        {
            DrawTextureEx(
                *texture,
                {x, y},
                0.0f,
                scale,
                WHITE);
        }
    }
}
