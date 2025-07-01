#include "EllipseOutline.h"

#include "../Core/GameObject.h"
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

void EllipseOutline::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawEllipseLines((int)t->getPosition().x, (int)t->getPosition().y, width * t->getScale().x, height * t->getScale().y, color);
}


