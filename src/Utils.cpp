#include "Utils.h"

#include <iostream>

#include "Component.h"
#include "Ctrl2DApp.h"
#include "Ellipse.h"
#include "GameObject.h"
#include "raylib.h"
#include "imgui.h"
#include "Transform2D.h"


void Utils::MakeImGuiColorEdit4(Color* color)
{
    float colEdit[4] = {
        color->r / 255.0f,
        color->g / 255.0f,
        color->b / 255.0f,
        color->a / 255.0f
    };

    if (ImGui::ColorEdit4("color", colEdit)){
        color->r = (unsigned char)(colEdit[0] * 255);
        color->g = (unsigned char)(colEdit[1] * 255);
        color->b = (unsigned char)(colEdit[2] * 255);
        color->a = (unsigned char)(colEdit[3] * 255);
    }
}

void Utils::MakeImGuiColorEdit3(Color* color)
{
    float colEdit[3] = {
        color->r / 255.0f,
        color->g / 255.0f,
        color->b / 255.0f
    };

    if (ImGui::ColorEdit3("color", colEdit)){
        color->r = (unsigned char)(colEdit[0] * 255);
        color->g = (unsigned char)(colEdit[1] * 255);
        color->b = (unsigned char)(colEdit[2] * 255);
    }
}


// TODO Fix compilation error: undefined reference to `Utils::icon_font'
/*
void Utils::MakeImGuiIconText(const char* icon_unicode, const char* text)
{
    LoadIconFont();
    //ImGui::Text((const char*))
    ImGui::Begin("Settings");
    ImGui::PushFont(icon_font);
    ImGui::Text(reinterpret_cast<const char*>(u8"\uEA86")); ImGui::PopFont();ImGui::SameLine();
    ImGui::Text("Adaef");

    ImGui::End();
}

void Utils::LoadIconFont(bool forceLoading)
{
    if (Utils::iconFont == nullptr && !forceLoading)
        return;

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontDefault();
    ImFontConfig iconsConfig;
    iconsConfig.MergeMode = true;   iconsConfig.PixelSnapH = true;
    static const ImWchar icon_ranges[] = { 0xE000, 0xF8FF, 0};

    icon_font = io.Fonts->AddFontFromFileTTF(R"(..\..\assets\Phosphor.ttf)", 20.0f, &iconsConfig, icon_ranges);
}

*/



class DemoScriptComponent : public Component
{
public:
    float speed = 100.0f;
    void Update() override
    {
        float dt = GetFrameTime(); // DeltaTime
        Vector2 move {0, 0};
        if (IsKeyDown(KEY_LEFT))  move.x    -= 1 * speed * dt;
        if (IsKeyDown(KEY_RIGHT)) move.x    += 1 * speed * dt;
        if (IsKeyDown(KEY_UP))    move.y    -= 1 * speed * dt;
        if (IsKeyDown(KEY_DOWN))  move.y    += 1 * speed * dt;

        Transform2D* t = owner->GetComponent<Transform2D>();
        if (t)
        {
            t->setPosition(t->getPosition() + move);
        }
    }

    void Inspect() override
    {
        ImGui::DragFloat("speed", &speed, 0.1f);
    }
    const char* GetName() const override {return "DemoComponent";}
};
void Utils::ShowDemoApp()
{
    Ctrl2DApp app = Ctrl2DApp();

    Scene scene = Scene(WHITE);

    GameObject* obj =scene.CreateObject("My Object");
    obj->AddComponent<DemoScriptComponent>();
    obj->GetComponent<Transform2D>()->SubscrineToEvent<TransformPositionChangedEvent>(
        [](TransformPositionChangedEvent e)
        {
            std::cout << "Position changed to x:" << e.newValue.x
                                        << ", y:" << e.newValue.y << std::endl;
        });

    obj->AddComponent<EllipseOutline>(50, 50, GREEN);

    app.RunEditor(&scene);
}
