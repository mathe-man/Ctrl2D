#include "../Core/Component.h"
#include "raylib.h"

#pragma once

class Transform2D : public Component {
public:
    Vector2 position = {0, 0};
    float rotation = 0;
    Vector2 scale = {1, 1};

    void Inspect() override;
    const char* GetName() const override {return "Transform2D";}
};

