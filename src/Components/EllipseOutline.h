#pragma once
#include "Component.h"
#include "raylib.h"


class EllipseOutline : public Component {
public:
    float width, height;
    Color color{};

    EllipseOutline(float width, float height, Color color);
    EllipseOutline(Vector2 dimensions, Color color);
    const char* GetName() const override {return "EllipseOutline";}

    void Inspect() override;
    void Draw() override;
};
