#include "Scene.h"
#include "imgui.h"

GameObject* Scene::CreateObject(const std::string& name)
{
    auto obj = std::make_unique<GameObject>(name, this);
    obj->AddComponent<Transform2D>();
    objects.emplace_back(std::move(obj));
    return objects.back().get();
}

void Scene::Awake()
{
    for (auto& o : objects)
        o->Awake();
}

void Scene::Start()
{
    for (auto& o : objects)
        o->Start();
}

void Scene::Update()
{
    UpdateTextureSize();
    UpdateCameraOffset();
    for (auto& o : objects)
        o->Update();
}

void Scene::Draw() const
{
    if (DrawingTargetUseTexture())  BeginTextureMode(renderTexture);

    ClearBackground(backgroundColor);

    if (DrawingTargetUseCamera())   BeginMode2D(renderCamera);

    for (auto& o : objects)
        o->Draw();

    // Draw a dot to indicate the object position
    if (selected)
    {
        auto t = selected->GetComponent<Transform2D>();
        if (t) DrawCircle(t->getPosition().x, t->getPosition().y, 4, BLUE);
    }

    if (DrawingTargetUseCamera()) EndMode2D();

    if (DrawingTargetUseTexture())  EndTextureMode();
}







void Scene::UpdateTextureSize()
{
    if (!DrawingTargetUseTexture())
        return;

    // RenderTexture resizing
    int sWidth = GetScreenWidth();
    int sHeight = GetScreenHeight();
    if (sWidth != renderTexture.texture.width || sHeight != renderTexture.texture.height)
    {
        if (sWidth > 0 && sHeight > 0)
        {
            UnloadRenderTexture(renderTexture);
            renderTexture = LoadRenderTexture(sWidth, sHeight);
        }
    }
}
void Scene::UpdateCameraOffset()
{
    if (!DrawingTargetUseCamera())
        return;

    float xTargertedOffset = GetScreenWidth() / 2.0f;
    float yTargertedOffset = GetScreenHeight() / 2.0f;

    if (renderCamera.offset.x != xTargertedOffset) renderCamera.offset.x = xTargertedOffset;
    if (renderCamera.offset.y != yTargertedOffset) renderCamera.offset.y = yTargertedOffset;
}

