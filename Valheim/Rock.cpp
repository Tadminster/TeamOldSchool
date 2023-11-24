#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Rock.h"

Rock::Rock()
{
	actor = Actor::Create();
	actor->LoadFile("Rock.xml");

	static int index = 0;
	actor->name = "Rock" + index++;

	hitPoint = 10;
}

Rock::~Rock()
{
}

void Rock::Init()
{
}

void Rock::Update()
{
	FeatureProto::Update();
	actor->Update();
}

void Rock::LateUpdate()
{
	groundRay.position = actor->GetWorldPos();

	if (MAP->ComputePicking(groundRay, rayCollisionPoint))
	{
		if (actor->GetWorldPos().y > rayCollisionPoint.y)
		{
			actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
		}
	}
}

void Rock::Render()
{
	actor->Render();
}

void Rock::Release()
{
	Rock::~Rock();
}

void Rock::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Rock::LodUpdate(LodLevel lv)
{
	//actor->Find("Lod0")->visible = false;
	//actor->Find("Lod1")->visible = false;
	//actor->Find("Lod3")->visible = false;

	//if (lv == LodLevel::LOD0)
	//	actor->Find("Lod0")->visible = true;
	//else if (lv == LodLevel::LOD1)
	//	actor->Find("Lod1")->visible = true;
	//else if (lv == LodLevel::LOD3)
	//	actor->Find("Lod3")->visible = true;
}

void Rock::DestructionEvent()
{
	// 아이템 생성 (stone)
	ItemProto* rock = ItemProto::Create(Item::Stone);
	Vector3 spawnPos = this->actor->GetWorldPos();
	Vector3 randomPos = Vector3(RANDOM->Float(-0.5f, 0.5f), RANDOM->Float(0.0f, 1.0f), RANDOM->Float(-0.5f, 0.5f));
	rock->GetActor()->SetWorldPos(spawnPos + randomPos);

	// 리스트에 아이템 추가
	OBJ->AddItem(rock);

	// 오브젝트 삭제
	Rock::~Rock();
}
