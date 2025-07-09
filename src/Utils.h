#pragma once
#include "imgui.h"
#include "raylib.h"
#include "Scene.h"

class Utils{
private:
    static ImFont* icon_font;
    static void LoadIconFont(bool forceLoading = false) {}

public:
    static void MakeImGuiColorEdit4(const char* label, Color* color);
    static void MakeImGuiColorEdit3(const char* label, Color* color);

    static const char* MakeImGuiUniqueLabel(const char* label = "", const Component* component = nullptr);


    static void MakeImGuiIconText(const char* icon_unicode, const char* text) {}


    static Scene* ShowDemoApp();
    static Scene* ShowDemoEditor();
};
