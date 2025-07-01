#include "Utils.h"

#include <iostream>

#include "imgui.h"


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