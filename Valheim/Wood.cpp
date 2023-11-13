#include "stdafx.h"
#include "Item.h"
#include "ResourceItem.h"
#include "Wood.h"

Wood::Wood(Vector3 spwanpos)
{
	actor = Actor::Create("Wood");
	actor->LoadFile("woodpile.xml");
	actor->name = "Wood";
	actor->SetWorldPos(spwanpos);

	itemName = "Wood";
	itemWeight = 2;
}

Wood::~Wood()
{

}

void Wood::CreateItem()
{

}

void Wood::EquipItem()
{

}

void Wood::DestroyItem()
{

}

void Wood::FixItem()
{

}

void Wood::Init()
{
}

void Wood::Update()
{
	actor->Update();
}

void Wood::LateUpdate()
{
}

void Wood::Render()
{
	actor->Render();
}

void Wood::RenderHierarchy()
{
	ImGui::Begin("Hierarchy");
	{
		actor->RenderHierarchy();
	}
	ImGui::End();
}

void Wood::Release()
{
}
