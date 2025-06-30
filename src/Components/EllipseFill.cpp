#include "Components.h"
#include "../Core/GameObject.h"


void EllipseFill::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawEllipse((int)t->position.x, (int)t->position.y, width * t->scale.x, height * t->scale.y, color);
}
