#include "imports.h"
#include "item.h"

vector<Item> items;
AssetLoader assetLoader;
char fpsText[32];
Item *picked = nullptr;
Background background;

void AddRandomItems(int qta);
void Draw();
void Update();

int main()
{
    srand(time(0));

    const Color bg = {119, 119, 119, 255};

    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");

    assetLoader.loadTextures();
    assetLoader.loadSounds();

    background.texture = assetLoader.getTexture("stone");
    background.scale = 5;

    AddRandomItems(100);

    while (!WindowShouldClose())
    {
        Update();

        // Drawing
        BeginDrawing();
        ClearBackground(bg);
        Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void AddRandomItems(int qta)
{
    static const vector<string> gemTypes = {
        "ruby", "amber", "topaz", "emerald", "jade",
        "sapphire", "diamond", "amethyst", "rose_quartz"};

    srand(static_cast<unsigned>(time(nullptr))); // Inizializzazione rand

    for (int i = 0; i < qta; i++)
    {
        int index = rand() % gemTypes.size();
        Item item(gemTypes[index]);
        items.push_back(item);
    }
}

void Draw()
{
    background.Draw();

    for (int i = 0; i < (int)items.size(); i++)
    {
        items.at(i).DrawShadow();
    }
    for (int i = 0; i < (int)items.size(); i++)
    {
        items.at(i).Draw();
    }

    // FPS
    int fps = GetFPS();
    sprintf(fpsText, "FPS: %d", fps);
    DrawText(fpsText, 10, 10, 20, WHITE);
}

void Update()
{
    if (IsMouseButtonDown(0) && picked == nullptr)
    {
        for (int i = (int)items.size() - 1; i >= 0; --i)
        {
            if (CheckCollisionPointCircle(GetMousePosition(), items.at(i).position, items.at(i).texture->height * items.at(i).scale * 0.5f))
            {
                // Sposta in cima al vettore
                Item selected = items.at(i);
                items.erase(items.begin() + i);
                items.push_back(selected);

                picked = &items.back();
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
        items.at(i).Update(&items.at(i) == picked);
    }
}