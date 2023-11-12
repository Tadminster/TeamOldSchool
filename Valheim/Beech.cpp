#include "stdafx.h"
#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"

Beech::Beech()
{
	actor = Actor::Create();
	actor->LoadFile("Beech.xml");

	static int index = 0;
	actor->name = "Beech" + index++;

	hitPoint = 10;
}

Beech::~Beech()
{
	cout << "Beech destructor" << endl;
}

void Beech::Init()
{
}

void Beech::Update()
{
	FeatureProto::Update();
	actor->Update();
}

void Beech::LateUpdate()
{
}

void Beech::Render()
{
	actor->Render();
}

void Beech::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Beech::LodUpdate(LodLevel lv)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;
	actor->Find("Lod3")->visible = false;

	if (lv == LodLevel::LOD0)
		actor->Find("Lod0")->visible = true;
	else if (lv == LodLevel::LOD1)
		actor->Find("Lod1")->visible = true;
	else if (lv == LodLevel::LOD3)
		actor->Find("Lod3")->visible = true;
}

void Beech::ReceivedDamageEvent(int damage)
{
	hitPoint -= damage;
}

void Beech::DestructionEvent()
{
	FeatureProto* object = FeatureProto::Create(FeatureType::BeechLog);
	Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0, 4, 0);
	object->GetActor()->SetWorldPos(spawnPos);
	//object->GetActor()->rotation = this->actor->rotation;
	//object->GetActor()->scale = this->actor->scale;
	OBJ->AddObject(object);
	Beech::~Beech();
}
