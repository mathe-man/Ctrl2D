#pragma once


class GameObject;

// ===== Base Component Class =====

class Component {
public:
    GameObject* owner;
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Inspect() = 0;
    virtual const char* GetName() const = 0;
    virtual ~Component() = default;
};

