#include "stdafx.h"
#include "TreeBeech.h"

TreeBeech::TreeBeech(Vector3 spawnPos, RenderType type)
{
	actor = Actor::Create();
	actor->LoadFile("Beech.xml");
	if (type == RenderType::SINGLE) 
		actor->LoadFile("Beech.xml");
	else if (type == RenderType::INSTANCING) 
		actor->LoadFile("BeechInstance.xml");

	static int index = 0;
	actor->name = "Beech" + index++;
	
	actor->SetWorldPos(spawnPos);
}

TreeBeech::~TreeBeech()
{
}

void TreeBeech::Init()
{
}

void TreeBeech::Update()
{
	actor->Update();
}

void TreeBeech::LateUpdate()
{
}

void TreeBeech::Render()
{
	actor->Render();
}

void TreeBeech::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void TreeBeech::LodUpdate(LodLevel lv)
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
