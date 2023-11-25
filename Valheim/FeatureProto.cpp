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

bool FeatureProto::ReceivedDamageEvent(int damage)
{
	// HP�� 0���ϸ� return false
	if (hitPoint <= 0) return false;

	// Ÿ�� ����Ʈ ���
	// ���� Ÿ���� ��ȯ�Լ� ��������� ���� ��ġ �������� ����
	PARTICLE->PlayParticleEffect(EffectType::HITBEECH, this->actor->GetWorldPos());

	// HP ����
	hitPoint -= damage;

	return true;
}

void FeatureProto::DestructionEvent()
{
}
