	#include "stdafx.h"

	#include <list>

	#include "Prototype.h"
	#include "TreeBeech.h"

	#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{
	//mPrototypes.emplace_back(new TreeBeech());
}

void ObjectManager::Release()
{
}

void ObjectManager::Update()
{
	for (auto& prototype : mPrototypes)
	{
		prototype->Update();
	}

}

void ObjectManager::LateUpdate()
{
	for (auto& prototype : mPrototypes)
	{
		prototype->LateUpdate();
	}
}

void ObjectManager::Render()
{
	for (auto& prototype : mPrototypes)
	{
		prototype->Render();
	}
}

void ObjectManager::RenderHierarchy()
{
	ImGui::Begin("TerrainHierarchy");
	{
	}
	ImGui::End();
}

void ObjectManager::GenerateFeatures()
{
	
}
