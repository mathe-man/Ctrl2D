#include "RectangleFill.h"
#include "GameObject.h"


void RectangleFill::Draw()
{
    Transform2D* t = owner->GetComponent<Transform2D>();
    if (t) DrawRectangle((int)t->getPosition().x, (int)t->getPosition().y, int(width * t->getScale().x), int(height * t->getScale().y), color);
}
