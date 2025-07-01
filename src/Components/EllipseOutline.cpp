#include "EllipseOutline.h"

#include "imgui.h"
#include "GameObject.h"
#include "Transform2D.h"


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
    ImGui::SeparatorText(GetName());

    ImGui::DragFloat(std::string(std::string("width##") + GetName()).c_str(), &width, 0.5f, 0, 1000);
    ImGui::DragFloat(std::string(std::string("height##") + GetName()).c_str(), &height, 0.5f, 0, 1000);

    // Convert Color into float[4] for ImGui
    float colEdit[4] = {
        color.r / 255.0f,
        color.g / 255.0f,
        color.b / 255.0f,
        color.a / 255.0f
    };

    if (ImGui::ColorEdit4(std::string(std::string("height##") + GetName()).c_str(), colEdit)){
        color.r = (unsigned char)(colEdit[0] * 255);
        color.g = (unsigned char)(colEdit[1] * 255);
        color.b = (unsigned char)(colEdit[2] * 255);
        color.a = (unsigned char)(colEdit[3] * 255);
    }
}

void EllipseOutline::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawEllipseLines((int)t->getPosition().x, (int)t->getPosition().y, width * t->getScale().x, height * t->getScale().y, color);
}


