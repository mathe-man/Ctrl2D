#pragma once
#include "Ctrl2DEditor.h"
#include "../ECS/Component.h"
#include "raylib.h"

/** @brief A rectangle outline*/
class RectangleOutline : public Component {
public:
    float width, height;
    Color color{};

    RectangleOutline(float width = 10, float height = 10, Color color = BLACK);
    RectangleOutline(Vector2 dimensions, Color color);
    const char* GetName() const override {return "RectangleOutline";}

    void Draw() override;

    void Inspect() override;
};
REGISTER_COMP(RectangleOutline)

/** @brief A filled rectangle*/
class RectangleFill : public RectangleOutline {
public:
    RectangleFill(float width = 10, float height = 10, Color color = BLACK)   :RectangleOutline(width, height, color) {}
    RectangleFill(Vector2 dimensions, Color color)                : RectangleOutline(dimensions, color) {}

    void Draw() override;
    const char* GetName() const override {return "RectangleFill";}
};
REGISTER_COMP(RectangleFill)