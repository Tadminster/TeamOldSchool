#include "stdafx.h"
#include "InGame.h"
#include "Main.h"

Main::Main()
{
   
}

Main::~Main()
{
}

void Main::Init()
{
    SCENE->AddScene("InGame", new InGame);
    SCENE->ChangeScene("InGame");
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