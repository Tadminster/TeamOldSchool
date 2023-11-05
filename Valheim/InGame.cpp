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
	// ����ü �ؽ�ó �������� ���̴�
	// 1031 ȯ�����_2 20:00 ����
	skyBox->Render(RESOURCE->shaders.Load("0.Sky.hlsl"));  //���
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
