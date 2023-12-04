#include "stdafx.h"
#include "Goblin.h"
#include "Elder.h"
#include "Elder_Stone.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			goblin[i * 3 + j] = new Goblin(Vector3((i - 1) * 50.0f, -1.0f, (j - 1) * 50.0f));
			unit.emplace_back(goblin[i * 3 + j]);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			goblin2[i * 2 + j] = new Goblin(Vector3((i * 2 - 1) * 25.0f, -1.0f, (j * 2 - 1) * 25.0f));
			goblin2[i * 2 + j]->GetActor()->Find("goblin")->material->diffuseMap
				= RESOURCE->textures.Load("Monster_Goblin/goblinBlue_d.png");
			unit.emplace_back(goblin2[i * 2 + j]);
		}
	}

	for (int i = 0; i < JELLYFISHNUM; i++)
	{
		monster01[i] = Actor::Create();
		monster01[i]->LoadFile("Unit/Monster_JellyFish.xml");
		monster01[i]->name = "JellyFish" + to_string(i+1);
	}

	stone = new Elder_Stone();
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

	for (int i = 0; i < JELLYFISHNUM; i++)
	{
		monsterPos[i] = Vector3(RANDOM->Float(-50.0f , 50.0f), RANDOM->Float(-3.0f, 0.0f), RANDOM->Float(-50.0f, 50.0f));
		monster01[i]->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	if (!ELDER->GetIsDeath()) ELDER->Update();

	for (int i = 0; i < unit.size(); i++)
	{
		if (unit[i]->IsDestroyed())
		{
			unit[i]->Release();
			unit.erase(unit.begin() + i);
		}
	}

	ELDER->IsDestroyed();

	for (auto& it : unit)
	{
		if ((PLAYER->GetActor()->GetWorldPos() - it->GetActor()->GetWorldPos()).Length() < 30.0f)
		{
			it->Update();
		}
	}

	Vector3 dir = PLAYER->GetActor()->GetWorldPos();
	dir.y = 0.0f;
	dir.Normalize();

	for (int i = 0; i < JELLYFISHNUM; i++)
	{
		monster01[i]->SetWorldPos(dir * 150.0f + monsterPos[i]);
		monster01[i]->Update();
	}
	stone->Update();
}

void MonsterManager::LateUpdate()
{
	if(!ELDER->GetIsDeath()) ELDER->LateUpdate();

	for (auto& it : unit)
	{
		if ((PLAYER->GetActor()->GetWorldPos() - it->GetActor()->GetWorldPos()).Length() < 30.0f)
		{
			it->LateUpdate();
		}
			
	}

	stone->LateUpdate();
}

void MonsterManager::RenderHierarchy()
{
	ELDER->RenderHierarchy();

	for (auto& it : unit)
	{
		it->RenderHierarchy();
	}

	for (int i = 0; i < JELLYFISHNUM; i++)
	{
		monster01[i]->RenderHierarchy();
	}
}

void MonsterManager::Render()
{
	if (!ELDER->GetIsDeath()) ELDER->Render();

	for (auto& it : unit)
	{
		if ((PLAYER->GetActor()->GetWorldPos() - it->GetActor()->GetWorldPos()).Length() < 30.0f)
		{
			it->Render();
		}
	}
	
	for (int i = 0; i < JELLYFISHNUM; i++)
	{
		monster01[i]->Render();
	}

	stone->Render();
}
