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
	groundRay.position = actor->GetWorldPos();

	if (MAP->ComputePicking(groundRay, rayCollisionPoint))
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
	// ������Ʈ ���� (�����볪��)
	FeatureProto* halfLog1 = FeatureProto::Create(FeatureType::BeechHalfLog);
	Vector3 spawnPos1 = this->actor->GetWorldPos();
	halfLog1->GetActor()->SetWorldPos(spawnPos1);
	//halfLog1->GetActor()->rotation = this->actor->rotation;
	//halfLog1->GetActor()->scale = this->actor->scale;
	halfLog1->Init();

	FeatureProto* halfLog2 = FeatureProto::Create(FeatureType::BeechHalfLog);
	Vector3 spawnPos2 = this->actor->GetWorldPos() + this->actor->GetUp() * 5;
	halfLog2->GetActor()->SetWorldPos(spawnPos2);
	//halfLog2->GetActor()->rotation = this->actor->rotation;
	//halfLog2->GetActor()->scale = this->actor->scale;
	halfLog2->Init();

	// ����Ʈ�� ������Ʈ �߰�
	OBJ->AddObject(halfLog1);
	OBJ->AddObject(halfLog2);

	// ������Ʈ ���� (�볪��)
	BeechLog::~BeechLog();
}

