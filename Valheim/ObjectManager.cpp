	#include "stdafx.h"

	#include <list>

	#include "Prototype.h"
	#include "TreeBeech.h"

	#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{
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
}

void ObjectManager::GenerateFeatures()
{
}
