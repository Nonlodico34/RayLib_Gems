#pragma once
#include "imports.h"

#define REPULSION 100.f

class VerletSolver
{
public:
    vector<VerletObject *> objects;
    Vector2 gravity;
    Rectangle constraint;
    int subSteps;

public:
    VerletSolver();
    void AddObject(VerletObject *object);
    void Update();

private:
    void ApplyConstraint();
    void solveCollisions();
};

VerletSolver::VerletSolver()
{
    gravity = {0.f, 0.f};
    subSteps = 4; // default
}

void VerletSolver::AddObject(VerletObject *object)
{
    objects.push_back(object);
}

void VerletSolver::Update()
{
    float dt = GetFrameTime();
    float stepDt = dt / (float)subSteps;

    for (int i = 0; i < subSteps; ++i)
    {
        for (VerletObject *object : objects)
            if (object->active)
                object->Accelerate(gravity);

        ApplyConstraint();
        solveCollisions();

        for (VerletObject *object : objects)
            if (object->active)
                object->UpdatePosition(stepDt);
    }
}

void VerletSolver::ApplyConstraint()
{
    for (VerletObject *object : objects)
    {
        if (!object->active)
            continue;

        // Per la coordinata X
        if (object->position.x < constraint.x)
            object->position.x = constraint.x;
        else if (object->position.x > constraint.x + constraint.width)
            object->position.x = constraint.x + constraint.width;

        // Per la coordinata Y
        if (object->position.y < constraint.y)
            object->position.y = constraint.y;
        else if (object->position.y > constraint.y + constraint.height)
            object->position.y = constraint.y + constraint.height;
    }
}

void VerletSolver::solveCollisions()
{
    for (int i = 0; i < (int)objects.size(); i++)
    {
        VerletObject *obj1 = objects[i];
        if (!obj1->active)
            continue;

        for (int j = i + 1; j < (int)objects.size(); j++)
        {
            VerletObject *obj2 = objects[j];
            if (!obj2->active)
                continue;

            float dist = Vector2Distance(obj1->position, obj2->position);

            if (dist < obj1->radius + obj2->radius)
            {
                Vector2 dir = obj1->position - obj2->position;
                Vector2 n = dir / dist;
                float overlap = obj1->radius + obj2->radius - dist;

                overlap *= 1.f / REPULSION;

                if (obj1->fixed && obj2->fixed)
                {
                    // entrambi fissi, non si fa nulla
                    continue;
                }
                else if (obj1->fixed)
                {
                    obj2->position = Vector2Subtract(obj2->position, Vector2Scale(n, overlap));
                }
                else if (obj2->fixed)
                {
                    obj1->position = Vector2Add(obj1->position, Vector2Scale(n, overlap));
                }
                else
                {
                    obj1->position = Vector2Add(obj1->position, Vector2Scale(n, overlap / 2));
                    obj2->position = Vector2Subtract(obj2->position, Vector2Scale(n, overlap / 2));
                }
            }
        }
    }
}