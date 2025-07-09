#include "Ellipse.h"


#include "imgui.h"
#include "../ECS/GameObject.h"
#include "Transform2D.h"
#include "../Utils.h"


EllipseOutline::EllipseOutline(float width, float height, Color color)
{
    this->width = width;
    this->height = height;
    this->color = color;
}
EllipseOutline::EllipseOutline(Vector2 dimensions, Color color)
{
    this->width = dimensions.x;
    this->height = dimensions.y;
    this->color = color;
}

void EllipseOutline::Inspect()
{
    ImGui::DragFloat(Utils::MakeImGuiUniqueLabel("width", this), &width, 0.5f, 0, 1000);
    ImGui::DragFloat(Utils::MakeImGuiUniqueLabel("height", this), &height, 0.5f, 0, 1000);

    // Convert Color into float[4] for ImGui
    Utils::MakeImGuiColorEdit4(Utils::MakeImGuiUniqueLabel("color", this), &color);
}

void EllipseOutline::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawEllipseLines((int)t->getPosition().x, (int)t->getPosition().y, width * t->getScale().x, height * t->getScale().y, color);
}


void EllipseFill::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawEllipse((int)t->getPosition().x, (int)t->getPosition().y, width * t->getScale().x, height * t->getScale().y, color);
}
