#pragma once
#include "imgui.h"
#include "raylib.h"

class Utils{
private:
    static ImFont* icon_font;
    static void LoadIconFont(bool forceLoading = false) {}

public:
    static void MakeImGuiColorEdit4(Color* color);
    static void MakeImGuiColorEdit3(Color* color);


    static void MakeImGuiIconText(const char* icon_unicode, const char* text) {}
};