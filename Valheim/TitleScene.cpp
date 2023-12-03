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
	titleCamera->name = "TitleCamera";
	titleCamera->SetWorldPos(Vector3(40.0f, 0.f, 40.0f));
	Camera::main = titleCamera;

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
	player->parent = karve;
	player->rotation.y = 180.0f * ToRadian;
	player->SetLocalPos(playerPos);
	playerRay.direction = Vector3(0.0f, -1.0f, 0.0f);

	monster01 = Actor::Create();
	monster01->LoadFile("Unit/Monster_JellyFish.xml");
	monster01->name = "Monster1";
	monster01->SetWorldPos(Vector3(43.0f, -3.0f, 36.0f));
	monster01->anim->ChangeAnimation(AnimationState::LOOP, 2);

	monster02 = Actor::Create();
	monster02->LoadFile("Unit/Monster_JellyFish.xml");
	monster02->name = "Monster2";
	monster02->SetWorldPos(Vector3(25.0f, -3.5f, 42.0f));
	monster02->anim->ChangeAnimation(AnimationState::LOOP, 2);
	
	PARTICLE->waterSplash->rotation.y = -50.0f * ToRadian;

	mouseIcon = UI::Create();
	mouseIcon->LoadFile("Unit/Mouse_Torch.xml");
	mouseIcon->name = "mouse";
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	SCENE->AddScene(SceneName::Loading, new LoadingScene);
	LIGHT->UpdateDirection();
	ShowCursor(false);
	SOUND->Play(BGM_OCEANWAVE);
	SETTING->Init();
}

void TitleScene::Release()
{
	titleUI->Release();

	player->Release();
	karve->Release();
	monster01->Release();

	titleCamera->Release();
	
	background->Release();
	underwater->Release();
	ocean->Release();
	floor->Release();
	mouseIcon->Release();
	PARTICLE->waterSplash->rotation.y = 0.0f;
	SOUND->Stop(BGM_OCEANWAVE);
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
		monster01->RenderHierarchy();
		monster02->RenderHierarchy();
		mouseIcon->RenderHierarchy();
		PARTICLE->waterSplash->RenderHierarchy();
	}
	ImGui::End();

	mouseIcon->SetWorldPos(Utility::MouseToNDC()+Vector3(0,-0.01f,0));

	// 메인 카메라 업데이트
	Camera::main->ControlMainCam();
	Camera::main->Update();
	
	// 물결 효과 (펄린노이즈)
	static float waveCycle = 0.0f;
	if (TIMER->GetTick(waveCycle, 0.05f))
	{
		ocean->PerlinNoiseSea(perlin);
	}

	// 레이 위치 설정
	Vector3 playerPos = player->GetWorldPos();
	playerRay.position = Vector3(playerPos.x, 100.0f, playerPos.z);
	Vector3 cameraPos = titleCamera->GetWorldPos();
	cameraRay.position = Vector3(cameraPos.x, 100.0f, cameraPos.z);
	// 시작버튼을 눌렀으면
	if (titleUI->isPostStart)
	{
		// 카메라 이동
		titleCamera->MoveWorldPos(cameraDir * 1.0f * DELTA);
		karve->MoveWorldPos(-cameraDir * 2.0f * DELTA);
		monster01->MoveWorldPos(-cameraDir * 5.0f * DELTA);
		monster02->MoveLocalPos(monster02->GetForward() * 5.0f * DELTA);
	}

	titleUI->Update();
	background->Update();
	ocean->Update();
	floor->Update();
	underwater->Update();
	player->Update();
	karve->Update();
	monster01->Update();
	monster02->Update();
	mouseIcon->Update();
	PARTICLE->Update();
	SETTING->Update();
}

void TitleScene::LateUpdate()
{

	// 배(플레이어) 위치 설정 
	if (Utility::RayIntersectMap(playerRay, ocean, playerRayHitPos))
	{
		// 배 Y위치를 물 표면으로 설정
		karve->SetWorldPosY(playerRayHitPos.y + karvePosY);

		static float waterEffectCycle = 1.9f;
		if (TIMER->GetTick(waterEffectCycle, 2.0f))
		{
			PARTICLE->PlayParticleEffect(EffectType::WATERSPLASH, karve->Find("Bow")->GetWorldPos());
		}
	}

	if (Utility::RayIntersectMap(cameraRay, ocean, rayHitPos))
	{
		// 카메라 Y위치를 물 표면으로 설정
		titleCamera->SetWorldPosY(rayHitPos.y * weightPosY);

		// 물속 표현
		if (rayHitPos.y > titleCamera->GetWorldPos().y)
		{
			// 물속으로 들어갈 때 잠수중이 아니라면
			if (!isUnderwater)
			{
				isUnderwater = true;
				underwater->visible = true;

				// 물속에서 들리는 파도 소리
				SoundName randomPlay1 = static_cast<SoundName>(RANDOM->Int(UNDERWATER_WAVE_PASS_BY_01, UNDERWATER_WAVE_PASS_BY_04));
				SOUND->Play(randomPlay1);

				// 물속에서 고통스러워 하는 소리
				SoundName randomPlay2 = static_cast<SoundName>(RANDOM->Int(UNDERWATER_HURT_01, UNDERWATER_HURT_03));
				SOUND->Play(randomPlay2);
			}
		}
		// 물속에서 나왔으면
		else
		{
			isUnderwater = false;
			underwater->visible = false;
		}
	}

	SETTING->LateUpdate();
	titleUI->LateUpdate();
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
	monster01->Render();
	monster02->Render();

	BLEND->Set(true);
	ocean->Render();
	BLEND->Set(false);

	underwater->Render();

	titleUI->Render();
	mouseIcon->Render();
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
