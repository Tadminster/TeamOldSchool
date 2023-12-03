#include "stdafx.h"
#include "TitleUI.h"
#include "LoadingScene.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	titleUI = new TitleUI();

	background = Actor::Create();
	background->LoadFile("RECT_TitleBG.xml");
	background->name = "Background";
	
	titleCamera = Camera::Create("titleCamera");
	titleCamera->LoadFile("Cam_title.xml");
	Camera::main = titleCamera;
	cameraRay.position = Vector3(45.0f, 100.0f, 45.0f);
	cameraRay.direction = Vector3(0.0f, -1.0f, 0.0f);

	floor = Terrain::Create();
	floor->LoadFile("Terrain_floor.xml");
	floor->CreateMesh(100);
	floor->name = "Floor";

	ocean = Terrain::Create();
	ocean->LoadFile("Terrain_Ocean.xml");
	ocean->CreateMesh(100);
	ocean->name = "Ocean";

	underwater = UI::Create("UnderWater");
	underwater->LoadFile("UI_UnderWater.xml");
	underwater->name = "UnderWater";

	player = Actor::Create();
	player->LoadFile("Unit/PlayerforOpening.xml");
	player->name = "Player";

	karve = Actor::Create();
	karve->LoadFile("Feature_Karve_title.xml");
	karve->name = "Karve";

	playerRay.position = Vector3(30.0f, 100.0f, 25.0f);
	playerRay.direction = Vector3(0.0f, -1.0f, 0.0f);

	jellyFish = Actor::Create();
	jellyFish->LoadFile("Unit/Monster_JellyFish.xml");
	jellyFish->name = "jellyFish";
	jellyFish->anim->ChangeAnimation(AnimationState::LOOP, 2);
	
	PARTICLE->waterSplash->rotation.y = -50.0f * ToRadian;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	SCENE->AddScene(SceneName::Loading, new LoadingScene);
	LIGHT->UpdateDirection();
	SETTING->Init();
}

void TitleScene::Release()
{
	titleUI->Release();

	player->Release();
	karve->Release();
	jellyFish->Release();

	titleCamera->Release();
	
	background->Release();
	underwater->Release();
	ocean->Release();
	floor->Release();

	PARTICLE->waterSplash->rotation.y = 0.0f;
	//btnStart->Release();
	//btnOption->Release();
	//btnExit->Release();
}

void TitleScene::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		titleUI->RenderHierarchy();
		background->RenderHierarchy();
		titleCamera->RenderHierarchy();
		ocean->RenderHierarchy();
		floor->RenderHierarchy();
		underwater->RenderHierarchy();
		player->RenderHierarchy();
		karve->RenderHierarchy();
		jellyFish->RenderHierarchy();
		PARTICLE->waterSplash->RenderHierarchy();
	}
	ImGui::End();


	Camera::main->ControlMainCam();
	Camera::main->Update();
	
	static float waveCycle = 0.0f;
	if (TIMER->GetTick(waveCycle, 0.05f))
	{
		ocean->PerlinNoiseSea(perlin);
	}

	titleUI->Update();
	background->Update();
	ocean->Update();
	floor->Update();
	underwater->Update();
	player->Update();
	karve->Update();
	jellyFish->Update();
	PARTICLE->Update();
	SETTING->Update();
}

void TitleScene::LateUpdate()
{

	// 플레이어와 배 위치 설정
	if (Utility::RayIntersectMap(playerRay, ocean, playerRayHitPos))
	{
		karve->SetWorldPos(playerRayHitPos + karvePos);
		player->SetWorldPos(playerRayHitPos + playerPos);

		static float waterEffectCycle = 1.9f;
		if (TIMER->GetTick(waterEffectCycle, 2.0f))
		{
			PARTICLE->PlayParticleEffect(EffectType::WATERSPLASH, karve->Find("Bow")->GetWorldPos());
		}
	}

	if (Utility::RayIntersectMap(cameraRay, ocean, rayHitPos))
	{
		// 카메라 위치를 물 표면으로 설정
		//titleCamera->SetWorldPos(Vector3(rayHitPos.x, rayHitPos.y * weightPosY, rayHitPos.z));

		// 물속 표현
		if (rayHitPos.y > titleCamera->GetWorldPos().y)
			underwater->visible = true;
		else underwater->visible = false;
	}

	titleUI->LateUpdate();
	SETTING->LateUpdate();
}

void TitleScene::PreRender()
{
	ResizeScreen();

	Camera::main->Set();
	LIGHT->Set();
}

void TitleScene::Render()
{
	Camera::main->Set();
	PARTICLE->Render();

	background->Render();
	floor->Render();
	player->Render();
	karve->Render();
	jellyFish->Render();

	BLEND->Set(true);
	ocean->Render();
	BLEND->Set(false);

	underwater->Render();

	titleUI->Render();
	SETTING->Render();
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
