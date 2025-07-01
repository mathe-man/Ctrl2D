// ==============================
// Simple 2D Engine
// GameObject -> Component based system
// Raylib for rendering
// ImGui for editor UI
// ==============================

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"


#include "GameObject.h"
#include "Scene.h"
#include "Components.h"



int main() {

    // === Setup Raylib, Dear ImGui
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Ctrl2D");
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


    // === Create and fill a new Scene with GameObjects
    Scene scene = Scene(WHITE);

    scene.CreateObject("Circle")
        ->AddComponent<EllipseOutline>(Vector2{50, 50}, VIOLET);

    GameObject* rect = scene.CreateObject("Rectangle");
    rect->AddComponent<RectangleFill>(Vector2{50, 70}, BLUE);

    rect->GetComponent<Transform2D>()->SetPosition(Vector2{400, 200});

    while (!WindowShouldClose()) {
        // Update everything in scene
        scene.Update();

        // Draw
        BeginDrawing();
            scene.Draw();

        // Draw - GUI (e.g. Inspector)
        rlImGuiBegin();
            scene.DrawEditor();
        rlImGuiEnd();

        EndDrawing();
    }


    // Close ImGui and Raylib
    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
