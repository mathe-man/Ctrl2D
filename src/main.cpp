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
#include "Ctrl2DApp.h"


int main() {
    //Create - Init a Ctrl2D app
    Ctrl2DApp app;
    app = Ctrl2DApp(true);

    // === Create and fill a new Scene with GameObjects
    Scene scene = Scene(WHITE);

    scene.CreateObject("Circle")
        ->AddComponent<EllipseOutline>(Vector2{50, 50}, VIOLET);

    GameObject* rect = scene.CreateObject("Rectangle");
    rect->AddComponent<RectangleFill>(Vector2{50, 70}, BLUE);

    auto* rectTrans = rect->GetComponent<Transform2D>();
    rectTrans->SetPosition(Vector2{400, 200});

    // Subscribe to the position changed event
    rectTrans->SubscrineToEvent<TransformPositionChangedEvent>(
    [](TransformPositionChangedEvent e)
    {
        std::cout<< "New value: (" << e.newValue.x << ";" << e.newValue.y << ")" << std::endl;
    });


    // Run the scene in the app
    app.RunEditor(&scene);
    std::cout << "Editor ended" << std::endl;



    return 0;
}
