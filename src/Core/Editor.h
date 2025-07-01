#pragma once
#include "Scene.h"

class Ctrl2DApp {
    bool isInited = false;
    bool isDarkTheme = true;

public:
    Ctrl2DApp(bool immediateInit = false, Vector2 windowSize = Vector2{720, 720}, const char* title = "Ctrl2D App", bool darkTheme = true)
        {if (immediateInit) Init(windowSize, title, darkTheme, true);}

    void Init(Vector2 windowSize = Vector2{720, 720}, const char* title = "Ctrl2D App", bool darkTheme = true, bool forceInit = false);

    bool IsInited()     const   {return isInited;}
    bool IsDarkTheme()  const   {return isDarkTheme;}

    void RunEditor(Scene* scene, bool shutdownAtEnd = true);
    void RunScene(Scene* scene,  bool shutdownAtEnd = true);

    void Shutdown();
};


