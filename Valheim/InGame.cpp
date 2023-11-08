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

#include "TreeBeech.h"

#include "InGame.h"

InGame::InGame()
{
	gameManager = new GameManager();

	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");
	Camera::main = tempCamera;

	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

	playerInventoryUI = new InventoryUiPannel();
	treeBeech = new TreeBeech();

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

	//Camera::main->ControlMainCam();
	Camera::main->Update();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		if (DEBUG)
		{
			grid->RenderHierarchy();
			PLAYER->AvtivatePlayerCam();
		}
		
		tempCamera->RenderHierarchy();
		skyBox->RenderHierarchy();
		treeBeech->RenderHierarchy();
		PLAYER->GetPlayer()->RenderHierarchy();
	}
	ImGui::End();

	// 디버그 모드
	if (DEBUG)
	{
		grid->Update();
	}
	PLAYER->AvtivatePlayerCam();

	skyBox->Update();
	playerInventoryUI->Update();
	treeBeech->Update();
	playerOptionUI->Update();
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

	if (DEBUG)
	{
		grid->Render();
	}

	skyBox->Render();
	MAP->Render();
	playerInventoryUI->Render();
	treeBeech->Render();
	playerOptionUI->Render();
	PLAYER->Render();
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
