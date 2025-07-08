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
};



