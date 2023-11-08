#include "stdafx.h"
#include "Prototype.h"

#include "Item.h"
#include "BattleItem.h"
#include "LivingItem.h"
#include "ConsumeItem.h"
#include "ResourceItem.h"
#include "Inventory.h"
#include "InventoryUiPannel.h"
#include "GameOption.h"

#include "InGame.h"

InGame::InGame()
{
	gameManager = new GameManager();

	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");
	Camera::main = tempCamera;

	grid = Grid::Create();
	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

	playerInventoryUI = new InventoryUiPannel();

	playerOptionUI    = new GameOption();
	
	RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("0.SkySphere_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("5.Cube_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("5.Cube_Shadow.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("4.Instance_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("4.Instance_Shadow.hlsl")->LoadGeometry();
}

InGame::~InGame()
{

}

void InGame::Init()
{
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
		if (DEBUGMODE)
		{
			grid->RenderHierarchy();
			PLAYER->AvtivatePlayerCam();
		}
		
		tempCamera->RenderHierarchy();
		skyBox->RenderHierarchy();
		MAP->RenderHierarchy();
		PLAYER->GetActor()->RenderHierarchy();
	}
	ImGui::End();

	// 디버그 모드
	if (DEBUGMODE)
	{
		grid->Update();
		PLAYER->AvtivatePlayerCam();
	}
	else {
		Camera::main->ControlMainCam();
	}
		
	GM->Update();

	Camera::main->Update();
	skyBox->Update();
	playerInventoryUI->Update();
	playerOptionUI->Update();
	
	OBJ->Update();
	PLAYER->Update();


}

void InGame::LateUpdate()
{
	playerInventoryUI->LateUpdate();
	PLAYER->LateUpdate();
}

void InGame::PreRender()
{
	LIGHT->Set();

	skyBox->Render(RESOURCE->shaders.Load("0.Sky_CR.hlsl"));
	MAP->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));
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
	OBJ->Render();
	PLAYER->Render();
	playerInventoryUI->Render();
	playerOptionUI->Render();


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
