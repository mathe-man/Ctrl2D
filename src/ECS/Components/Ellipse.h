#pragma once
#include "Ctrl2DEditor.h"
#include "../ECS/Component.h"
#include "raylib.h"

/** @brief Only draw the outline of an ellipse */
class EllipseOutline : public Component {
public:
    float width, height;
    Color color{};

    EllipseOutline(float width = 10, float height = 10, Color color = BLACK);
    EllipseOutline(Vector2 dimensions, Color color);
    const char* GetName() const override {return "EllipseOutline";}

    void Inspect() override;
    void Draw() override;
};
REGISTER_COMP(EllipseOutline)

/** @brief Draw a filled ellipse*/
class EllipseFill : public EllipseOutline {
public:
    EllipseFill(float width = 10, float height = 10, Color color = BLACK)
    : EllipseOutline(width, height, color) {}

    EllipseFill(Vector2 dimensions, Color color)
    : EllipseOutline(dimensions, color) {}


    void Draw() override;

    const char* GetName() const override {return "EllipseFill";}
};
REGISTER_COMP(EllipseFill)