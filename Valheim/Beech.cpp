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
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());
	
	// 거리가 3000.0f 이상이면 리턴(업데이트 하지 않음)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;

	LodUpdate(playerDistance);

	FeatureProto::Update();
}

void Beech::LateUpdate()
{
	groundRay.position = actor->GetWorldPos();

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
	// 나무 아이템 생성
	for (int i = 0; i < RANDOM->Int(3, 5); i++)
	{
		ItemProto* item = ItemProto::Create(Item::Woodpile);
		Vector3 randomPos = Vector3(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(1.0f, 3.0f), RANDOM->Float(-1.0f, 1.0f));
		item->GetActor()->SetWorldPos(actor->GetWorldPos() + randomPos);
		OBJ->AddItem(item);
	}

	// 나무 파괴 이펙트 재생
	Vector3 effectPos = this->actor->GetWorldPos() + this->actor->GetUp() * 3.0f;
	PARTICLE->PlayParticleEffect(EffectType::WOODDROP, effectPos);
	
	// 오브젝트 삭제 (나무)
	delete this;
}
