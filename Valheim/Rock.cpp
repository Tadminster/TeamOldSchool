#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Rock.h"

Rock::Rock()
{
	actor = Actor::Create();
	if (RANDOM->Int(0, 1)) actor->LoadFile("Rock1.xml");
	else actor->LoadFile("Rock2.xml");
	static int index = 0;
	actor->name = "Rock" + to_string(index++);

	float x = RANDOM->Float(1.0f, 3.0f);
	float y = RANDOM->Float(1.0f, 3.0f);
	float z = RANDOM->Float(1.0f, 3.0f);
	actor->scale = Vector3(x, y, z);
	actor->collider->rotation = actor->rotation;

	hitPoint = 10;

	rotation = &actor->Find("RootNode")->rotation;
}

Rock::~Rock()
{
}

void Rock::Init()
{
}

void Rock::Update()
{
	// 오브젝트와 카메라의 거리 계산
	float distance = Vector3::DistanceSquared(Camera::main->GetWorldPos(), actor->GetWorldPos());

	// 거리가 3000.0f 이상이면 리턴(업데이트 하지 않음)
	if (distance > MAXMUM_UPDATE_DISTANCE) return;

	FeatureProto::Update();
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
