#pragma once
#include "../Core/Scene.h"

class Ctrl2DApp {
    /// <summary>True if a raylib window (and ImGui) have been inited</summary>
    bool isInited = false;



public:
    /// <summary>
    /// Create a new Ctrl2DApp to work with a scene
    /// </summary>
    /// <param name="immediateInit">When true the app will immediately init itself, you will not need to call Init()</param>
    /// <seealso cref="Init"/>
    /// <param name="windowSize">The window size with x for width and y for height. The window is resizable</param>
    /// <param name="title">The title of the window</param>
    /// <param name="darkTheme">The dark theme only affect ImGui (When running Editor)</param>
     explicit Ctrl2DApp(bool immediateInit = true, Vector2 windowSize = Vector2{1280, 720}, const char* title = "Ctrl2D App")
        {if (immediateInit) Init(windowSize, title, true);}

    /// <summary> Initiate a window for this app </summary>
    /// <param name="windowSize">The window size with x for width and y for height.</param>
    /// <param name="title">The title of the window</param>
    /// <param name="darkTheme">The dark theme only affect ImGui (When running Editor)</param>
    /// <param name="forceInit">Will force initialization of a new window when the app has already created one</param>
    /// <remarks>The window is resizable</remarks>
    void Init(Vector2 windowSize = Vector2{1280, 720}, const char* title = "Ctrl2D App", bool forceInit = false);

    /// <returns>True if the app has already inited a window</returns>
    bool IsInited()     const   {return isInited;}


    /// <summary>Run a scene into the app window,
    /// no Editor/GUI is provided to make change. Use this mode to make a release of your app.
    /// </summary>
    /// <param name="scene">The scene to run</param>
    /// <param name="shutdownAtEnd">The app will shutdown is window itself at the end</param>
    void RunScene(Scene* scene,  bool shutdownAtEnd = true);

    /// <summary>Close the window of this app</summary>
    void Shutdown();
};


