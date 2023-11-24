#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"

Beech::Beech()
{
	actor = Actor::Create();
	actor->LoadFile("Beech.xml");

	static int index = 0;
	actor->name = "Beech" + index++;

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

	//임시로 오브젝트 파괴시 파티클효과 추가합니다------------
	// PlayParticleEffect 함수의 이펙트의 타입과 Vector3 pos 이펙트 시작위치는 개인이원하는 위치에 지정해주시면 됩니다
	//나무 자체 타격 이펙트 입니다
	PARTICLE->PlayParticleEffect(EffectType::HITBEECH, this->actor->GetWorldPos());
	//나무 파괴시 나뭇잎이 떨어지는 이펙트입니다
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, this->actor->GetWorldPos());
	//나무 타격시 발생하는 먼지 이펙트 입니다
	PARTICLE->PlayParticleEffect(EffectType::WOODHITDUST, this->actor->GetWorldPos());
	//-------------------------------------------------
	// 오브젝트 삭제 (나무)
	Beech::~Beech();
}
