#include "stdafx.h"
#include "Troll.h"

Troll::Troll()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Troll.xml");
	actor->name = "Troll";

}

Troll::~Troll()
{
}

void Troll::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos());
}

void Troll::Update()
{
	//중력 구현
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;

	actor->Update();
}

void Troll::LateUpdate()
{
	//Troll - Terrain 충돌판정
	Ray trollTop;
	trollTop.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
	trollTop.direction = Vector3(0, -1, 0);
	Vector3 hit;
	if (Utility::RayIntersectMap(trollTop, MAP, hit))
	{
		if (actor->GetWorldPos().y - hit.y < 0.1f) {
			actor->SetWorldPosY(hit.y);
			isLand = true;
		}
		else isLand = false;
	}
}

void Troll::Render()
{
	actor->Render();
}

void Troll::Release()
{
}

void Troll::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Troll::IsDestroyed()
{
	return false;
}

void Troll::DestructionEvent()
{
}
