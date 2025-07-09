#include "Transform2D.h"
#include "imgui.h"
#include "raymath.h"
#include "Utils.h"


void Transform2D::Inspect()
{
    auto pastPos = position;
    auto pastRot = rotation;
    auto pastScale = scale;


    // Show each fields, emit and event only if the value as changed
    if (ImGui::DragFloat2(Utils::MakeImGuiUniqueLabel("position", this), &position.x, 1.0f, -1000, 1000))
        events.Emit(TransformPositionChangedEvent{pastPos, position, Vector2Subtract(position, pastPos)});

    if (ImGui::DragFloat(Utils::MakeImGuiUniqueLabel("rotation", this), &rotation, 1.0f, -360, 360))
        events.Emit(TransformRotationChangedEvent{pastRot, rotation, rotation - pastRot});

    if (ImGui::DragFloat2(Utils::MakeImGuiUniqueLabel("scale", this), &scale.x, 0.25f, -100, 100))
        events.Emit(TransformScaleChangedEvent{pastScale, scale, scale - pastScale});



}

