#include "stdafx.h"
//#include "Prototype.h"

#include "Birch.h"
#include "Beech.h"
#include "BeechInstancing.h"
#include "BeechStump.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"
#include "Rock.h"

#include "FeatureProto.h"

FeatureProto* FeatureProto::Create(FeatureType featureType)
{
	switch (featureType)
	{
		case FeatureType::Birch:
			return new Birch();
		case FeatureType::Beech:
			return new Beech();
		case FeatureType::BeechInstancing:
			return new BeechInstancing();
		case FeatureType::BeechStump:
			return new BeechStump();
		case FeatureType::BeechLog:
			return new BeechLog();
		case FeatureType::BeechHalfLog:
			return new BeechHalfLog();
		case FeatureType::Rock:
			return new Rock();
		default:
			throw std::invalid_argument("error");
	}
}

void FeatureProto::Init()
{
	groundRay.direction = Vector3(0.0f, -1.0f, 0.0f);
}

void FeatureProto::Update()
{
	if (hitPoint <= 0)
	{
		DestructionEvent();
	}

	ReceivedDamageAnimation();

	actor->Update();
}

void FeatureProto::LateUpdate()
{
}

void FeatureProto::Render()
{
}

void FeatureProto::Release()
{
}

void FeatureProto::RenderHierarchy()
{
}

bool FeatureProto::ReceivedDamageEvent(float damage, WeaponType wType)
{
	//임시로 나무 타격시 이펙트발생위치 잡아두었습니다!
	Vector3 leafDropPos = PLAYER->GetCollisionPoint() + Vector3(0, 5, 0);
	// 타격 이펙트 재생
	PARTICLE->PlayParticleEffect(EffectType::HITBEECH, PLAYER->GetCollisionPoint());
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, leafDropPos);

	// 타격 애니메이션(흔들림) 재생시간 설정
	hitAnimDuration = 0.3f;

	// 데미지 계산
	if (wType == WeaponType::Axe)
	{
		if (type == FeatureArmorType::Tree) damage *= 2.0f;
	}
	else if (wType == WeaponType::Pickaxe)
	{
		if (type == FeatureArmorType::Rock) damage *= 2.0f;
	}

	//cout << "체력 : " << hitPoint << endl;
	//cout << "데미지 : " << damage << endl;
	// 데미지 적용
	hitPoint = max(0.0f, hitPoint - damage);

	UIM->AddDamageText((int)damage, PLAYER->GetCollisionPoint());
	//cout << "남은 체력 : " << hitPoint << endl;

	return true;
}

void FeatureProto::ReceivedDamageAnimation()
{
	if (hitAnimDuration <= 0.0f) return;

	hitAnimDuration -= DELTA;

	// 랜덤한 방향으로 흔들림
	rotation->x = clamp(rotation->x + (RANDOM->Int(0, 1) ? 0.01f : -0.01f), -0.01f, 0.01f);
	rotation->z = clamp(rotation->z + (RANDOM->Int(0, 1) ? 0.01f : -0.01f), -0.01f, 0.01f);
}

void FeatureProto::DestructionEvent()
{
}
