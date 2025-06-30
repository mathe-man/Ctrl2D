// ==============================
// Simple 2D Engine
// GameObject -> Component based system
// Raylib for rendering
// ImGui for editor UI
// ==============================

#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

#include "Scene.h"
#include "Components.h"
#include "GameObject.h"






// ===== Main Loop =====
int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Mini Unity Editor with Raylib and ImGui");
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    Scene scene = Scene(RAYWHITE);
    GameObject* obj1 = scene.CreateObject("Hollow Circle");
    obj1->AddComponent<EllipseOutline>(100, 50, RED);
    obj1->GetComponent<Transform2D>()->position = {200, 300};

    GameObject* obj2 = scene.CreateObject("Filled Circle");
    obj2->AddComponent<EllipseFill>(50, 100, GREEN);
    obj2->AddComponent<RectangleOutline>(50, 100, GREEN);
    obj2->GetComponent<Transform2D>()->position = {400, 300};

    while (!WindowShouldClose()) {
        // Update
        scene.Update();

        // Draw
        BeginDrawing();
            scene.Draw();

        // Draw - GUI
        rlImGuiBegin();
            scene.DrawEditor();
        rlImGuiEnd();

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
