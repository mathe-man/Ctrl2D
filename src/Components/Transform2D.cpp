#include "Transform2D.h"
#include "imgui.h"


void Transform2D::Inspect()
{
    ImGui::SeparatorText(GetName());
    ImGui::DragFloat2("position", &position.x, 1.0f, -1000, 1000);
    ImGui::DragFloat("rotation", &rotation, 1.0f, -360, 360);
    ImGui::DragFloat2("scale", &scale.x, 0.25f, -100, 100);

}

