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
    for (auto& comp : components)
    {
        if (ImGui::CollapsingHeader(comp->GetName()))
            comp->Inspect();
        ImGui::Separator();
    }
}
