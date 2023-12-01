#include "stdafx.h"
#include "LoadingScene.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	titleCamera = Camera::Create("titleCamera");
	titleCamera->LoadFile("Cam.xml");
	Camera::main = titleCamera;

	sea = Terrain::Create();
	sea->LoadFile("Terrain_sea.xml");
	sea->CreateMesh(100);
}

TitleScene::~TitleScene()
{
	titleCamera->Release();
}

void TitleScene::Init()
{
	SCENE->AddScene("Loading", new LoadingScene);
}

void TitleScene::Release()
{
}

void TitleScene::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		titleCamera->RenderHierarchy();
		sea->RenderHierarchy();
	}
	ImGui::End();


	Camera::main->ControlMainCam();
	Camera::main->Update();
	
	static float waveCycle = 0.0f;
	if (TIMER->GetTick(waveCycle, 0.05f))
	{
		sea->PerlinNoiseSea();
	}

	sea->Update();

	if (INPUT->KeyDown(VK_SPACE))
	{
		SCENE->ChangeScene("Loading");
	}
}

void TitleScene::LateUpdate()
{

}

void TitleScene::PreRender()
{
	Camera::main->Set();
	LIGHT->Set();
}

void TitleScene::Render()
{
	Camera::main->Set();
	sea->Render();
}

void TitleScene::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
