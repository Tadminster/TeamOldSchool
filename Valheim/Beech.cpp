#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"

Beech::Beech()
{
	static int index = 0;

	actor = Actor::Create();
	actor->LoadFile("Feature_Beech.xml");
	actor->name = "Beech" + to_string(index++);

	float x = RANDOM->Float(0.8f, 1.2f);
	float y = RANDOM->Float(0.4f, 0.6f);
	float z = RANDOM->Float(0.8f, 1.2f);
	actor->rotation.y = RANDOM->Float(0.0f, 360.0f) * ToRadian;
	actor->scale = Vector3(x, y, z);

	rotation = &actor->Find("RootNode")->rotation;

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 80;
}

Beech::~Beech()
{
}

void Beech::Init()
{
}

void Beech::Update()
{
	//오브젝트와 카메라의 거리 계산
	float distance = Vector3::DistanceSquared(Camera::main->GetWorldPos(), actor->GetWorldPos());
	
	// 거리가 3000.0f 이상이면 리턴(업데이트 하지 않음)
	if (distance > MAXMUM_UPDATE_DISTANCE) return;
	else LodUpdate(distance);

	FeatureProto::Update();
}

void Beech::LateUpdate()
{
	groundRay.position = actor->GetWorldPos();

	//if (MAP->ComputePicking(groundRay, rayCollisionPoint))
	//{
	//	if (actor->GetWorldPos().y > rayCollisionPoint.y)
	//	{
	//		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
	//	}
	//}
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

void Beech::LodUpdate(float distance)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;
	actor->Find("Lod3")->visible = false;

	if (distance < 1000) actor->Find("Lod0")->visible = true;			// 거리 1000 이하는 LOD0
	else if (distance < 2000) actor->Find("Lod1")->visible = true;		// 거리 2000 이하는 LOD1
	else if (distance < 3000) actor->Find("Lod3")->visible = true;		// 거리 5000 이하는 LOD3
	else return;
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

	// 나무 파괴 이펙트 재생
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, spawnPos);
	
	// 오브젝트 삭제 (나무)
	delete this;
}
