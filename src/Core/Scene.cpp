#include "imgui.h"
#include "Scene.h"
#include "Transform2D.h"

GameObject* Scene::CreateObject(const std::string& name, bool selectNewObject)
{
    auto obj = std::make_unique<GameObject>(name, this);
    obj->AddComponent<Transform2D>();
    objects.emplace_back(std::move(obj));
    if (selectNewObject) selected = objects.back().get();
    return objects.back().get();
}

bool Scene::RemoveObject(GameObject* object)
{
    for (auto it = objects.begin(); it != objects.end(); ++it)
        if (it->get() == object)
        {
            if (object == selected) selected = nullptr;

            it->reset();
            objects.erase(it);
            return true;
        }

    return false;
}
bool Scene::RemoveObject(const int index)
{
    if (index >= objects.size())
        return false;

    if (objects.at(index).get() == selected) selected = nullptr;

    objects.erase(objects.begin() + index);
    return true;
}



void Scene::Awake()
{
    eventDispatcher.Emit(SceneAwakeEvent{});
    for (auto& o : objects)
        o->Awake();
}

void Scene::Start()
{
    eventDispatcher.Emit(SceneStartEvent{});
    for (auto& o : objects)
        o->Start();
}

void Scene::Update()
{
    eventDispatcher.Emit(SceneUpdateEvent{});
    UpdateTextureSize();
    UpdateCameraOffset();
    for (auto& o : objects)
        o->Update();
}

void Scene::Draw()
{
    eventDispatcher.Emit(SceneDrawEvent{});

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

