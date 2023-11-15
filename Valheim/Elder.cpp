#include "stdafx.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Elder.xml");
	actor->name = "Monster_Elder";

	bossStone = Actor::Create();
	bossStone->LoadFile("Monster_Elder_BossStone.xml");
	bossStone->name = "Monster_Elder_BossStone";
}

Elder::~Elder()
{
}

void Elder::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos());
	bossStone->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(5,0,0));
}

void Elder::Update()
{
	//중력 구현
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;

	actor->Update();
	bossStone->Update();
}

void Elder::LateUpdate()
{
	//Elder - Terrain 충돌판정---------------------------------------------------
	Ray ElderTop;
	ElderTop.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
	ElderTop.direction = Vector3(0, -1, 0);
	Vector3 hit;
	if (Utility::RayIntersectMap(ElderTop, MAP, hit))
	{
		if (actor->GetWorldPos().y - hit.y < 0.1f) {
			actor->SetWorldPosY(hit.y);
			isLand = true;
		}
		else isLand = false;
	}
	
	//Elder_BossStone - Terrain 충돌판정---------------------------------------------
	Ray Elder_BossStoneTop;
	Elder_BossStoneTop.position = bossStone->GetWorldPos() + Vector3(0, 1000, 0);
	Elder_BossStoneTop.direction = Vector3(0, -1, 0);
	Vector3 hit2;
	if (Utility::RayIntersectMap(Elder_BossStoneTop, MAP, hit2))
	{
		bossStone->SetWorldPosY(hit2.y - 1.5f);
	}

	//
	if (PLAYER->GetPlayer()->collider->Intersect(bossStone->collider))
	{
		PLAYER->MoveBack();
	}
	else
	{

	}
}

void Elder::Render()
{
	actor->Render();
	bossStone->Render();
}

void Elder::Release()
{
}

void Elder::RenderHierarchy()
{
	actor->RenderHierarchy();
	bossStone->RenderHierarchy();
}

bool Elder::IsDestroyed()
{
	return false;
}

void Elder::DestructionEvent()
{
}
