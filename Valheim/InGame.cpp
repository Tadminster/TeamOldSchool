#include "stdafx.h"
#include "ItemProto.h"
#include "MonsterManager.h"
#include "OutroScene.h"
#include "InGame.h"

extern int loadCount;

InGame::InGame()
{
	scattering = new Scattering();
	loadCount++; // 1
	
	mouseIcon = UI::Create();
	mouseIcon->LoadFile("Unit/Mouse_Aim.xml");
	mouseIcon->name = '1';
	loadCount++; // 2
	
	mouseIcon2 = UI::Create();
	mouseIcon2->LoadFile("Unit/Mouse_Torch.xml");
	mouseIcon2->name = '2';
	
	fadeOut = UI::Create();
	fadeOut->name = "fade";
	fadeOut->LoadFile("UI_FadeOut.xml");
	loadCount++; // 3
	RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("0.SkySphere_CR.hlsl")->LoadGeometry();
	
	RESOURCE->shaders.Load("5.Cube_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_Shadow.hlsl")->LoadGeometry();
	loadCount++; // 4

	RESOURCE->shaders.Load("5.Cube_Water.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_CR.hlsl")->LoadGeometry();
	
	RESOURCE->shaders.Load("4.Instance_Shadow.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_Water.hlsl")->LoadGeometry();
	loadCount++; // 5
}

InGame::~InGame()
{

}

void InGame::Init()
{
	mouseIcon2->visible = false;

	GM->Init();
	UIM->Init();

	OBJ->Init();
	PLAYER->Init();
	MONSTER->Init();
	SETTING->Init();
	// 배경음악 재생
	SOUND->Play(BGM_HOMEBASE);
	// 라이트 현재시간 초기화
	LIGHT->currentTime = LIGHT->halfdayCycleLength;
}

void InGame::Release()
{
	OBJ->Release();
	GM->Release();
	UIM->Release();

	fadeOut->Release();
	LIGHT->currentTime = LIGHT->halfdayCycleLength;
	SOUND->Stop(BGM_HOMEBASE);
	PARTICLE->Release();
	SETTING->Release();
	delete scattering;
}

void InGame::Update()
{
	//LIGHT->RenderDetail();
	//scattering->RenderDetail();

	mouseIcon2->SetWorldPos(Utility::MouseToNDC() + Vector3(0.025f, -0.045f, 0));

	if (!INVEN->isOpen && !CRAFT->isOpen && !SETTING->isOpen && !STATUS->isOpen)
	{
		mouseIcon->visible = true;
		mouseIcon2->visible = false;
	}
	else
	{
		mouseIcon->visible = false;
		mouseIcon2->visible = true;
	}

	//ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	/*ImGui::Begin("Hierarchy");
	{
		MAP->RenderHierarchy();
		SEA->RenderHierarchy();
		OBJ->RenderHierarchy();
		PARTICLE->RenderHierarchy();
		PLAYER->RenderHierarchy();
		MONSTER->RenderHierarchy();
	}
	ImGui::End();*/

	// F1 : 모드전환
	//if (INPUT->KeyDown(VK_F1))
	//{
	//	DEBUGMODE = !DEBUGMODE;
	//}
	// F2 : 카메라전환
	//if (INPUT->KeyDown(VK_F2))
	//{
	//	if (DEBUGMODE)
	//	{
	//		Camera::main = tempCamera;
	//		isDebugCam = true;
	//	}
	//	else
	//	{
	//		Camera::main = PLAYER->GetPlayerCam();
	//		isDebugCam = false;
	//	}
	//}

	// 디버그 모드에서 업데이트
	//if (DEBUGMODE)
	//{
	//	grid->Update();
	//}

	// 카메라에 따른 조작
	//if (isDebugCam)
	//{
	//	if (INPUT->KeyDown(VK_F3)) isDebugCamControl = !isDebugCamControl;
	//	if (isDebugCamControl) Camera::main->ControlMainCam();
	//}
	//else 
	

	Camera::main->Update();
	mouseIcon->Update();
	mouseIcon2->Update();
	GM->Update();
	SEA->Update();
	OBJ->Update();
	PARTICLE->Update();
	PLAYER->Update();
	SETTING->Update();
	UIM->Update();
	MONSTER->Update();
	fadeOut->Update();
	//월드타임을 받아오고 그에따라서 광원의 각도를 변화시킵니다
	
	LIGHT->UpdateDirection();

	if (PLAYER->isEnding)
	{
		fadeout += DELTA;
		fadeOut->material->opacity = fadeout * (1.0f / FADEOUT);
	}
	if (fadeOut->material->opacity>=1.0f)
	{
		SCENE->AddScene(SceneName::Outro, new OutroScene());
		SCENE->ChangeScene(SceneName::Outro);
	}
		
	

}

void InGame::LateUpdate()
{
	OBJ->LateUpdate();
	PLAYER->LateUpdate();
	MONSTER->LateUpdate();
	SETTING->LateUpdate();
	UIM->LateUpdate();
}

void InGame::PreRender()
{
	Camera::main->Set();

	scattering->DrawPass1();
	//LIGHT->Set();

	MAP->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));

	// 물반사 렌더링
	SEA->SetReflectionTarget();
	OBJ->RefractionRender();
	PLAYER->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	//MAP->Render(RESOURCE->shaders.Load("5.Cube_Water.hlsl"));

	// 물굴절 렌더링
	SEA->SetRefractionTarget();
	PLAYER->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	MAP->Render(RESOURCE->shaders.Load("5.Cube_Water.hlsl"));
}

void InGame::Render()
{
	Camera::main->Set();
	scattering->DrawPass2();
	//LIGHT->Set();

	GM->Render();
	MAP->Render();
	SEA->Render();
	OBJ->Render();
	PARTICLE->Render();
	MONSTER->Render();
	PLAYER->Render();
	UIM->Render();
	SETTING->Render();
	mouseIcon->Render();
	mouseIcon2->Render();
	fadeOut->Render();
}

void InGame::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();

	INVEN->ResizeScreen();
}
