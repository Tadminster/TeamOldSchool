#include "stdafx.h"
#include "InGame.h"
#include "Prototype.h"
#include "Item.h"
#include "BattleItem.h"
#include "LivingItem.h"
#include "ConsumeItem.h"
#include "ResourceItem.h"
#include "Inventory.h"

InGame::InGame()
{
	tempCamera = Camera::Create();
	tempCamera->LoadFile("Cam.xml");
	Camera::main = tempCamera;

	grid = Grid::Create();

	skyBox = Sky::Create();
	skyBox->LoadFile("Sky1.xml");

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
	}
	ImGui::End();

	Camera::main->ControlMainCam();
	Camera::main->Update();
	grid->Update();
	skyBox->Update();
}

void InGame::LateUpdate()
{
}

void InGame::PreRender()
{
	skyBox->Render(RESOURCE->shaders.Load("0.Sky.hlsl"));  //¹è°æ
	//skyBox->Render(RESOURCE->shaders.Load("0.Sky_CR.hlsl"));
}

void InGame::Render()
{
	Camera::main->Set();
	skyBox->Render();
	grid->Render();
}

void InGame::ResizeScreen()
{
}
