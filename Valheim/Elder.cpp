#include "stdafx.h"
#include "ElderState.h"
#include "ElderPatern.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("/Unit/Monster_Elder.xml");
	actor->name = "Monster_Elder";
	actor->anim->aniScale = 0.4f;

	patern = new ElderPatern(this);

	hitPoint = 5;
}

Elder::~Elder()
{
}

void Elder::Init()
{
	moveSpeed = 2.0f;
	state = Elder_OpeningState::GetInstance();
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(10,0,0));
}

void Elder::Update()
{
	//테스트용------------------------------------
	//if (INPUT->KeyDown('-')) actor->LoadFile("Monster_Elder.xml");
	//else if (INPUT->KeyDown('=')) actor->LoadFile("Monster_Elder_BossStone.xml");

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
	else if (state == Elder_StompState::GetInstance())
	{
		ImGui::Text("stomp");
	}
	else if (state == Elder_JumpAttackState::GetInstance())
	{
		ImGui::Text("JumpAttack");
	}
	else if (state == Elder_SummonState::GetInstance())
	{
		ImGui::Text("summon");
	}

	if (hitPoint <= 0)
	{
		state = E_DEATH;
		Ray deathRay;
		deathRay.position = actor->GetWorldPos() + (-actor->GetForward()) * 10.0f + Vector3(0, 1000, 0);
		deathRay.direction = Vector3(0, -1, 0);
		Vector3 temp;
		if (Utility::RayIntersectMap(deathRay, MAP, temp))
		{
			Vector3 dir = temp - actor->GetWorldPos();
			dir.Normalize();
			actor->rotation.x = asinf(dir.y);
		}
		
		
	}
	else
	{
		BehaviorPatern();
		ApplyGravity();
	}

	
	
	
	DoFSM();
	actor->Update();
	patern->Update();
	
	
	

}

void Elder::LateUpdate()
{
	//Elder - Terrain 충돌
	SetOnTerrain();
	
	//Elder_BossStone - Player 충돌
	if (PLAYER->GetCollider()->Intersect(actor->collider)) PLAYER->MoveBack(actor);
	
	

	//Elder 공격 -> Player 피격
	if (PLAYER->GetCollider()->Intersect(actor->Find("mixamorig:RightLeg")->collider)
		&& state == E_STOMP)
	{
		PLAYER->PlayerHit();
	}

	//Player 공격 -> Elder 피격
	if (PLAYER->CleanHit(actor->collider) && PLAYER->CleanFrame())
	{
		if (actor->collider->Intersect(PLAYER->GetPlayerWeapon()->GetActor()->collider))
		{
			this->hitPoint -= PLAYER->GetWeaponDMG();
		}
	}
	
}

void Elder::Render()
{
	actor->Render();
	patern->Render();
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
	if (hitPoint <= 0) return true;
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
	//공격 한번 당 2.5초 쉼
	if (paternTime >= 0 && state == E_IDLE)
	{
		paternTime -= DELTA;
		paternType = RANDOM->Int(0, 99);
	}
	//패턴 한번 - 발찍기 한번 반복
	if (stompPatern )
	{
		patern->StompPatern(this);
	}
	else
	{
		switch (paternType % 2)
		{
		case 0:
			patern->JumpAttackPatern(this);
			break;
		case 1:
			patern->SummonPatern(this);
			break;
		}
	}
	

}

void Elder::DoFSM()
{
	if (state == E_OPENING)
	{
		state->Opening(this);
	}
	else if (state == E_IDLE)
	{
		state->Idle(this);
	}
	else if (state == E_WALK)
	{
		state->Walk(this);
	}
	else if (state == E_STOMP)
	{
		state->Stomp(this);
	}
	else if (state == E_JumpAttack)
	{
		state->JumpAttack(this);
	}
	else if (state == E_SUMMON)
	{
		state->Summon(this);
	}
	else if (state == E_DEATH)
	{
		state->Death(this);
	}
}



