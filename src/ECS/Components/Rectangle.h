#pragma once
#include "../ECS/Component.h"
#include "raylib.h"

/** @brief A rectangle outline*/
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

/** @brief A filled rectangle*/
class RectangleFill : public RectangleOutline {
public:
    RectangleFill(float width, float height, Color color)   :RectangleOutline(width, height, color) {}
    RectangleFill(Vector2 dimensions, Color color)                : RectangleOutline(dimensions, color) {}

    void Draw() override;
    const char* GetName() const override {return "RectangleFill";}
};