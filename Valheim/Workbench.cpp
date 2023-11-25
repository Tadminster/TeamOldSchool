#include "stdafx.h"
#include "StructureProto.h"
#include "Workbench.h"

Workbench::Workbench()
{
	static int index = 0;
	actor = Actor::Create("Workbench");
	actor->LoadFile("Workbench.xml");
	actor->name = "Workbench" + index++;

	//=========================
	name = "Workbench";
}

Workbench::~Workbench()
{

}

void Workbench::Init()
{
}

void Workbench::Update()
{
	StructureProto::Update();
}

void Workbench::LateUpdate()
{
}

void Workbench::Render()
{
	StructureProto::Render();
}

void Workbench::Release()
{
}

void Workbench::RenderHierarchy()
{
}

bool Workbench::ReceivedDamageEvent(float damage, WeaponType wType)
{
	return false;
}

bool Workbench::IsDestroyed()
{
	return false;
}

void Workbench::DestructionEvent()
{
}

bool Workbench::interaction()
{

	return false;
}
