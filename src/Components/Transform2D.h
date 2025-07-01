#include "Event.h"
#include "Component.h"
#include "raylib.h"
#include "raymath.h"

#pragma once

struct TransformPositionChangedEvent    :   ValueChangeEvent<Vector2>   { using ValueChangeEvent::ValueChangeEvent; };
struct TransformScaleChangedEvent       :   ValueChangeEvent<Vector2>   { using ValueChangeEvent::ValueChangeEvent; };
struct TransformRotationChangedEvent    :   ValueChangeEvent<float>     { using ValueChangeEvent::ValueChangeEvent; };




class Transform2D : public Component {
private:
    Vector2 position = {0, 0};
    float rotation = 0;
    Vector2 scale = {1, 1};

public:
    Vector2 getPosition() {return position;}
    float   getRotation() {return rotation;}
    Vector2 getScale()    {return scale;}

    void SetPosition(Vector2 newPosition){
        events.Emit(TransformPositionChangedEvent{position, newPosition, newPosition});
        position = newPosition;
    }


    void Inspect() override;
    const char* GetName() const override {return "Transform2D";}
    EventDispatcher events = EventDispatcher();
};

