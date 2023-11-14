#include "stdafx.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Elder.xml");
	actor->name = "Elder";

}

Elder::~Elder()
{
}

void Elder::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos());
}

void Elder::Update()
{
	//중력 구현
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;

	actor->Update();
}

void Elder::LateUpdate()
{
	//Elder - Terrain 충돌판정
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
