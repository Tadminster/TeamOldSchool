#include "stdafx.h"
#include "Goblin.h"
#include "Elder.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			goblin[i * 3 + j] = new Goblin(Vector3((i - 1) * 50.0f, 0, (j - 1) * 50.0f));
			unit.emplace_back(goblin[i * 3 + j]);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			goblin2[i * 2 + j] = new Goblin(Vector3((i * 2 - 1) * 25.0f, 0, (j * 2 - 1) * 25.0f));
			goblin2[i * 2 + j]->GetActor()->Find("goblin")->material->diffuseMap
				= RESOURCE->textures.Load("Monster_Goblin/goblinBlue_d.png");
			unit.emplace_back(goblin2[i * 2 + j]);
		}
	}

	

}

MonsterManager::~MonsterManager()
{

}

void MonsterManager::Init()
{
	ELDER->Init();

	for (auto& it : unit)
	{
		it->Init();
		it->Update();
	}
	/*for (int i = 0; i < 9; i++)
	{
		goblin[i]->Init();
	}
	for (int i = 0; i < 4; i++)
	{
		goblin2[i]->Init();
	}*/
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	ELDER->Update();

	for (auto& it : unit)
	{
		if ((PLAYER->GetActor()->GetWorldPos() - it->GetActor()->GetWorldPos()).Length() < 40.0f)
			it->Update();
	}
	/*for (int i = 0; i < 9; i++)
	{
		goblin[i]->Update();
	}
	for (int i = 0; i < 4; i++)
	{
		goblin2[i]->Update();
	}*/
}

void MonsterManager::LateUpdate()
{
	ELDER->LateUpdate();

	for (auto& it : unit)
	{
		if ((PLAYER->GetActor()->GetWorldPos() - it->GetActor()->GetWorldPos()).Length() < 40.0f)
			it->LateUpdate();
	}
}

void MonsterManager::RenderHierarchy()
{
	ELDER->RenderHierarchy();

	for (auto& it : unit)
	{
		it->RenderHierarchy();
	}

	/*for (int i = 0; i < 9; i++)
	{
		goblin[i]->RenderHierarchy();
	}
	for (int i = 0; i < 4; i++)
	{
		goblin2[i]->RenderHierarchy();
	}*/
}

void MonsterManager::Render()
{
	ELDER->Render();

	for (auto& it : unit)
	{
		if((PLAYER->GetActor()->GetWorldPos()-it->GetActor()->GetWorldPos()).Length()<40.0f)
			it->Render();
	}
	/*for (int i = 0; i < 9; i++)
	{
		goblin[i]->Render();
	}
	for (int i = 0; i < 4; i++)
	{
		goblin2[i]->Render();
	}*/
}
