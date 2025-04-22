#include "modules/imports.h"
#include "item.h"

vector<Item *> items;
AssetLoader assetLoader;
char fpsText[32];
Item *picked = nullptr;
Background background;
VerletSolver verletSolver;

void AddRandomItems(int qta);
void Draw();
void Update();
void Cleanup();

int main()
{
    srand(time(0));

    const Color bg = {119, 119, 119, 255};

    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    assetLoader.loadTextures();
    assetLoader.loadSounds();

    background.texture = assetLoader.getTexture("stone");
    background.scale = 5;

    verletSolver.constraint = {0.f, 0.f, screenWidth, screenHeight};

    AddRandomItems(100);

    while (!WindowShouldClose())
    {
        Update();

        BeginDrawing();
        ClearBackground(bg);
        Draw();
        EndDrawing();
    }

    CloseWindow();
    Cleanup();

    return 0;
}

void AddRandomItems(int qta)
{
    static const vector<string> gemTypes = {
        "ruby", "amber", "topaz", "emerald", "jade",
        "sapphire", "diamond", "amethyst", "rose_quartz"};

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < qta; i++)
    {
        int index = rand() % gemTypes.size();
        Item *item = new Item(gemTypes[index]);
        items.push_back(item);

        verletSolver.AddObject(item->verlet);
    }
}

void Draw()
{
    background.Draw();

    for (int i = 0; i < (int)items.size(); i++)
    {
        items.at(i)->DrawShadow();
    }
    for (int i = 0; i < (int)items.size(); i++)
    {
        items.at(i)->Draw();
    }

    int fps = GetFPS();
    sprintf(fpsText, "FPS: %d", fps);
    DrawText(fpsText, 10, 10, 20, WHITE);
}

void Update()
{
    background.offset.x += 2;
    background.offset.y += 2;

    if (IsMouseButtonDown(0) && picked == nullptr)
    {
        for (int i = (int)items.size() - 1; i >= 0; --i)
        {
            if (CheckCollisionPointCircle(GetMousePosition(), items.at(i)->position, items.at(i)->texture->height * items.at(i)->scale * 0.5f))
            {
                Item *selected = items.at(i);
                items.erase(items.begin() + i);
                items.push_back(selected);

                picked = items.back();
                picked->PickAnimation();
                break;
            }
        }
    }

    if (IsMouseButtonUp(0) && picked != nullptr)
    {
        picked = nullptr;
    }

    for (int i = 0; i < (int)items.size(); i++)
    {
        items.at(i)->Update(items.at(i) == picked);
    }

    verletSolver.Update();
}

void Cleanup()
{
    for (auto &item : items)
    {
        delete item;
    }
    items.clear();
}
