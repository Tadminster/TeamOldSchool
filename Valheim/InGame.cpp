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

	//RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("0.SkySphere_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("5.Cube_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("5.Cube_Shadow.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("4.Instance_CR.hlsl")->LoadGeometry();
	//RESOURCE->shaders.Load("4.Instance_Shadow.hlsl")->LoadGeometry();
	playerInventory = UI::Create("playerInventory");
	playerInventory->LoadFile("InvenUI.xml");
	//인벤토리 처음에 감추기 메인슬롯은 보여줍니다
	playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = false;
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("mainSlot" + to_string(i))->visible = true;
		playerInventory->Find("subSlot" + to_string(i))->visible = false;
		playerInventory->Find("SecondsubSlot" + to_string(i))->visible = false;
		playerInventory->Find("ThirdsubSlot" + to_string(i))->visible = false;
	}


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
		playerInventory->RenderHierarchy();
	}
	ImGui::End();



	grid->Update();
	skyBox->Update();
	playerInventory->Update();

	//ui 위치코드로 배정해주기
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("subSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090, 0.110, 0));
		playerInventory->Find("subSlot" + to_string(i))->scale.x = 0.110f;
		playerInventory->Find("subSlot" + to_string(i))->scale.y = 0.170f;

		playerInventory->Find("SecondsubSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090, -0.050, 0));
		playerInventory->Find("SecondsubSlot" + to_string(i))->scale.x = 0.110f;
		playerInventory->Find("SecondsubSlot" + to_string(i))->scale.y = 0.170f;

		playerInventory->Find("ThirdsubSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090, -0.200, 0));
		playerInventory->Find("ThirdsubSlot" + to_string(i))->scale.x = 0.110f;
		playerInventory->Find("ThirdsubSlot" + to_string(i))->scale.y = 0.170f;
	}

}

void InGame::LateUpdate()
{
	//탭키로 인벤토리 온오프

	if (INPUT->KeyDown(VK_TAB))
	{
		playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = !playerInventory->Find("PLAYER_PANNEL_INVEN")->visible;
		for (int i = 0; i < 8; i++)
		{
			playerInventory->Find("subSlot" + to_string(i))->visible = !playerInventory->Find("subSlot" + to_string(i))->visible;
			playerInventory->Find("SecondsubSlot" + to_string(i))->visible = !playerInventory->Find("SecondsubSlot" + to_string(i))->visible;
			playerInventory->Find("ThirdsubSlot" + to_string(i))->visible = !playerInventory->Find("ThirdsubSlot" + to_string(i))->visible;
		}
	}


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

	playerInventory->Render();

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
