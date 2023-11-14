#include "stdafx.h"
#include "Prototype.h"
#include "FeatureProto.h"
#include "BeechLog.h"

BeechLog::BeechLog()
{
	actor = Actor::Create();
	actor->LoadFile("BeechLog.xml");

	static int index = 0;
	actor->name = "BeechLog" + index++;

	hitPoint = 10;
}

BeechLog::~BeechLog()
{

}

void BeechLog::Init()
{

}

void BeechLog::Update()
{
	actor->Update();
}

void BeechLog::LateUpdate()
{
	ray.position = actor->GetWorldPos();

	if (MAP->ComputePicking(ray, rayCollisionPoint))
	{	
		if (actor->GetWorldPos().y > rayCollisionPoint.y)
		{
			actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
		}
	}
}

void BeechLog::Render()
{
	actor->Render();
}

void BeechLog::Release()
{
}

void BeechLog::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void BeechLog::ReceivedDamageEvent(int damage)
{
	hitPoint -= damage;
}

void BeechLog::DestructionEvent()
{
	// 오브젝트 생성 (반쪽통나무)
	FeatureProto* halfLog1 = FeatureProto::Create(FeatureType::BeechHalfLog);
	Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	halfLog1->GetActor()->SetWorldPos(spawnPos);
	//halfLog->GetActor()->rotation = this->actor->rotation;
	//halfLog->GetActor()->scale = this->actor->scale;

	FeatureProto* halfLog2 = FeatureProto::Create(FeatureType::BeechHalfLog);
	Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	halfLog2->GetActor()->SetWorldPos(spawnPos);

	// 리스트에 오브젝트 추가
	OBJ->AddObject(halfLog1);
	OBJ->AddObject(halfLog2);

	// 오브젝트 삭제 (통나무)
	BeechLog::~BeechLog();
}

