// ==============================
// Simple 2D Engine
// GameObject -> Component based system
// Raylib for rendering
// ImGui for editor UI
// ==============================

#include "Ctrl2DEditor.h"
#include "Utils.h"
class a : public Component
{
    const char* GetName() const override {return "aaAA";}
    void Inspect() override {ImGui::TextUnformatted(GetName());}
};
REGISTER_COMP(a)


int main() {

    Utils::ShowDemoEditor();

    return 0;
}
