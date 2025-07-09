#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Component.h"


class Scene;

/**
 * @brief Represent a GameObject, member of a scene.
 */
class GameObject {
public:
    /**
     * @brief The name of this GameObject.
     * @remarks For better readabilty and Editor (when running the scene)
     * please avoid using the same name multiple time.
     */
    std::string name;
    /** @brief The scene containing this GameObject. */
    Scene* scene;
    /** @brief All the components of this GameObject. */
    std::vector<std::shared_ptr<Component>> components;

    /**
     * @brief Add a new component to the components of this GameObject.
     * @tparam T T
     * @param args The arguments given to the T component constructor.
     * @returns The newly created component.
     * @remarks The new component owner will be set to this.
     */
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    /**
     * @brief Get the first component of this type
     * @tparam T The wanted type of component.
     * @return The first component matching the T type.
     * found in this GameObject components list.
     * @returns A nullptr if no matching component has been found.
     */
    template<typename T>
    T* GetComponent();

    /** @brief Is called before the start of the app loop       */
    void Awake  ();
    /** @brief Is called at the first frame of the app          */
    void Start  ();
    /** @brief Is called at each frame of the app               */
    void Update ();
    /** @brief Is called to draw this GameObject on the scene   *
     *  @remarks This is called in a raylib frame, so use adapted drawing method.
     *  @remarks The drawing target depend on this GameObject's scene render camera.
     */
    void Draw   ();
    /** @brief Is called to draw this GameObject inspector in the Editor.
     * @remarks This is called in a ImGui frame, so use rlImGui or ImGui methods.
     * @remarks The Editor already create an ImGui window using ImGui::Begin().
     * @remarks Create a new ImGui window only if it's necessary.
     */
    void Inspect();
protected:
    void AddComponent(Component* component)
    {
        for (const auto& comp : components)
            if (comp.get()->GetName() == component->GetName())
                return;

        auto newComponent = std::shared_ptr<Component>(component);
        newComponent->owner = this;
        components.push_back(newComponent);
    }
    friend class Ctrl2DEditor;
};




template <typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args)
{
    if (GetComponent<T>() != nullptr)
        return nullptr;

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
