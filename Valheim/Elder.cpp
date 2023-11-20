#include "stdafx.h"
#include "ElderState.h"
#include "ElderPatern.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	//actor->LoadFile("Monster_Elder_BossStone.xml");
	actor->LoadFile("Monster_Elder.xml");
	actor->name = "Monster_Elder";
	actor->anim->aniScale = 0.4f;

	state = Elder_OpeningState::GetInstance();

	moveSpeed = 2.0f;

	/*astar = new AStar();
	astar->CreateNode(MAP, 200);*/
}

Elder::~Elder()
{
}

void Elder::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(10,0,0));
}

void Elder::Update()
{
	//테스트용-------------------------------------
	if (INPUT->KeyDown('9')) actor->LoadFile("Monster_Elder.xml");
	else if (INPUT->KeyDown('0')) actor->LoadFile("Monster_Elder_BossStone.xml");

	if (INPUT->KeyDown(VK_F3)) state->Opening(this);
	else if (INPUT->KeyDown(VK_F4)) state->Idle(this);
	else if (INPUT->KeyDown(VK_F5)) state->Walk(this);
	else if (INPUT->KeyDown(VK_F6)) state->Stomp(this);
	else if (INPUT->KeyDown(VK_F7)) state->VineShoot(this);
	else if (INPUT->KeyDown(VK_F8)) state->Summon(this);

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
	else if (state == Elder_VineShootState::GetInstance())
	{
		ImGui::Text("vineshoot");
	}
	else if (state == Elder_SummonState::GetInstance())
	{
		ImGui::Text("summon");
	}

	if (ImGui::Button("astar"))
	{
		if (astar != nullptr) delete astar;
		astar = new AStar();
		astar->CreateNode(MAP, MAP->rowSize*1.5f, OBJ->GetColliders());
	}

	//행동패턴(astar 노드 생성 -> 트리 생성(역순은 astar노드생성 시간이 느려짐))
	//기능은 두 경우 모두 정상작동함 확인
	BehaviorPatern();
	DoFSM();

	//중력 구현
	ApplyGravity();
	actor->Update();
}

void Elder::LateUpdate()
{
	//Elder - Terrain 충돌
	SetOnTerrain();

	//Elder_BossStone - Player 충돌
	if (PLAYER->GetCollider()->Intersect(actor->collider))
	{
		PLAYER->istouch = true;
		PLAYER->MoveBack(actor);
	}
	else
	{
		PLAYER->istouch = false;
	}

	//Elder - Player 충돌
	if (PLAYER->GetCollider()->Intersect(actor->Find("mixamorig:RightLeg")->collider)
		&& state == E_STOMP)
	{
		PLAYER->PlayerHit();
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
	if (paternTime >= 0) paternTime -= DELTA;
	patern->StompPatern(this);
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
	else if (state == E_VINESHOOT)
	{
		state->VineShoot(this);
	}
	else if (state == E_SUMMON)
	{
		state->Summon(this);
	}
}



