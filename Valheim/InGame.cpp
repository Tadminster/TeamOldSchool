#include "stdafx.h"
//#include "Prototype.h"
#include "ItemProto.h"
//#include "Inventory.h"
#include "GameOption.h"
#include "StoneAxe.h"
#include "Elder.h"
#include "Goblin.h"
#include "InGame.h"

InGame::InGame()
{
	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");

	grid = Grid::Create();

	scattering = new Scattering();

	elder = new Elder();
	goblin = new Goblin();

	RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("0.SkySphere_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_Shadow.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_Water.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_Shadow.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_Water.hlsl")->LoadGeometry();
}

InGame::~InGame()
{

}

void InGame::Init()
{
	GM->Init();
	UIM->Init();
	PLAYER->Init();

	elder->Init();
	goblin->Init();
}

void InGame::Release()
{
}

void InGame::Update()
{
	LIGHT->RenderDetail();
	scattering->RenderDetail();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		if (DEBUGMODE)
		{
			grid->RenderHierarchy();
			tempCamera->RenderHierarchy();
		}

		MAP->RenderHierarchy();
		SEA->RenderHierarchy();
		OBJ->RenderHierarchy();
		PARTICLE->RenderHierarchy();
		PLAYER->RenderHierarchy();
		elder->RenderHierarchy();
		goblin->RenderHierarchy();
	}
	ImGui::End();

	// F1 : 모드전환
	if (INPUT->KeyDown(VK_F1))
	{
		DEBUGMODE = !DEBUGMODE;
	}
	// F2 : 카메라전환
	if (INPUT->KeyDown(VK_F2))
	{
		if (DEBUGMODE)
		{
			Camera::main = tempCamera;
			isDebugCam = true;
		}
		else
		{
			Camera::main = PLAYER->GetPlayerCam();
			isDebugCam = false;
		}
	}

	// 디버그 모드에서 업데이트
	if (DEBUGMODE)
	{
		grid->Update();
	}

	// 카메라에 따른 조작
	if (isDebugCam)
	{
		if (INPUT->KeyDown(VK_F3)) isDebugCamControl = !isDebugCamControl;
		if (isDebugCamControl) Camera::main->ControlMainCam();
	}
	else PLAYER->AvtivatePlayerCam();

	Camera::main->Update();

	SEA->Update();
	OBJ->Update();
	PARTICLE->Update();
	//elder->Update();
	goblin->Update();
	PLAYER->Update();
	UIM->Update();

	//월드타임을 받아오고 그에따라서 광원의 각도를 변화시킵니다
	float currentTime = TIMER->GetWorldTime();
	LIGHT->UpdateDirection(currentTime);
}



void InGame::LateUpdate()
{
	OBJ->LateUpdate();
	PLAYER->LateUpdate();
	PARTICLE->LateUpdate();

	//elder->LateUpdate();
	goblin->LateUpdate();
	UIM->LateUpdate();
}

void InGame::PreRender()
{
	Camera::main->Set();

	scattering->DrawPass1();
	LIGHT->Set();


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
	LIGHT->Set();


	if (DEBUGMODE)
	{
		grid->Render();
	}

	MAP->Render();
	SEA->Render();
	OBJ->Render();
	//elder->Render();
	goblin->Render();
	PLAYER->Render();
	PARTICLE->Render();
	UIM->Render();
}

void InGame::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
