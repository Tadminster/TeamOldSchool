#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "BeechHalfLog.h"

BeechHalfLog::BeechHalfLog()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_BeechHalfLog.xml");

	static int index = 0;
	actor->name = "BeechHalfLog" + to_string(index++);

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 50;
}

BeechHalfLog::~BeechHalfLog()
{

}

void BeechHalfLog::Init()
{

}

void BeechHalfLog::Update()
{
	actor->Update();
}

void BeechHalfLog::LateUpdate()
{

}

void BeechHalfLog::Render()
{
	actor->Render();
}

void BeechHalfLog::Release()
{
}

void BeechHalfLog::RenderHierarchy()
{

}

void BeechHalfLog::DestructionEvent()
{
	// 오브젝트 생성 (반쪽통나무)
	ItemProto* item = ItemProto::Create(Item::Woodpile);
	item->GetActor()->SetWorldPos(actor->GetWorldPos());
	OBJ->AddItem(item);

	BeechHalfLog::~BeechHalfLog();
}