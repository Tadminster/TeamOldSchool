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
	tempCamera = Camera::Create();
	tempCamera->LoadFile("Cam.xml");
	Camera::main = tempCamera;

	grid = Grid::Create();

	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

	playerInventory = UI::Create("playerInventory");
	playerInventory->LoadFile("InvenUI.xml");
	playerInventory->visible = false;


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
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::Begin("Hierarchy");
	{
		skyBox->RenderHierarchy();
		playerInventory->RenderHierarchy();
	}
	ImGui::End();

	Camera::main->ControlMainCam();
	Camera::main->Update();
	grid->Update();
	skyBox->Update();
	playerInventory->Update();

	//ui 위치코드로 배정해주기
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("subSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090,  0.110, 0));
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
		playerInventory->visible = !playerInventory->visible;
	}
	

}

void InGame::PreRender()
{
	// 육면체 텍스처 렌더링용 쉐이더
	// 1031 환경맵핑_2 20:00 참고

	skyBox->Render(RESOURCE->shaders.Load("0.Sky.hlsl"));  //배경
}

void InGame::Render()
{
	Camera::main->Set();
	skyBox->Render();
	grid->Render();
	playerInventory->Render();

}

void InGame::ResizeScreen()
{
}
