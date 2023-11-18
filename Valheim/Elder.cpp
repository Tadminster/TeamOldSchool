#include "stdafx.h"
#include "ElderState.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Elder_BossStone.xml");
	actor->LoadFile("Monster_Elder.xml");
	actor->name = "Monster_Elder";

	state = Elder_OpeningState::GetInstance();
}

Elder::~Elder()
{
}

void Elder::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(10,0,0));
	state->Opening(this);
}

void Elder::Update()
{
	
	if (state == Elder_OpeningState::GetInstance())
	{
		ImGui::Text("opening");
	}
	else if (state == Elder_IdleState::GetInstance())
	{
		ImGui::Text("idle");
	}
	else if (state == Elder_WalkState::GetInstance())
	{
		ImGui::Text("walk");
	}
	ImGui::Text("animplaytime %f", actor->anim->GetPlayTime());
	//중력 구현
	ApplyGravity();
	actor->Update();
}

void Elder::LateUpdate()
{
	//Elder - Terrain 충돌
	SetonTerrain();

	//보스 소환 임시
	if (INPUT->KeyDown('9')) actor->LoadFile("Monster_Elder.xml");
	else if (INPUT->KeyDown('0')) actor->LoadFile("Monster_Elder_BossStone.xml");

	//슬라이딩 벡터 초기작
	if (PLAYER->GetPlayer()->collider->Intersect(actor->collider))
	{
		PLAYER->istouch = true;
		PLAYER->MoveBack(actor);
	}
	else
	{
		PLAYER->istouch = false;
	}
}

void Elder::Render()
{
	actor->Render();
	
}

void Elder::Release()
{
}

void Elder::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Elder::IsDestroyed()
{
	return false;
}

void Elder::DestructionEvent()
{
}

void Elder::SetState(ElderState* state)
{
	this->state = state;
}

void Elder::BehaviorPatern()
{
	if (INPUT->KeyDown(VK_F3)) state->Opening(this);
	else if (INPUT->KeyDown(VK_F4)) state->Idle(this);
	else if (INPUT->KeyDown(VK_F5)) state->Walk(this);



}
