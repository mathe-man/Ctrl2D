#include "Editor.h"
#include "imgui.h"
#include "rlImGui.h"
#include "raylib.h"

void Ctrl2DApp::Init(Vector2 windowSize, const char* title, bool darkTheme, bool forceInit)
{
    if (isInited && !forceInit)
        return;

    isDarkTheme = darkTheme;

    // === Setup Raylib, Dear ImGui
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowSize.x, windowSize.y, title);
    rlImGuiSetup(isDarkTheme);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    isInited = true;
}


void Ctrl2DApp::RunEditor(Scene* scene, bool shutdownAtEnd)
{
    Init();
    std::cout << WindowShouldClose() << std::endl;

    while (!WindowShouldClose())
    {
        // Update everything in scene
        scene->Update();

        // Draw
        BeginDrawing();
            scene->Draw();

        // Draw - GUI (e.g. Inspector)
        rlImGuiBegin();
            scene->DrawEditor();
        rlImGuiEnd();

        EndDrawing();
    }

    // shutdow
    if (shutdownAtEnd)
        Shutdown();
}


void Ctrl2DApp::RunScene(Scene* scene, bool shutdownAtEnd)
{
    Init();
    std::cout << WindowShouldClose() << std::endl;

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
    rlImGuiShutdown();
    CloseWindow();
    isInited = false;
}
