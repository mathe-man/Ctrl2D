#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "GameObject.h"

enum SceneDrawingTarget : char
{
    SceneDrawingTarget_NoSpecialTarget,
    SceneDrawingTarget_Camera,
    SceneDrawingTarget_Texture,
    SceneDrawingTarget_CameraAndTexture
};


class Scene {
public:
    std::vector<std::unique_ptr<GameObject>> objects;
    GameObject* selected = nullptr;

    Color backgroundColor{};
    SceneDrawingTarget drawingTarget = SceneDrawingTarget_Camera;

    RenderTexture2D renderTexture = LoadRenderTexture(512, 512);
    Camera2D        renderCamera  = { 0 };


    Scene(Color backgroundColor = DARKGRAY)
    {
        objects = std::vector<std::unique_ptr<GameObject>>();
        selected = nullptr;
        this->backgroundColor = backgroundColor;

        renderCamera.target     = {0,0};
        renderCamera.rotation   = 0.0f;
        renderCamera.zoom       = 1.0f;

        UpdateCameraOffset();
    }

    GameObject* CreateObject(const std::string& name);

    void Awake();
    void Start();
    void Update();
    void Draw() const;

    bool DrawingTargetUseCamera() const
    {
        return drawingTarget == SceneDrawingTarget_Camera ||
            drawingTarget == SceneDrawingTarget_CameraAndTexture;
    }
    bool DrawingTargetUseTexture() const
    {
        return  drawingTarget == SceneDrawingTarget_Texture ||
                drawingTarget == SceneDrawingTarget_CameraAndTexture;
    }

    static const char* GetDrawingTargetName(SceneDrawingTarget target)
    {
        switch (target)
        {
        case SceneDrawingTarget_NoSpecialTarget : return "No special target";
        case SceneDrawingTarget_Camera          : return "Camera";
        case SceneDrawingTarget_Texture         : return "Texture";
        case SceneDrawingTarget_CameraAndTexture: return "Camera & Texture";
        }
        return nullptr;
    }

private:
    void UpdateTextureSize();

    void UpdateCameraOffset();

    static void CreateMainDockSpace();
};

