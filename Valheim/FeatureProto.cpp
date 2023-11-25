#include "stdafx.h"
//#include "Prototype.h"

#include "Birch.h"
#include "Beech.h"
#include "BeechStump.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"
#include "Rock.h"

#include "FeatureProto.h"

FeatureProto* FeatureProto::Create(FeatureType type)
{
	switch (type)
	{
		case FeatureType::Birch:
			return new Birch();
		case FeatureType::Beech:
			return new Beech();
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

bool FeatureProto::ReceivedDamageEvent(float damage)
{
	// 타격 이펙트 재생
	PARTICLE->PlayParticleEffect(EffectType::HITBEECH, PLAYER->GetCollisionPoint());

	// 타격 애니메이션 재생시간 설정
	hitAnimDuration = 0.3f;

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
