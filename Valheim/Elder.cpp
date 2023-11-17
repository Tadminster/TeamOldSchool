#include "stdafx.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Elder.xml");
	actor->LoadFile("Monster_Elder_BossStone.xml");
	actor->name = "Monster_Elder";
}

Elder::~Elder()
{
}

void Elder::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(10,0,0));
}

void Elder::Update()
{
	//중력 구현
	ApplyGravity();

	actor->Update();
}

void Elder::LateUpdate()
{
	//Elder - Terrain 충돌
	SetonTerrain();

	//보스 소환 임시
	if (INPUT->KeyDown('Q')) actor->LoadFile("Monster_Elder.xml");
	else if (INPUT->KeyDown('E')) actor->LoadFile("Monster_Elder_BossStone.xml");

	//슬라이딩 벡터 초기작
	if (PLAYER->GetPlayer()->collider->Intersect(actor->collider))
	{
		PLAYER->istouch = true;
		PLAYER->MoveBack(actor);
	}
	else
	{
		PLAYER->istouch = false;
	}
}

void Elder::Render()
{
	actor->Render();
	
}

void Elder::Release()
{
}

void Elder::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Elder::IsDestroyed()
{
	return false;
}

void Elder::DestructionEvent()
{
}
