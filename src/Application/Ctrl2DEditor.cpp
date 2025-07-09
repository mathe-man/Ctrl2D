#include "Ctrl2DEditor.h"

#include <iostream>

#include "imgui.h"
#include "rlImGui.h"


void Ctrl2DEditor::Init(Vector2 windowSize, const char* title, bool darkTheme, bool forceInit)
{
    if (inited && ! forceInit)
        return;

    // === Setup Raylib, Dear ImGui
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowSize.x, windowSize.y, title);
    rlImGuiSetup(darkTheme);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    darkTheme = darkTheme;
    inited = true;
}

void Ctrl2DEditor::Shutdown()
{
    if (!inited)
        return;

    rlImGuiShutdown();
    CloseWindow();
    inited = false;
}



void Ctrl2DEditor::RunEditor(Scene* scene, const bool shutdownAtEnd)
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

void Ctrl2DEditor::DrawEditor(Scene* scene)
{
    CreateMainDockSpace();
    ImGui::ShowDemoWindow();


    DrawSceneControlPanel(scene);
    DrawObjectInspector(scene);
}


void Ctrl2DEditor::DrawSceneControlPanel(Scene* scene)
{
    ImGui::Begin("Scene control panel");
    ImGui::SeparatorText("Scene infos");

    ImGui::Text("%zu objects in scene", scene->objects.size());
    ImGui::Text("Scene running at %d fps", GetFPS());


    if (ImGui::CollapsingHeader("Camera2D"))
    {
        if (ImGui::BeginCombo("drawing target", Scene::GetDrawingTargetName(scene->drawingTarget), ImGuiComboFlags_WidthFitPreview)) {
            for (int i = 0; i < 4; i++)
            {
                bool is_selected = SceneDrawingTarget(i) == scene->drawingTarget;
                if (ImGui::Selectable(Scene::GetDrawingTargetName(SceneDrawingTarget(i)), is_selected))
                    scene->drawingTarget = SceneDrawingTarget(i);

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
        ImGui::EndCombo();
    }

        ImGui::DragFloat2("offset", &scene->renderCamera.offset.x, 1, -2000, 2000);
        ImGui::DragFloat2("target", &scene->renderCamera.target.x, 2.5f, -500, 500);
        ImGui::DragFloat("rotation", &scene->renderCamera.rotation, 0.5f, 0, 360);
        ImGui::DragFloat("zoom", &scene->renderCamera.zoom, 0.05f, 0.01, 15);
    }


    if (ImGui::CollapsingHeader("Objects"))
    {
        ImGui::Button("Create Object");
        ValidNameInput("##name",
            [scene](const char* name)
            { scene->CreateObject(name); }
            );



        // Show scene objects
        for (auto& obj : scene->objects) {
            if (ImGui::Selectable(obj->name.c_str(), scene->selected == obj.get())) {
                scene->selected = obj.get();
            }
            GameObjectInterations(obj.get());

        }
    }

    ImGui::End();
}

void Ctrl2DEditor::DrawObjectInspector(Scene* scene)
{
    ImGui::Begin("Object Inspector");

    if (scene->selected) {
        GameObject* s = scene->selected;


        ImGui::Text("Game Object: %s", s->name.c_str());
        ImGui::Text("With %zu components", s->components.size());

        // Add a new component
        static int comp_selected_index = 0;
        auto comps = getComponentsTypesNames();
        if (ImGui::Button("Add new component"))
            // Add a new instance of the selected component to the GameObject
                s->AddComponent(getComponentsTypes()[comp_selected_index]());

        ImGui::SameLine();
        if (ImGui::BeginCombo("##selectionCombo", comps[comp_selected_index], ImGuiComboFlags_WidthFitPreview))
        {
            for (int i = 0; i < comps.size(); i++)
            {
                const bool is_selected = (i == comp_selected_index);
                if (ImGui::Selectable(comps[i], is_selected))
                    comp_selected_index = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        s->Inspect();
    }
    else ImGui::Text("No selected object");

    ImGui::End();
}

bool Ctrl2DEditor::ValidNameInput(const char* label, std::function<void(const char*)> OnValidInput, ImGuiPopupFlags flags)
{
    static char input[64];
    bool EnterPressedOnInput = false;

    if (ImGui::BeginPopupContextItem(label, flags))
    {
        ImGui::SetKeyboardFocusHere();

        EnterPressedOnInput = ImGui::InputText("##NameInput", input, sizeof(input),
                                                                ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll);


        // Show tips if the input is hovered
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_Stationary))
            ImGui::SetTooltip("Enter a name valid name"
                              "The name should not be empty or start with a blank space");


        // A name is valid if it's not empty and do not start with a blank space
        const bool IsNameValid = input[0] != '\0' && input[0] != ' ';
        // Create object if enter is pressed and the name is valid
        if (EnterPressedOnInput && IsNameValid) {
            OnValidInput(input);

            input[0] = '\0';
            ImGui::CloseCurrentPopup();
        }
        // Close the popup if the field is empty
        else if (EnterPressedOnInput){
            ImGui::CloseCurrentPopup();
            input[0] = '\0';
        }

        ImGui::EndPopup();
    }

    return EnterPressedOnInput;
}

void Ctrl2DEditor::GameObjectInterations(GameObject* obj)
{
    if (ImGui::BeginPopupContextItem(obj->name.c_str()))
    {
        if (ImGui::Button("Delete"))
        {
            obj->scene->RemoveObject(obj);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}




void Ctrl2DEditor::CreateMainDockSpace()
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



using ComponentConstructor = Component* (*)();

void Ctrl2DEditor::RegisterComponentTypeToEditor(ComponentConstructor constructor)
{
    // Avoid duplicating
    for (int i = 0; i < componentsTypes.size(); i++)
        if (constructor()->GetName() == componentsTypesNames[i] ||
            constructor == componentsTypes[i])
            return;

    componentsTypes.push_back(constructor);
    componentsTypesNames.push_back(constructor()->GetName());
}
// define static properties
std::vector<ComponentConstructor>   Ctrl2DEditor::componentsTypes;
std::vector<const char*>            Ctrl2DEditor::componentsTypesNames;