#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Components.h"


class Scene;

class GameObject {
public:
    std::string name;
    Scene* scene;
    std::vector<std::unique_ptr<Component>> components;

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    template<typename T>
    T* GetComponent();

    void Awake  ();
    void Start  ();
    void Update ();
    void Draw   ();
    void Inspect();
};




template <typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args)
{
    T* comp = new T(std::forward<Args>(args)...);
    comp->owner = this;
    components.emplace_back(comp);
    return comp;
}


template <typename T>
T* GameObject::GetComponent()
{
    for (auto& c : components) {
        if (T* ptr = dynamic_cast<T*>(c.get())) return ptr;
    }
    return nullptr;
}
