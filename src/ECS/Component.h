#pragma once


class GameObject;

// ===== Base Component Class =====

class Component {
public:
    /** @brief The GameObject this Component is attached to*/
    GameObject* owner;
    /** @brief Is called when the owner of this component call Awake()*/
    virtual void Awake  ()  {}
    /** @brief Is called when the owner of this component call Start()*/
    virtual void Start  ()  {}
    /** @brief Is called when the owner of this component call Update()*/
    virtual void Update ()  {}
    /** @brief Is called to draw to the scene.
     * @remark Use Raylib drawing methods*/
    virtual void Draw   ()  {}
    /** @brief Is called to draw this component in the inspector
     * @remarks This is called in a ImGui frame, so use rlImGui or ImGui methods.
     * @remarks The Editor already create an ImGui window using ImGui::Begin().
     * @remarks Create a new ImGui window only if it's necessary.
     */
    virtual void Inspect() = 0;

    virtual const char* GetName() const = 0;
    virtual ~Component() = default;
};

