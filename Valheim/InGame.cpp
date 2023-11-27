#include "stdafx.h"
//#include "Prototype.h"
#include "ItemProto.h"
//#include "Inventory.h"
#include "GameOption.h"
#include "StoneAxe.h"
#include "Elder.h"
#include "InGame.h"

InGame::InGame()
{
	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");

	grid = Grid::Create();

	scattering = new Scattering();
	

	elder = new Elder();

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
	PLAYER->Init();
	elder->Init();
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
		if(DEBUGMODE)
		{
			grid->RenderHierarchy();
			tempCamera->RenderHierarchy();
		}
		
		MAP->RenderHierarchy();
		SEA->RenderHierarchy();
		OBJ->RenderHierarchy();
		PARTICLE->RenderHierarchy();
		PLAYER->GetActor()->RenderHierarchy();
		MINIMAP->RenderHierarchy();
		elder->RenderHierarchy();
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
		if(isDebugCamControl) Camera::main->ControlMainCam();
	}
	else PLAYER->AvtivatePlayerCam();

	GM->Update();

	Camera::main->Update();
	
	SEA->Update();
	OBJ->Update();
	PARTICLE->Update();

	INVEN->Update();
	CRAFT->Update();

	elder->Update();
	PLAYER->Update();
	MINIMAP->Update();
}



void InGame::LateUpdate()
{
	INVEN->LateUpdate();
	CRAFT->LateUpdate();
	OBJ->LateUpdate();
	PLAYER->LateUpdate();
	MINIMAP->LateUpdate();
	PARTICLE->LateUpdate();

	elder->LateUpdate();
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

	elder->Render();
	PLAYER->Render();
	PARTICLE->Render();
	MINIMAP->Render();

	INVEN->Render();
	CRAFT->Render();
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
