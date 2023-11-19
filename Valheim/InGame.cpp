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
	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

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
	
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		if(DEBUGMODE)
		{
			grid->RenderHierarchy();
			tempCamera->RenderHierarchy();
		}
		skyBox->RenderHierarchy();
		MAP->RenderHierarchy();
		SEA->RenderHierarchy();
		OBJ->RenderHierarchy();
		PLAYER->GetActor()->RenderHierarchy();
		MINIMAP->RenderHierarchy();
		elder->RenderHierarchy();
	}
	ImGui::End();

	if (DEBUGMODE)
	{
		Camera::main = tempCamera;
		Camera::main->ControlMainCam();

		grid->Update();
	}
	else 
	{
		PLAYER->AvtivatePlayerCam();
	}

	GM->Update();

	Camera::main->Update();
	skyBox->Update();
	
	SEA->Update();
	OBJ->Update();

	INVEN->Update();

	elder->Update();
	PLAYER->Update();
	MINIMAP->Update();


}

void InGame::LateUpdate()
{
	INVEN->LateUpdate();
	OBJ->LateUpdate();
	PLAYER->LateUpdate();
	MINIMAP->LateUpdate();

	elder->LateUpdate();
}

void InGame::PreRender()
{
	Camera::main->Set();
	LIGHT->Set();

	skyBox->Render(RESOURCE->shaders.Load("0.Sky_CR.hlsl"));
	MAP->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));

	// ¹°¹Ý»ç ·»´õ¸µ
	SEA->SetReflectionTarget();
	OBJ->RefractionRender();
	PLAYER->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	//MAP->Render(RESOURCE->shaders.Load("5.Cube_Water.hlsl"));
	
	// ¹°±¼Àý ·»´õ¸µ
	SEA->SetRefractionTarget();
	PLAYER->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	MAP->Render(RESOURCE->shaders.Load("5.Cube_Water.hlsl"));
}

void InGame::Render()
{
	Camera::main->Set();
	LIGHT->Set();
	skyBox->Render();

	if (DEBUGMODE)
	{
		grid->Render();
	}

	MAP->Render();
	SEA->Render();
	OBJ->Render();

	elder->Render();
	PLAYER->Render();
	MINIMAP->Render();

	INVEN->Render();
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
