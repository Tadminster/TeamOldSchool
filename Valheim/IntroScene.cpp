#include "stdafx.h"
#include "TitleScene.h"
#include "IntroScene.h"

int introCount = 0;

void CreateTitleScene()
{
    SCENE->AddScene(SceneName::Title, new TitleScene());
}

void IntroScene::Init()
{
    introCam = Camera::Create();
    introCam->LoadFile("Cam.xml");
    Camera::main = introCam;

    backgroundImg = UI::Create();
    backgroundImg->LoadFile("UI_Intro.xml");

    thread1 = new thread(CreateTitleScene);

    ResizeScreen();
}

void IntroScene::Release()
{
    introCam->Release();
    backgroundImg->Release();

    thread1->join();
    delete thread1;
}

void IntroScene::Update()
{
    if (introCount == MAX_INTROCOUNT)
    {
        SCENE->ChangeScene(SceneName::Title);
    }
}

void IntroScene::LateUpdate()
{
}

void IntroScene::PreRender()
{
}

void IntroScene::Render()
{
    introCam->Set();
    LIGHT->Set();
    backgroundImg->Render();
}

void IntroScene::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
