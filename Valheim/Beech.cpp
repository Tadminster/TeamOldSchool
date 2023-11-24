#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"

Beech::Beech()
{
	static int index = 0;

	actor = Actor::Create();
	actor->LoadFile("Beech.xml");
	actor->name = "Beech" + to_string(index++);

	float x = RANDOM->Float(0.8f, 1.2f);
	float y = RANDOM->Float(0.4f, 0.6f);
	float z = RANDOM->Float(0.8f, 1.2f);
	actor->scale = Vector3(x, y, z);
	actor->rotation.y = RANDOM->Float(0.0f, 360.0f) * ToRadian;



	hitPoint = 10;
}

Beech::~Beech()
{
}

void Beech::Init()
{
}

void Beech::Update()
{
	FeatureProto::Update();
	actor->Update();
}

void Beech::LateUpdate()
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

void Beech::Render()
{
	actor->Render();
}

void Beech::Release()
{
	Beech::~Beech();
}

void Beech::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Beech::LodUpdate(LodLevel lv)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;
	actor->Find("Lod3")->visible = false;

	if (lv == LodLevel::LOD0)
		actor->Find("Lod0")->visible = true;
	else if (lv == LodLevel::LOD1)
		actor->Find("Lod1")->visible = true;
	else if (lv == LodLevel::LOD3)
		actor->Find("Lod3")->visible = true;
}

void Beech::DestructionEvent()
{
	// 오브젝트 생성 (그루터기)
	FeatureProto* stump = FeatureProto::Create(FeatureType::BeechStump);
	stump->GetActor()->SetWorldPos(this->actor->GetWorldPos());

	// 오브젝트 생성 (통나무)
	FeatureProto* log = FeatureProto::Create(FeatureType::BeechLog);
	Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	log->GetActor()->SetWorldPos(spawnPos);
	log->Init();
	//log->GetActor()->rotation = this->actor->rotation;
	//log->GetActor()->scale = this->actor->scale;

	// 리스트에 오브젝트 추가
	OBJ->AddObject(stump);
	OBJ->AddObject(log);

	// 오브젝트 삭제 (나무)
	Beech::~Beech();
}
