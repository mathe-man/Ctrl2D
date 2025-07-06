#pragma once
#include "../ECS/Component.h"
#include "raylib.h"

/** @brief Only draw the outline of an ellipse */
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


/** @brief Draw a filled ellipse*/
class EllipseFill : public EllipseOutline {
public:
    EllipseFill(float width, float height, Color color)
    : EllipseOutline(width, height, color) {}

    EllipseFill(Vector2 dimensions, Color color)
    : EllipseOutline(dimensions, color) {}


    void Draw() override;

    const char* GetName() const override {return "EllipseFill";}
};