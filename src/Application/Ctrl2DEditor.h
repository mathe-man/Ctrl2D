#pragma once
#include "imgui.h"
#include "Scene.h"



class Ctrl2DEditor {
    bool inited = false;
    bool darkTheme = true;

    // Editor drawing
    void DrawEditor(Scene* scene);
    // Editor windows
        void DrawSceneControlPanel(Scene* scene);
        void DrawObjectInspector(Scene* scene);
        bool ValidNameInput(const char* label, std::function<void(const char*)> OnValidInput, ImGuiPopupFlags flags = 0);

    static void CreateMainDockSpace();
public:
    Ctrl2DEditor(bool immediateInit = true, Vector2 windowSize = Vector2{1280,720}, const char* title = "Ctrl2D Editor", bool darkTheme = true){
        if (immediateInit) Init(windowSize, title, true, true);
    }

    void Init(Vector2 windowSize = Vector2{1280, 720}, const char* title = "Ctrl2D App", bool darkTheme = true, bool forceInit = false);

    bool isInited()     const { return inited;      }
    bool isDarkTheme()  const { return darkTheme;   }

    void RunEditor(Scene* scene, const bool shutdownAtEnd = true);

    void Shutdown();


    using ComponentConstructor = Component* (*)();
    static void RegisterComponentTypeToEditor(ComponentConstructor constructor);
    static std::vector<const char*> getComponentsTypesNames() {return componentsTypesNames;}
    static std::vector<ComponentConstructor> getComponentsTypes() {return componentsTypes;}
private:
    static std::vector<ComponentConstructor> componentsTypes;
    static std::vector<const char*> componentsTypesNames;

};


#define REGISTER_COMP(CLASSNAME)                                             \
namespace {                                                                     \
    Component* create_##CLASSNAME() { return new CLASSNAME; }                   \
    struct CLASSNAME##_registrar {                                              \
        CLASSNAME##_registrar() {                                               \
            Ctrl2DEditor::RegisterComponentTypeToEditor(create_##CLASSNAME);    \
        }                                                                       \
    };                                                                          \
static CLASSNAME##_registrar global_##CLASSNAME##_registrar;                    \
}


