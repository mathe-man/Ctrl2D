#pragma once
#include "RectangleOutline.h"
#include "Transform2D.h"
#include "GameObject.h"

class RectangleFill : public RectangleOutline {
public:
    RectangleFill(float width, float height, Color color)   :RectangleOutline(width, height, color) {}
    RectangleFill(Vector2 dimensions, Color color)                : RectangleOutline(dimensions, color) {}

    void Draw() override;
    const char* GetName() const override {return "RectangleFill";}
};


