#include "stdafx.h"
#include "IntroScene.h"
#include "Main.h"

Main::Main()
{
   
}

Main::~Main()
{
}

void Main::Init()
{
    SCENE->AddScene(SceneName::Intro, new IntroScene);
    SCENE->ChangeScene(SceneName::Intro);
}

void Main::Release()
{
    SCENE->Release();
}

void Main::Update()
{
    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}

void Main::PreRender()
{
    SCENE->PreRender();
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Valheim");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();

    int wParam = (int)WIN->Run(main);


    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}