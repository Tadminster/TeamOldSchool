#include "stdafx.h"
#include "InGame.h"
#include "LoadingScene.h"


int loadCount = 0;

void CreateInGameScene()
{
    SCENE->AddScene(SceneName::InGame, new InGame());
}

void LoadingScene::Init()
{
    loadingCam = Camera::Create();
    loadingCam->LoadFile("Cam.xml");
    Camera::main = loadingCam;

    backgroundImg = UI::Create();
    backgroundImg->LoadFile("UI_Loading.xml");

    thread2 = new thread(CreateInGameScene);
  
    textPos.left = App.GetWidth() * 0.9f;
    textPos.top = App.GetHeight() * 0.95f;
    textPos.right = textPos.left + 1000;
    textPos.bottom = textPos.top + 300;

    ResizeScreen();
}

void LoadingScene::Release()
{
    loadingCam->Release();
    backgroundImg->Release();

    thread2->join();
    delete thread2;
}

void LoadingScene::Update()
{
    float maximumPercent = min(99.0f, 100.0f * ((float)loadCount / (MAX_LOADCOUNT - 1)));
   // loadingProgress = clamp(loadingProgress + LOADIND_RATE, (float)loadCount * 19.0f, maximumPercent);
    loadingProgress = clamp(loadingProgress, (float)loadCount * 19.0f, maximumPercent);

    if (loadCount == MAX_LOADCOUNT)
    {
        SCENE->ChangeScene(SceneName::InGame);
    }
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
    int temp = (int)loadingProgress;


    DWRITE->RenderText(
        to_wstring(temp) + L" %",
        textPos,
        30.0f,
        L"Arial",
        Color(1.0f, 1.0f, 1.0f, 0.0f),
        DWRITE_FONT_WEIGHT_SEMI_BOLD,
        DWRITE_FONT_STYLE_ITALIC,
        DWRITE_FONT_STRETCH_EXPANDED);

    loadingCam->Set();
    LIGHT->Set();
    backgroundImg->Render();
}

void LoadingScene::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
