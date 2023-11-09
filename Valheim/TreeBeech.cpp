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