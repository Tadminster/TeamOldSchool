#include "stdafx.h"
#include "InGame.h"
#include "Prototype.h"
#include "Item.h"
#include "BattleItem.h"
#include "LivingItem.h"
#include "ConsumeItem.h"
#include "ResourceItem.h"
#include "Inventory.h"
#include "InventoryUiPannel.h"

InGame::InGame()
{
	grid = Grid::Create("Grid");

	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");
	Camera::main = tempCamera;

    map = Terrain::Create("Terrain");
    map->LoadFile("TerrainPerlin.xml");
    map->PerlinNoiseHeightMap();
    map->CreateStructuredBuffer();

	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

	playerInventoryUI = new InventoryUiPannel();
	//RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("0.SkySphere_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("5.Cube_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("5.Cube_Shadow.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("4.Instance_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("4.Instance_Shadow.hlsl")->LoadGeometry();
	
	RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
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

	Camera::main->ControlMainCam();
	Camera::main->Update();

	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		grid->RenderHierarchy();
		tempCamera->RenderHierarchy();
		map->RenderHierarchy();
		skyBox->RenderHierarchy();
	}
	ImGui::End();

	grid->Update();
	skyBox->Update();
	playerInventoryUI->Update();


}

void InGame::LateUpdate()
{
	playerInventoryUI->LateUpdate();
	
}

void InGame::PreRender()
{
	LIGHT->Set();

	skyBox->Render(RESOURCE->shaders.Load("0.Sky_CR.hlsl"));
	map->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));
}

void InGame::Render()
{
	Camera::main->Set();
	LIGHT->Set();

	skyBox->Render();
	grid->Render();
	map->Render();
	playerInventoryUI->Render();

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
