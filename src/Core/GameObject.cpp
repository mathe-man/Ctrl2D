#include "GameObject.h"

#include "imgui.h"


void GameObject::Awake()
{
    for (auto& comp : components)
        comp->Awake();
}

void GameObject::Start()
{
    for (auto& comp : components)
        comp->Start();
}

void GameObject::Update()
{
    for (auto& comp : components)
        comp->Update();
}

void GameObject::Draw()
{
        for (auto& comp : components)
            comp->Draw();
}
void GameObject::Inspect()
{
    ImGui::Text("Game Object: %s", name.c_str());
    ImGui::Text("With %zu components", components.size());
    for (auto& comp : components)
        comp->Inspect();
    ImGui::Separator();
}
