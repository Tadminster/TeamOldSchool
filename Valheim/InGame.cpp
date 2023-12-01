#include "stdafx.h"
#include "ItemProto.h"
#include "SoundDB.h"
#include "MonsterManager.h"
#include "InGame.h"

extern int loadCount;

InGame::InGame()
{
	tempCamera = Camera::Create("tempCamera");
	tempCamera->LoadFile("Cam.xml");
	loadCount++; // 1

	grid = Grid::Create();
	loadCount++; // 2

	soundDB = new SoundDB();
	loadCount++; // 3

	scattering = new Scattering();
	loadCount++; // 4

	
	RESOURCE->shaders.Load("0.Sky_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("0.SkySphere_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_Shadow.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("5.Cube_Water.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_CR.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_Shadow.hlsl")->LoadGeometry();
	RESOURCE->shaders.Load("4.Instance_Water.hlsl")->LoadGeometry();
	loadCount++; // 5
}

InGame::~InGame()
{

}

void InGame::Init()
{
	GM->Init();
	UIM->Init();
	soundDB->Init();

	OBJ->Init();
	PLAYER->Init();
	MONSTER->Init();
	// ������� ���
	SOUND->Play(BGM_HOMEBASE);
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
		if (DEBUGMODE)
		{
			grid->RenderHierarchy();
			tempCamera->RenderHierarchy();
		}

		MAP->RenderHierarchy();
		SEA->RenderHierarchy();
		OBJ->RenderHierarchy();
		PARTICLE->RenderHierarchy();
		PLAYER->RenderHierarchy();
		MONSTER->RenderHierarchy();
	}
	ImGui::End();

	// F1 : �����ȯ
	if (INPUT->KeyDown(VK_F1))
	{
		DEBUGMODE = !DEBUGMODE;
	}
	// F2 : ī�޶���ȯ
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

	// ����� ��忡�� ������Ʈ
	if (DEBUGMODE)
	{
		grid->Update();
	}

	// ī�޶� ���� ����
	if (isDebugCam)
	{
		if (INPUT->KeyDown(VK_F3)) isDebugCamControl = !isDebugCamControl;
		if (isDebugCamControl) Camera::main->ControlMainCam();
	}
	else PLAYER->AvtivatePlayerCam();

	Camera::main->Update();
	GM->Update();
	SEA->Update();
	OBJ->Update();
	PARTICLE->Update();
	PLAYER->Update();
	UIM->Update();
	MONSTER->Update();
	//����Ÿ���� �޾ƿ��� �׿����� ������ ������ ��ȭ��ŵ�ϴ�
	
	LIGHT->UpdateDirection();
}

void InGame::LateUpdate()
{
	OBJ->LateUpdate();
	PLAYER->LateUpdate();
	MONSTER->LateUpdate();
	PARTICLE->LateUpdate();

	UIM->LateUpdate();
}

void InGame::PreRender()
{
	Camera::main->Set();

	scattering->DrawPass1();
	//LIGHT->Set();

	MAP->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));

	// ���ݻ� ������
	SEA->SetReflectionTarget();
	OBJ->RefractionRender();
	PLAYER->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	//MAP->Render(RESOURCE->shaders.Load("5.Cube_Water.hlsl"));

	// ������ ������
	SEA->SetRefractionTarget();
	PLAYER->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	MAP->Render(RESOURCE->shaders.Load("5.Cube_Water.hlsl"));
}

void InGame::Render()
{
	Camera::main->Set();
	scattering->DrawPass2();
	//LIGHT->Set();

	if (DEBUGMODE)
	{
		grid->Render();
	}
	GM->Render();
	MAP->Render();
	SEA->Render();
	OBJ->Render();
	PLAYER->Render();
	PARTICLE->Render();
	UIM->Render();
	MONSTER->Render();
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
