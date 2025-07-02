#include "Ctrl2DApp.h"
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

    while (!WindowShouldClose())
    {
        // Update everything in scene
        scene->Update();

        // Draw
        BeginDrawing();
            scene->Draw();

        // Draw - GUI (e.g. Inspector)
        rlImGuiBegin();
            DrawEditor(scene);
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

    rlImGuiShutdown();
    CloseWindow();
    isInited = false;
}


void Ctrl2DApp::DrawEditor(Scene* scene)
{
    CreateMainDockSpace();


    ImGui::Begin("Scene control panel");
    ImGui::SeparatorText("Scene infos");

    ImGui::Text("%zu objects in scene", scene->objects.size());
    ImGui::Text("Scene running at %d fps", GetFPS());

    const SceneDrawingTarget targets[] = {
        SceneDrawingTarget_NoSpecialTarget,
        SceneDrawingTarget_Camera,
        SceneDrawingTarget_Texture,
        SceneDrawingTarget_CameraAndTexture
    };

    if (ImGui::BeginCombo("drawing target", Scene::GetDrawingTargetName(scene->drawingTarget))) {
        for (int i = 0; i < std::size(targets); i++)
        {
            bool is_selected = (targets[i] == scene->drawingTarget);
            if (ImGui::Selectable(Scene::GetDrawingTargetName(targets[i]), is_selected))
                scene->drawingTarget = targets[i];

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }


    if (ImGui::CollapsingHeader("Camera2D"))
    {
        ImGui::DragFloat2("offset", &scene->renderCamera.offset.x, 1, -2000, 2000);
        ImGui::DragFloat2("target", &scene->renderCamera.target.x, 2.5f, -500, 500);
        ImGui::DragFloat("rotation", &scene->renderCamera.rotation, 0.5f, 0, 360);
        ImGui::DragFloat("zoom", &scene->renderCamera.zoom, 0.05f, 0.01, 15);
    }



    if (ImGui::CollapsingHeader("Objects"))
    {
        for (auto& obj : scene->objects) {
            if (ImGui::Selectable(obj->name.c_str(), scene->selected == obj.get())) {
                scene->selected = obj.get();
            }
        }
    }

    ImGui::End();


    if (scene->selected) {

        ImGui::Begin("Inspector");
        scene->selected->Inspect();
        ImGui::End();

    }
}

void Ctrl2DApp::CreateMainDockSpace()
{
    // Get Raylib window size
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    // Flags to make this window entirely invisible
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground;

    // Remove border effects
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("Main dockspace window", nullptr, window_flags);
    ImGui::PopStyleVar(2);

    // Create dockspace
    ImGuiID dockspace_id = ImGui::GetID("Main dockspace");
    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();
}
