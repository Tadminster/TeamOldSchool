#include "stdafx.h"
#include "OutroScene.h"

extern int introCount;

OutroScene::OutroScene()
{
	background = Actor::Create();
	background->LoadFile("RECT_TitleBG.xml");
	background->name = "Background";

	outroCamera = Camera::Create("outroCamera");
	outroCamera->LoadFile("Cam_title.xml");
	outroCamera->name = "TitleCamera";
	outroCamera->SetWorldPos(Vector3(37.0f, 2.f, 34.0f));
	Camera::main = outroCamera;

	floor = Terrain::Create();
	floor->LoadFile("Terrain_floor.xml");
	floor->CreateMesh(100);
	floor->name = "Floor";

	ocean = Terrain::Create();
	ocean->LoadFile("Terrain_Ocean.xml");
	ocean->CreateMesh(100);
	ocean->name = "Ocean";

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
	karve->rotation.y = 220.0f * ToRadian;
	karve->SetWorldPos(Vector3(-20.0f, 0.0f, -20.0f));

	PARTICLE->waterSplash->rotation.y = -50.0f * ToRadian;
	introCount++;
}

OutroScene::~OutroScene()
{
}

void OutroScene::Init()
{
	LIGHT->UpdateDirection();

	SOUND->Play(BGM_OCEANWAVE);
	SOUND->Play(BGM_ENDING);
	SETTING->Init();
}

void OutroScene::Release()
{
	player->Release();
	karve->Release();

	outroCamera->Release();

	background->Release();
	ocean->Release();
	floor->Release();

	PARTICLE->waterSplash->rotation.y = 0.0f;
	SOUND->Stop(BGM_OCEANWAVE);
}

void OutroScene::Update()
{
	if (!isEnding)
	{
		// 메인 카메라 업데이트
		Camera::main->ControlMainCam();


		// 물결 효과 (펄린노이즈)
		static float waveCycle = 0.0f;
		if (TIMER->GetTick(waveCycle, 0.05f))
		{
			ocean->PerlinNoiseSea(perlin);
		}

		// 레이 위치 설정
		Vector3 playerPos = player->GetWorldPos();
		playerRay.position = Vector3(playerPos.x, 100.0f, playerPos.z);

		// 카메라 이동, 배 이동
		karve->MoveWorldPos(-cameraDir * 8.0f * DELTA);

		outroCamera->Update();
		background->Update();
		ocean->Update();
		floor->Update();
		player->Update();
		karve->Update();
		PARTICLE->Update();
		SETTING->Update();
	}
}

void OutroScene::LateUpdate()
{
	// 플레이어와 카메라 거리 계산
	float length = (outroCamera->GetWorldPos() - karve->GetWorldPos()).LengthSquared();
	//cout << length << endl;
	// 카메라와 일정거리 가까워지면
	if (length < 200 && length > 50)
	{
		// 0.1초마다 소리재생
		static float waveCycle = 0.0f;
		if (TIMER->GetTick(waveCycle, 0.1f))
		{
			SoundName randomPlay1 = static_cast<SoundName>(RANDOM->Int(UNDERWATER_WAVE_PASS_BY_01, UNDERWATER_WAVE_PASS_BY_04));
			SOUND->Play(randomPlay1);
		}
	}
	else if (length < 50)
	{
		isEnding = true;
	}

	if (!isEnding)
	{
		// 배(플레이어) 위치 설정 
		if (Utility::RayIntersectMap(playerRay, ocean, playerRayHitPos))
		{
			// 배 Y위치를 물 표면으로 설정
			karve->SetWorldPosY(playerRayHitPos.y + karvePosY);

			static float waterEffectCycle = 1.9f;
			if (TIMER->GetTick(waterEffectCycle, 0.2f))
			{
				PARTICLE->PlayParticleEffect(EffectType::WATERSPLASH, karve->Find("Bow")->GetWorldPos());
			}
		}
	}
}

void OutroScene::PreRender()
{
	ResizeScreen();

	Camera::main->Set();
	LIGHT->Set();
}

void OutroScene::Render()
{
	Camera::main->Set();
	PARTICLE->Render();

	background->Render();
	floor->Render();
	player->Render();
	karve->Render();

	BLEND->Set(true);
	ocean->Render();
	BLEND->Set(false);

	if (isEnding)
	{
		RECT rect;
		rect.left = App.GetWidth() * 0.2f;
		rect.right = rect.left + 2000;
		rect.top = App.GetHeight() * 0.4f;
		rect.bottom = rect.top + 2000;
		DWRITE->RenderText(L"Thank you for playing !!\n\nTEAM 올드스쿨\n김병구, 진희원, 민경호", rect, 70.0f, L"Arial", Color(1, 1, 1, 0), DWRITE_FONT_WEIGHT_SEMI_BOLD, DWRITE_FONT_STYLE_ITALIC, DWRITE_FONT_STRETCH_EXPANDED);

	}
}

void OutroScene::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
