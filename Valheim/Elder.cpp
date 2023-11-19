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

	astar = new AStar();
	astar->CreateNode(MAP, 200);
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
	ImGui::Text("animplaytime %f", actor->anim->GetPlayTime());
	ImGui::Text("paternTime %f", paternTime);

	//행동패턴
	BehaviorPatern();
	DoFSM();
	Astar();

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
	/*if (paternTime >= 0) paternTime -= DELTA;
	patern->StompPatern(this);*/

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

void Elder::Astar()
{
	//AstarRay.position = PLAYER->GetPlayer()->GetWorldPos() + Vector3(0, 100, 0);
	//AstarRay.direction = Vector3(0, -1, 0);
	//Vector3 target;
	//if (Utility::RayIntersectMap(AstarRay, MAP, target))
	//	//if(MAP->ComputePicking(AstarRay,target))
	//{
	//	astar->PathFinding(actor->GetWorldPos(), target, way);
	//}
	//if (!way.empty())
	//{
	//	RotationForMove(way.back());
	//	for (auto& it : way)
	//	{
	//		ImGui::Text("way x %f", it.x);
	//		ImGui::Text("way y %f", it.y);
	//		ImGui::Text("way z %f", it.z);
	//	}
	//	way.pop_back();
	//}
	
	
	/*AstarRay.position = PLAYER->GetPlayer()->GetWorldPos() + Vector3(0, 100, 0);
	AstarRay.direction = Vector3(0, -1, 0);
	Vector3 target;*/
	//if (Utility::RayIntersectMap(AstarRay, MAP, target))
		//if(MAP->ComputePicking(AstarRay,target))
	//{
	//}
	
		astar->PathFinding(actor->GetWorldPos(), PLAYER->GetPlayer()->GetWorldPos(), way);
		if (!way.empty())
		{
			RotationForMove(way.back());
			MonsterMove();
			for (auto& it : way)
			{
				ImGui::Text("way x %f", it.x);
				ImGui::Text("way y %f", it.y);
				ImGui::Text("way z %f", it.z);
			}
			if ((way.back() - actor->GetWorldPos()).Length() <= 1.5f)
			{
				way.pop_back();
				cout << "pop";
			}
		}
		if ((PLAYER->GetPlayer()->GetWorldPos() - actor->GetWorldPos()).Length() <= 1.5f) way.clear();
	
}


