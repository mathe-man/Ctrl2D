#include "Ctrl2DApp.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "rlImGui.h"
#include "raylib.h"

void Ctrl2DApp::Init(Vector2 windowSize, const char* title, bool forceInit)
{
    if (isInited && !forceInit)
        return;


    // === Setup Raylib
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowSize.x, windowSize.y, title);

    isInited = true;
}



void Ctrl2DApp::RunScene(Scene* scene, bool shutdownAtEnd)
{
    Init();

    while (!WindowShouldClose())
    {
        // Update everything in scene
        scene->Update();

        // Draw
        BeginDrawing();
            scene->Draw();

        EndDrawing();
    }

    // shutdow
    if (shutdownAtEnd)
        Shutdown();
}


void Ctrl2DApp::Shutdown()
{
    if (!isInited)
        return;

    CloseWindow();
    isInited = false;
}
