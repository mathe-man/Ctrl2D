#include "Components.h"
#include "../Core/GameObject.h"


void EllipseFill::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawEllipse((int)t->getPosition().x, (int)t->getPosition().y, width * t->getScale().x, height * t->getScale().y, color);
}
