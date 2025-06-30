#include "RectangleOutline.h"

#include "../Core/GameObject.h"
#include "imgui.h"


RectangleOutline::RectangleOutline(float width, float height, Color color)
{
    this->width = width;
    this->height = height;
    this->color = color;
}
RectangleOutline::RectangleOutline(Vector2 dimensions, Color color)
{
    this->width = dimensions.x;
    this->height = dimensions.y;
    this->color = color;
}



void RectangleOutline::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();

    if (t) DrawRectangleLines((int)t->position.x, (int)t->position.y, (int)width, (int)height, color);
}

void RectangleOutline::Inspect()
{
    ImGui::SeparatorText(GetName());

    ImGui::DragFloat("width", &width, 0.5f);
    ImGui::DragFloat("height", &width, 0.5f);

    // Convert Color into float[4] for ImGui
    float colEdit[4] = {
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
    };

    if (ImGui::ColorEdit4("Color", colEdit)){
        color.r = (unsigned char)(colEdit[0] * 255);
        color.g = (unsigned char)(colEdit[1] * 255);
        color.b = (unsigned char)(colEdit[2] * 255);
        color.a = (unsigned char)(colEdit[3] * 255);
    }
}
