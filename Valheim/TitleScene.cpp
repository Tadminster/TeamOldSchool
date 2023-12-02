#include "stdafx.h"
#include "LoadingScene.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	titleCamera = Camera::Create("titleCamera");
	titleCamera->LoadFile("Cam.xml");
	Camera::main = titleCamera;

	cameraRay.position = Vector3(45.0f, 100.0f, 45.0f);
	cameraRay.direction = Vector3(0.0f, -1.0f, 0.0f);

	underwaterRay.position = Vector3(44.5f, 100.0f, 44.5f);
	underwaterRay.direction = Vector3(0.0f, -1.0f, 0.0f);

	floor = Terrain::Create();
	floor->LoadFile("Terrain_floor.xml");
	floor->CreateMesh(100);

	ocean = Terrain::Create();
	ocean->LoadFile("Terrain_Ocean.xml");
	ocean->CreateMesh(100);

	underwater = UI::Create("UnderWater");
	underwater->LoadFile("UI_UnderWater.xml");

	openingPlayer = Actor::Create();
	openingPlayer->LoadFile("Unit/PlayerforOpening.xml");
	openingPlayer->name = "OpeningPlayer";
	openingPlayer->name = "Player";
}

TitleScene::~TitleScene()
{
	titleCamera->Release();
	openingPlayer->Release();
	ocean->Release();
	floor->Release();
}

void TitleScene::Init()
{
	SCENE->AddScene("Loading", new LoadingScene);
	LIGHT->UpdateDirection();
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
		ocean->RenderHierarchy();
		floor->RenderHierarchy();
		openingPlayer->RenderHierarchy();
		underwater->RenderHierarchy();
	}
	ImGui::End();


	Camera::main->ControlMainCam();
	Camera::main->Update();
	
	static float waveCycle = 0.0f;
	if (TIMER->GetTick(waveCycle, 0.05f))
	{
		ocean->PerlinNoiseSea(perlin);
	}

	ocean->Update();
	floor->Update();
	openingPlayer->Update();
	underwater->Update();

	if (INPUT->KeyDown(VK_SPACE))
	{
		SCENE->ChangeScene("Loading");
	}
}

void TitleScene::LateUpdate()
{
	// 카메라 위치를 물 표현으로 조절
	if (Utility::RayIntersectMap(cameraRay, ocean, rayHitPos))
	{
		titleCamera->SetWorldPos(Vector3(rayHitPos.x, rayHitPos.y * weightPosY, rayHitPos.z));

		// 물속 표현
		if (rayHitPos.y > titleCamera->GetWorldPos().y)
			underwater->visible = true;
		else underwater->visible = false;
	}
}

void TitleScene::PreRender()
{
	Camera::main->Set();
	LIGHT->Set();
}

void TitleScene::Render()
{
	Camera::main->Set();

	floor->Render();
	openingPlayer->Render();

	BLEND->Set(true);
	ocean->Render();
	BLEND->Set(false);

	underwater->Render();
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
