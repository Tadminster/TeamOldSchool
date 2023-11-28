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
	//�ӽ÷� ���� Ÿ�ݽ� ����Ʈ�߻���ġ ��Ƶξ����ϴ�!
	Vector3 leafDropPos = PLAYER->GetCollisionPoint() + Vector3(0, 5, 0);
	// Ÿ�� ����Ʈ ���
	PARTICLE->PlayParticleEffect(EffectType::HITBEECH, PLAYER->GetCollisionPoint());
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, leafDropPos);

	// Ÿ�� �ִϸ��̼�(��鸲) ����ð� ����
	hitAnimDuration = 0.3f;

	// ������ ���
	if (wType == WeaponType::Axe)
	{
		if (type == FeatureArmorType::Tree) damage *= 2.0f;
	}
	else if (wType == WeaponType::Pickaxe)
	{
		if (type == FeatureArmorType::Rock) damage *= 2.0f;
	}

	//cout << "ü�� : " << hitPoint << endl;
	//cout << "������ : " << damage << endl;
	// ������ ����
	hitPoint = max(0.0f, hitPoint - damage);

	UIM->AddDamageText((int)damage, PLAYER->GetCollisionPoint());
	//cout << "���� ü�� : " << hitPoint << endl;

	return true;
}

void FeatureProto::ReceivedDamageAnimation()
{
	if (hitAnimDuration <= 0.0f) return;

	hitAnimDuration -= DELTA;

	// ������ �������� ��鸲
	rotation->x = clamp(rotation->x + (RANDOM->Int(0, 1) ? 0.01f : -0.01f), -0.01f, 0.01f);
	rotation->z = clamp(rotation->z + (RANDOM->Int(0, 1) ? 0.01f : -0.01f), -0.01f, 0.01f);
}

void FeatureProto::DestructionEvent()
{
}
