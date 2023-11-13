#include "stdafx.h"
#include "Prototype.h"
#include "FeatureProto.h"
#include "Birch.h"

Birch::Birch()
{
	actor = Actor::Create();
	actor->LoadFile("Birch.xml");

	static int index = 0;
	actor->name = "Birch" + index++;

	hitPoint = 10;
}

Birch::~Birch()
{
}

void Birch::Init()
{
}

void Birch::Update()
{
	FeatureProto::Update();
	actor->Update();
}

void Birch::LateUpdate()
{
}

void Birch::Render()
{
	actor->Render();
}

void Birch::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Birch::LodUpdate(LodLevel lv)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;

	if (lv == LodLevel::LOD0)
		actor->Find("Lod0")->visible = true;
	else if (lv == LodLevel::LOD1 || lv == LodLevel::LOD3)
		actor->Find("Lod1")->visible = true;
}

void Birch::ReceivedDamageEvent(int damage)
{
	hitPoint -= damage;
}

void Birch::Release()
{
	Birch::~Birch();
}

void Birch::DestructionEvent()
{
	// 오브젝트 생성 (그루터기)
	FeatureProto* stump = FeatureProto::Create(FeatureType::BeechStump);
	stump->GetActor()->SetWorldPos(this->actor->GetWorldPos());

	// 오브젝트 생성 (통나무)
	FeatureProto* log = FeatureProto::Create(FeatureType::BeechLog);
	Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	log->GetActor()->SetWorldPos(spawnPos);
	//log->GetActor()->rotation = this->actor->rotation;
	//log->GetActor()->scale = this->actor->scale;

	// 리스트에 오브젝트 추가
	OBJ->AddObject(stump);
	OBJ->AddObject(log);

	// 오브젝트 삭제 (나무)
	Birch::~Birch();
}
