#pragma once
#include "Scene.h"



class Ctrl2DEditor {
    bool inited = false;
    bool darkTheme = true;

    void DrawEditor(Scene* scene);
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
    static void RegisterComponentTypeToEditor(ComponentConstructor constructor){
        // Avoid duplicating
        for (int i = 0; i < componentsTypes.size(); i++)
            if (constructor()->GetName() == componentsTypesNames[i] ||
                constructor == componentsTypes[i])
                return;

        componentsTypes.push_back(constructor);
        componentsTypesNames.push_back(constructor()->GetName());
    }
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


