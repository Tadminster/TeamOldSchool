#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "BeechStump.h"

BeechStump::BeechStump()
{
	actor = Actor::Create();
	actor->LoadFile("BeechStump.xml");

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
	actor->Update();
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
	BeechStump::~BeechStump();
}


