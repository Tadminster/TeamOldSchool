#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Birch.h"

//Birch::Birch()
//{
//	actor = Actor::Create();
//	actor->LoadFile("Feature_Birch.xml");
//
//	static int index = 0;
//	actor->name = "Birch" + to_string(index++);
//
//	float x = RANDOM->Float(0.7f, 1.1f);
//	float y = RANDOM->Float(0.4f, 0.6f);
//	float z = RANDOM->Float(0.7f, 1.1f);
//	actor->scale = Vector3(x, y, z);
//	actor->rotation.y = RANDOM->Float(0.0f, 360.0f) * ToRadian;
//
//	rotation = &actor->Find("RootNode")->rotation;
//
//	//==================================================
//	type = FeatureArmorType::Tree;
//	hitPoint = 80;
//}

Birch::Birch()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_Birch.xml");

	static int index = 0;
	actor->name = "Birch" + to_string(index++);

	float x = RANDOM->Float(0.7f, 1.1f);
	float y = RANDOM->Float(0.4f, 0.6f);
	float z = RANDOM->Float(0.7f, 1.1f);
	actor->scale = Vector3(x, y, z);
	actor->rotation.y = RANDOM->Float(0.0f, 360.0f) * ToRadian;

	rotation = &actor->Find("RootNode")->rotation;

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 80;
}

Birch::~Birch()
{
}

void Birch::Init()
{
}

void Birch::Update()
{
	// 오브젝트와 카메라의 거리 계산
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());

	// 거리가 3000.0f 이상이면 리턴(업데이트 하지 않음)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;
	// 3000.0f 미만이면 Lod 적용
	else LodUpdate(playerDistance);

	FeatureProto::Update();
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

void Birch::LodUpdate(float distance)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;

	if (distance < 1000) actor->Find("Lod0")->visible = true;
	else if (distance < 3000) actor->Find("Lod1")->visible = true;
	else return;
}


void Birch::Release()
{
	Birch::~Birch();
}

bool Birch::ReceivedDamageEvent(float damage, WeaponType wType)
{
	// 타격 애니메이션(흔들림) 재생시간 설정
	hitAnimDuration = 0.3f;

	// 타격 이펙트 재생
	PARTICLE->PlayParticleEffect(EffectType::HITWOOD, PLAYER->GetCollisionPoint());

	// 데미지 계산
	if (wType == WeaponType::Axe)
	{
		if (type == FeatureArmorType::Tree) damage *= 2.0f;
	}
	else if (wType == WeaponType::Pickaxe)
	{
		if (type == FeatureArmorType::Rock) damage *= 2.0f;
	}

	// Birch는 20데미지 무시
	damage = max(0.0f, damage - 20.0f);

	// 데미지 적용
	hitPoint = max(0.0f, hitPoint - damage);

	UIM->AddDamageText((int)damage, PLAYER->GetCollisionPoint());

	return true;
}

void Birch::DestructionEvent()
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
