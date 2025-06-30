#pragma once
#include "../Core/Component.h"
#include "raylib.h"


class RectangleOutline : public Component {
public:
    float width, height;
    Color color{};

    RectangleOutline(float width, float height, Color color);
    RectangleOutline(Vector2 dimensions, Color color);
    const char* GetName() const override {return "RectangleOutline";}

    void Draw() override;

    void Inspect() override;
};
