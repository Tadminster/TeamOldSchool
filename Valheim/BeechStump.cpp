#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "BeechStump.h"

BeechStump::BeechStump()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_BeechStump.xml");

	static int index = 0;
	actor->name = "BeechStump" + to_string(index++);

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 50;
}

BeechStump::~BeechStump()
{

}

void BeechStump::Init()
{

}

void BeechStump::Update()
{
	// ������Ʈ�� ī�޶��� �Ÿ� ���
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());

	// �Ÿ��� 2000.0f �̻��̸� ����(������Ʈ ���� ����)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;

	FeatureProto::Update();
}

void BeechStump::LateUpdate()
{

}

void BeechStump::Release()
{
}

void BeechStump::Render()
{
	actor->Render();
}

void BeechStump::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void BeechStump::DestructionEvent()
{
	// ������ ���� (��������) (����)
	//FeatureProto* halfLog = FeatureProto::Create(FeatureType::BeechHalfLog);
	//Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	//halfLog->GetActor()->SetWorldPos(spawnPos);

	// ����Ʈ�� ������Ʈ �߰�
	//OBJ->AddObject(halfLog);

	// ������Ʈ ���� (�׷��ͱ�)
	delete this;
}


