#include "stdafx.h"
#include "Goblin.h"
#include "Elder.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	for (int i = 0; i < 9; i++)
	{
		goblin[i] = new Goblin();
		
	}
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Init()
{
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
}

void MonsterManager::LateUpdate()
{
}

void MonsterManager::RenderHierarchy()
{
}

void MonsterManager::Render()
{
}
