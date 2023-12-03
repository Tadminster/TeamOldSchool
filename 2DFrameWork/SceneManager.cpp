#include "framework.h"
#include "SceneManager.h"

SceneManager::~SceneManager()
{
    for (auto i = scenes.begin();
        i != scenes.end(); i++)
    {
        SafeDelete(i->second);
    }
    scenes.clear();
}

bool SceneManager::AddScene(SceneName key, Scene* value)
{
    auto iter = scenes.find(key);

    if (iter != scenes.end())
    {
        return false;
    }
    scenes[key] = value;

    return true;
}

bool SceneManager::DeleteScene(SceneName key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return false;
    }

    SafeDelete(iter->second);
    scenes.erase(iter);

    return true;
}

Scene* SceneManager::ChangeScene(SceneName key, float changingTime)
{
    Scene* temp = GetScene(key);
    currentSceneKey = key;

    if (temp)
    {
        nextScene = temp;
        this->changingTime = changingTime;

        if (changingTime <= 0.0f)
        {
            isChanging = true;
            //¾À ºÒ·¯¿Ã ¶§ 
            SafeRelease(currentScene);
            //¾À ¹Ù²ð ¶§
            nextScene->Init();
        }
    }
    return temp;
}

Scene* SceneManager::GetScene(SceneName key)
{
    auto iter = scenes.find(key);

    if (iter == scenes.end())
    {
        return nullptr;
    }

    return iter->second;
}

Scene* SceneManager::GetCurrentScene()
{
    return currentScene;
}

void SceneManager::Release()
{
    if (currentScene)currentScene->Release();
}

void SceneManager::Update()
{
    if (changingTime > 0.0f)
    {
        changingTime -= DELTA;

        if (changingTime <= 0.0f)
        {
            isChanging = true;
            SafeRelease(currentScene);
            nextScene->Init();
        }
    }


    if (isChanging)
    {
        currentScene = nextScene;
        isChanging = false;
    }
    currentScene->Update();
}

void SceneManager::LateUpdate()
{
    if (isChanging)return;
    currentScene->LateUpdate();
}

void SceneManager::Render()
{
    if (isChanging)return;
    currentScene->Render();
}

void SceneManager::PreRender()
{
    if (isChanging)return;
    currentScene->PreRender();
}

void SceneManager::ResizeScreen()
{
    if (isChanging || !currentScene)return;
    currentScene->ResizeScreen();
}

bool SceneManager::IsMacthScene(SceneName key)
{
    if (currentSceneKey == key) return true;
    return false;
}
