#include "stdafx.h"
#include "FeatureProto.h"
#include "Shipwreck.h"

Shipwreck::Shipwreck()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_Shipwreck.xml");
	actor->name = "Shipwreck";

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 100;
}

Shipwreck::~Shipwreck()
{
}

void Shipwreck::Init()
{
}

void Shipwreck::Update()
{
	//오브젝트와 카메라의 거리 계산
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());

	// 거리가 2000.0f 이상이면 리턴(업데이트 하지 않음)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;

	LodUpdate(playerDistance);

	FeatureProto::Update();
}

void Shipwreck::LateUpdate()
{
}

void Shipwreck::Render()
{
	actor->Render();
}

void Shipwreck::Release()
{
	Shipwreck::~Shipwreck();
}

void Shipwreck::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Shipwreck::ReceivedDamageEvent(float damage, WeaponType wType)
{
	FeatureProto::ReceivedDamageEvent(damage, wType);

	// 나무 타격 이펙트
	PARTICLE->PlayParticleEffect(EffectType::HITWOOD, PLAYER->GetCollisionPoint());

	// 나무 타격 사운드
	SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(TREE_HIT_01, TREE_HIT_07));
	SOUND->Play(randomPlay);

	return true;
}

void Shipwreck::DestructionEvent()
{
	// 나무 아이템 생성
	for (int i = 0; i < RANDOM->Int(8, 10); i++)
	{
		ItemProto* item = ItemProto::Create(Item::Woodpile);
		Vector3 randomPos = Vector3(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(1.0f, 3.0f), RANDOM->Float(-1.0f, 1.0f));
		item->GetActor()->SetWorldPos(actor->GetWorldPos() + randomPos);
		OBJ->AddItem(item);
	}

	// 나무 파괴 이펙트
	Vector3 effectPos = this->actor->GetWorldPos() + this->actor->GetUp() * 8.0f;
	PARTICLE->PlayParticleEffect(EffectType::WOODDROP, effectPos);

	// 오브젝트 삭제 (나무)
	delete this;
}
