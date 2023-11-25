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
	// 아이템 생성 (나뭇가지) (예정)
	//FeatureProto* halfLog = FeatureProto::Create(FeatureType::BeechHalfLog);
	//Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	//halfLog->GetActor()->SetWorldPos(spawnPos);

	// 리스트에 오브젝트 추가
	//OBJ->AddObject(halfLog);

	// 오브젝트 삭제 (그루터기)
	BeechStump::~BeechStump();
}


