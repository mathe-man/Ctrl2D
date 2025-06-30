#pragma once
#include "EllipseOutline.h"


class EllipseFill : public EllipseOutline {
public:
    EllipseFill(float width, float height, Color color)
    : EllipseOutline(width, height, color) {}

    EllipseFill(Vector2 dimensions, Color color)
    : EllipseOutline(dimensions, color) {}


    void Draw() override;
    const char* GetName() const override {return "EllipseFill";}
};
