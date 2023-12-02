#include "stdafx.h"
//#include "Prototype.h"

#include "Birch.h"
#include "Beech.h"
#include "BeechInstancing.h"
#include "BeechStump.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"
#include "Rock.h"
#include "Karve.h"
#include "Shipwreck.h"

#include "FeatureProto.h"

FeatureProto* FeatureProto::Create(FeatureType featureType)
{
	switch (featureType)
	{
		case FeatureType::Birch:
			return new Birch();
		case FeatureType::Beech:
			return new Beech();
		//case FeatureType::BeechInstancing:
		//	return new BeechInstancing();
		//case FeatureType::BeechStump:
		//	return new BeechStump();
		//case FeatureType::BeechLog:
		////	return new BeechLog();
		//case FeatureType::BeechHalfLog:
		//	return new BeechHalfLog();
		case FeatureType::Rock:
			return new Rock();
		case FeatureType::Karve:
			return new Karve();
		case FeatureType::Shipwreck:
			return new Shipwreck();
		default:
			throw std::invalid_argument("error");
			return nullptr;
	}
}

void FeatureProto::Init()
{
	groundRay.direction = Vector3(0.0f, -1.0f, 0.0f);
}

void FeatureProto::Update()
{
	// 체력이 0 이하이면
	if (hitPoint <= 0)
	{
		// 파괴 이벤트
		DestructionEvent();
	}

	//// 거리가 10.0f 이하이면
	if (playerDistance < 10.0f)
	{
		// 플레이어 공격 검사
		if (PLAYER->CleanHit(this->GetActor()->collider) && PLAYER->CleanFrame())
		{
			ReceivedDamageEvent(PLAYER->GetWeaponDMG(), PLAYER->GetWeaponType());
		}

		// 슬라이딩 벡터
		if (PLAYER->GetCollider()->Intersect(this->GetActor()->collider))
		{
			PLAYER->MoveBack(this->GetActor());
		}
	}
	if (ELDER->GetIsElder())
	{
		if ((ELDER->GetActor()->GetWorldPos() - actor->GetWorldPos()).Length() < 10.0f)
		{
			if (ELDER->GetActor()->collider->Intersect(this->GetActor()->collider))
			{
				ReceivedDamageEvent(100, WeaponType::Blunt, Vector3(0, 0, 0));
			}
		}
	}

	// 데미지를 입었을 때 애니메이션 재생
	ReceivedDamageAnimation();

	UpdateLight();

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

	// 데미지 적용
	hitPoint = max(0.0f, hitPoint - damage);

	UIM->AddDamageText((int)damage, PLAYER->GetCollisionPoint());

	return true;
}

bool FeatureProto::ReceivedDamageEvent(float damage, WeaponType wType, Vector3 dmgPos)
{
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

	// 데미지 적용
	hitPoint = max(0.0f, hitPoint - damage);

	//데미지 텍스트 출력 위치
	if (dmgPos == Vector3()) dmgPos = actor->GetWorldPos() + Vector3(0, actor->scale.y * 0.5f, 0);
	
	UIM->AddDamageText((int)damage, dmgPos);

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

void FeatureProto::UpdateLight()
{
	float lightRatio = max(0.1f, LIGHT->GetTimeRatio());
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);

	actor->Find("Mesh")->material->diffuse = color;
	actor->Find("Mesh")->material->ambient = color;
}
