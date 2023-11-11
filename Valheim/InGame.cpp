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
#include "Wood.h"
#include "StoneAxe.h"
#include "InGame.h"

InGame::InGame()
{
	gameManager = new GameManager();

	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");

	tempCamera2 = Camera::Create("tempCamera2");
	tempCamera2->LoadFile("Cam.xml");

	grid = Grid::Create();
	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

	playerInventoryUI = new InventoryUiPannel();
	playerOptionUI    = new GameOption();
	
	
	wood = new Wood();
	stoneAxe = new StoneAxe();


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
	PLAYER->Init();
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
			tempCamera2->RenderHierarchy();
		}
		skyBox->RenderHierarchy();
		MAP->RenderHierarchy();
		OBJ->RenderHierarchy();
		PLAYER->GetActor()->RenderHierarchy();

	}
	ImGui::End();

	// 디버그 모드
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
	playerInventoryUI->Update();
	playerOptionUI->Update();
	wood->Update();
	stoneAxe->Update();
	
	OBJ->Update();
	PLAYER->Update();


}

void InGame::LateUpdate()
{
	playerInventoryUI->LateUpdate();
	playerOptionUI->LateUpdate();
	wood->LateUpdate();
	stoneAxe->LateUpdate();
	
	PLAYER->LateUpdate();
}

void InGame::PreRender()
{
	Camera::main->Set();
	LIGHT->Set();

	skyBox->Render(RESOURCE->shaders.Load("0.Sky_CR.hlsl"));
	MAP->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));
	
	//OBJ->Render();

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
	//OBJ->FrustumCulling(tempCamera2);
	OBJ->Render();
	PLAYER->Render();
	playerInventoryUI->Render();
	playerOptionUI->Render();
	wood->Render();
	stoneAxe->Render();


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
