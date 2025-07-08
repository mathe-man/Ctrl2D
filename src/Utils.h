#pragma once
#include "imgui.h"
#include "raylib.h"
#include "Scene.h"

class Utils{
private:
    static ImFont* icon_font;
    static void LoadIconFont(bool forceLoading = false) {}

public:
    static void MakeImGuiColorEdit4(Color* color);
    static void MakeImGuiColorEdit3(Color* color);


    static void MakeImGuiIconText(const char* icon_unicode, const char* text) {}


    static Scene* ShowDemoApp();
    static Scene* ShowDemoEditor();
};
