#include "Event.h"
#include "Component.h"
#include "Ctrl2DEditor.h"
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

    EventDispatcher events = EventDispatcher();
public:
    Vector2 getPosition() {return position;}
    float   getRotation() {return rotation;}
    Vector2 getScale()    {return scale;}

    void setPosition(Vector2 newPosition){
        if (newPosition == position) return; // Admit that the position didn't change

        auto pastp = position;
        position = newPosition;
        events.Emit(TransformPositionChangedEvent{pastp, position, Vector2Subtract(position, pastp)});
    }
    void setRotation(float newRotation){
        if (newRotation == rotation) return; // Admit that the rotation didn't change

        auto pastr = rotation;
        rotation = newRotation;
        events.Emit(TransformRotationChangedEvent{pastr, rotation, rotation - pastr});
    }
    void setScale(Vector2 newScale){
        if (newScale == scale) return; // Admit that the scale didn't change

        auto pasts = scale;
        scale = newScale;
        events.Emit(TransformScaleChangedEvent{pasts, scale, scale - pasts});
    }
    void MovePosition(Vector2 distance) { setPosition(position + distance); }
    void MoveRotation(float distance)   { setRotation(rotation + distance); }
    void MoveScale(Vector2 distance)    { setScale(scale + distance);       }

    // Subscribe a function to the wanted event
    template<typename eventType>
    void SubscrineToEvent(std::function<void(const eventType&)> function) {events.Get<eventType>().subscribe(function);}

    void Inspect() override;
    const char* GetName() const override {return "Transform2D";}

};
REGISTER_COMP(Transform2D)
