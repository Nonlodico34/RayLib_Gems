#pragma once
#include "imports.h"

float DegToRad(float degrees)
{
    return degrees * (PI / 180.0f);
}

float RadToDeg(float radians)
{
    return radians * (180.0f / PI);
}

float Distance(Vector2 a, Vector2 b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return sqrt(dx * dx + dy * dy);
}

float MapValue(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    return outputMin + ((value - inputMin) / (inputMax - inputMin)) * (outputMax - outputMin);
}

/*
float Clamp(float value, float min, float max)
{
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}
*/

/*
float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}
*/

/*
float Normalize(float value, float min, float max)
{
    return (value - min) / (max - min);
}
*/

float GetAngleBetween(Vector2 a, Vector2 b)
{
    float angleRad = atan2f(b.y - a.y, b.x - a.x);
    return RadToDeg(angleRad); // Convert radians to degrees
}

Vector2 GetRectCenter(Rectangle rect)
{
    return {rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f};
}

Vector2 RotatePoint(Vector2 point, Vector2 center, float angleDeg)
{
    float angleRad = DegToRad(angleDeg); // Convert degrees to radians
    float s = sinf(angleRad);
    float c = cosf(angleRad);

    // Traslazione rispetto al centro
    point.x -= center.x;
    point.y -= center.y;

    // Rotazione
    float xnew = point.x * c - point.y * s;
    float ynew = point.x * s + point.y * c;

    // Ritorna al sistema originale
    point.x = xnew + center.x;
    point.y = ynew + center.y;

    return point;
}

int RandomI(int min, int max)
{
    return (min + (rand() % ((max - min) + 1)));
}

float RandomF(float min, float max)
{
    return min + ((float)rand() / RAND_MAX) * (max - min);
}