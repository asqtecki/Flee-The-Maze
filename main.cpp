#include <raylib.h>
#include <iostream>
#include "include/Game.hpp"
#include <cstdlib>
using namespace std;

struct Screen {
    const int width = 1280;
    const int height = 720;
};

int main() {
    srand(time(0));
    Screen s;
    InitWindow(s.width, s.height, "Flee the Maze!");
    DisableCursor();
    SetTargetFPS(60);
    Texture2D wall = LoadTexture("Graphics/wall.jpg");
    Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model wallModel = LoadModelFromMesh(cube);
    wallModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = wall;
    Game g(wallModel);
    while (!WindowShouldClose()) {
        g.Update();
        g.Draw();
    }
    UnloadModel(wallModel);
    UnloadTexture(wall);
    CloseWindow();
}