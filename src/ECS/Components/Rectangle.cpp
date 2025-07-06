#include "Rectangle.h"

#include "../ECS/GameObject.h"
#include "imgui.h"
#include "Transform2D.h"
#include "Utils.h"


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

    if (t) DrawRectangleLines((int)t->getPosition().x, (int)t->getPosition().y, int(width * t->getScale().x), int(height * t->getScale().y), color);
}

void RectangleOutline::Inspect()
{
    ImGui::DragFloat("width", &width, 0.5f);
    ImGui::DragFloat("height", &height, 0.5f);

    Utils::MakeImGuiColorEdit4(&color);

}



void RectangleFill::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawRectangle((int)t->getPosition().x, (int)t->getPosition().y, int(width * t->getScale().x), int(height * t->getScale().y), color);
}