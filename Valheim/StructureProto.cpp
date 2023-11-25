#include "stdafx.h"

#include "Workbench.h"
#include "StructureProto.h"

StructureProto* StructureProto::Create(StructureName name)
{
	switch (name)
	{
	case StructureName::Workbench:
		return new Workbench();
	//case StructureName::Workbench:
		//return new Workbench();
	default:
		throw std::invalid_argument("error");
	}
}

void StructureProto::Init()
{
}

void StructureProto::Update()
{
	actor->Update();
}

void StructureProto::LateUpdate()
{
}

void StructureProto::Render()
{
	actor->Render();
}

bool StructureProto::ReceivedDamageEvent(float damage)
{
	return false;
}

bool StructureProto::IsDestroyed()
{
	return false;
}

void StructureProto::DestructionEvent()
{
}
