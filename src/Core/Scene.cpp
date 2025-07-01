#include "Scene.h"
#include "imgui.h"

GameObject* Scene::CreateObject(const std::string& name)
{
    auto obj = std::make_unique<GameObject>(name, this);
    obj->AddComponent<Transform2D>();
    objects.emplace_back(std::move(obj));
    return objects.back().get();
}

void Scene::Draw() const
{
    if (DrawingTargetUseTexture())  BeginTextureMode(renderTexture);

    ClearBackground(backgroundColor);

    if (DrawingTargetUseCamera())   BeginMode2D(renderCamera);

    for (auto& o : objects)
        o->Draw();

    if (DrawingTargetUseCamera()) EndMode2D();

    if (DrawingTargetUseTexture())  EndTextureMode();
}


void Scene::DrawEditor()
{
    CreateMainDockSpace();


    ImGui::Begin("Scene control panel");
    ImGui::SeparatorText("Scene infos");

    ImGui::Text("%zu objects in scene", objects.size());
    ImGui::Text("Scene running at %d fps", GetFPS());

    const SceneDrawingTarget targets[] = {
        SceneDrawingTarget_NoSpecialTarget,
        SceneDrawingTarget_Camera,
        SceneDrawingTarget_Texture,
        SceneDrawingTarget_CameraAndTexture
    };

    if (ImGui::BeginCombo("drawing target", GetDrawingTargetName(drawingTarget))) {
        for (int i = 0; i < std::size(targets); i++)
        {
            bool is_selected = (targets[i] == drawingTarget);
            if (ImGui::Selectable(GetDrawingTargetName(targets[i]), is_selected))
                drawingTarget = targets[i];

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }


    if (ImGui::CollapsingHeader("Camera2D"))
    {
        ImGui::DragFloat2("offset", &renderCamera.offset.x, 1, -2000, 2000);
        ImGui::DragFloat2("target", &renderCamera.target.x, 2.5f, -500, 500);
        ImGui::DragFloat("rotation", &renderCamera.rotation, 0.5f, 0, 360);
        ImGui::DragFloat("zoom", &renderCamera.zoom, 0.05f, 0.01, 15);
    }



    if (ImGui::CollapsingHeader("Objects"))
    {
        for (auto& obj : objects) {
            if (ImGui::Selectable(obj->name.c_str(), selected == obj.get())) {
                selected = obj.get();
            }
        }
    }

    ImGui::End();


    if (selected) {

        ImGui::Begin("Inspector");
        selected->Inspect();
        ImGui::End();

    }
}



void Scene::UpdateTextureSize()
{
    if (!DrawingTargetUseTexture())
        return;

    // RenderTexture resizing
    int sWidth = GetScreenWidth();
    int sHeight = GetScreenHeight();
    if (sWidth != renderTexture.texture.width || sHeight != renderTexture.texture.height)
    {
        if (sWidth > 0 && sHeight > 0)
        {
            UnloadRenderTexture(renderTexture);
            renderTexture = LoadRenderTexture(sWidth, sHeight);
        }
    }
}
void Scene::UpdateCameraOffset()
{
    if (!DrawingTargetUseCamera())
        return;

    float xTargertedOffset = GetScreenWidth() / 2.0f;
    float yTargertedOffset = GetScreenHeight() / 2.0f;

    if (renderCamera.offset.x != xTargertedOffset) renderCamera.offset.x = xTargertedOffset;
    if (renderCamera.offset.y != yTargertedOffset) renderCamera.offset.y = yTargertedOffset;
}


void Scene::CreateMainDockSpace()
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
