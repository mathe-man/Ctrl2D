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
#include "Editor.h"


int main() {
    //Create - Init a Ctrl2D app
    Ctrl2DApp app = Ctrl2DApp(true);

    // === Create and fill a new Scene with GameObjects
    Scene scene = Scene(WHITE);

    scene.CreateObject("Circle")
        ->AddComponent<EllipseOutline>(Vector2{50, 50}, VIOLET);

    GameObject* rect = scene.CreateObject("Rectangle");
    rect->AddComponent<RectangleFill>(Vector2{50, 70}, BLUE);

    rect->GetComponent<Transform2D>()->SetPosition(Vector2{400, 200});


    // Run the scene in the app
    app.RunEditor(&scene);
    std::cout << "Editor ended" << std::endl;
    app.RunScene(&scene);



    return 0;
}
