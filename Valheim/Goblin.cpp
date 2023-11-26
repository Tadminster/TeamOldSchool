#include "stdafx.h"
#include "GoblinState.h"
#include "Goblin.h"

Goblin::Goblin(Vector3 spawnPos)
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Goblin.xml");
	actor->name = "Monster_Goblin";
	actor->SetWorldPos(spawnPos);

	state = G_IDLE;

	hitPoint = 5.0f;
	moveSpeed = 5.0f;
	rotationScale = 1.0f;
}

Goblin::~Goblin()
{
}

void Goblin::Init()
{
	Vector3 temp = {};
	idlePos.push_back(actor->GetWorldPos());
	idlePos.push_back(actor->GetWorldPos()+actor->GetForward()*10.0f);
	idlePos.push_back(actor->GetWorldPos()-actor->GetForward()*10.0f);
	idlePos.push_back(actor->GetWorldPos()+actor->GetRight()*10.0f);
	idlePos.push_back(actor->GetWorldPos()-actor->GetRight()*10.0f);
	temp = actor->GetForward() + actor->GetRight();
	temp.Normalize();
	idlePos.push_back(actor->GetWorldPos() + temp * 10.0f);
	idlePos.push_back(actor->GetWorldPos() - temp * 10.0f);
	temp = actor->GetForward() - actor->GetRight();
	temp.Normalize();
	idlePos.push_back(actor->GetWorldPos() + temp * 10.0f);
	idlePos.push_back(actor->GetWorldPos() - temp * 10.0f);
}

void Goblin::Update()
{
	if (ImGui::Button("astar"))
	{
		if (astar != nullptr) delete astar;
		astar = new AStar();
		astar->CreateNode(MAP, MAP->rowSize * 2.5f, OBJ->GetColliders());
	}

	BehaviorPatern();
	DoFSM();
	SetOnTerrain();
	ApplyGravity();

	

	actor->Update();
}

void Goblin::LateUpdate()
{
	//Goblin 공격 -> Player 피격
	if (PLAYER->GetCollider()->Intersect(actor->Find("mixamorig:RightHand")->collider)
		&& state == G_ATTACK)
	{
		PLAYER->PlayerHit();
	}

	//Player 공격 -> Goblin 피격
	if (PLAYER->CleanHit(actor->collider) && PLAYER->CleanFrame())
	{
		if (actor->collider->Intersect(PLAYER->GetPlayerWeapon()->GetActor()->collider))
		{
			this->ReceivedDamageEvent(PLAYER->GetWeaponDMG(), PLAYER->GetWeaponType());
			isAngry = true;
		}
	}
}

void Goblin::Render()
{
	actor->Render();
}

void Goblin::Release()
{
}

void Goblin::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Goblin::ReceivedDamageEvent(float damage, WeaponType wType)
{
	if (wType == WeaponType::Blunt)
	{
		hitPoint -= damage * 2.0f;
		cout << "Blunt" << endl;
		cout << damage << endl;
	}
	else
	{
		hitPoint -= damage;
		cout << damage << endl;
	}

	return false;

	return false;
}

bool Goblin::IsDestroyed()
{
	return false;
}

void Goblin::DestructionEvent()
{
}

void Goblin::SetState(GoblinState* state)
{
	this->state = state;
}

void Goblin::BehaviorPatern()
{
	if (!isAngry)
	{
		//Idle
		if (state == G_IDLE)
		{
			idlePosNum = RANDOM->Int(0, 8);
		}
		state = G_RUN;
		Astar(idlePos[idlePosNum]);

		if ((Vector2(idlePos[idlePosNum].x, idlePos[idlePosNum].z) - Vector2(actor->GetWorldPos().x, actor->GetWorldPos().z)).Length() < 2.0f)
		{
			state = G_IDLE2;
		}
	}
	else
	{
		//Chase & Attack
		if ((PLAYER->GetPlayer()->GetWorldPos() - actor->GetWorldPos()).Length() < 1.5f)
		{
			RotationForMove();
			state = G_ATTACK;
			waitingTime = 0;
		}
		else
		{
			if (waitingTime > 0.8f)
			{
				//Astar();
				RotationForMove();
				MonsterMove();
				state = G_RUN;
			}
			else
			{
				waitingTime += DELTA;
			}
		}
	}
}

void Goblin::DoFSM()
{
	if (state == G_IDLE)
	{
		state->Idle(this);
	}
	else if (state == G_IDLE2)
	{
		state->Idle2(this);
	}
	else if (state == G_RUN)
	{
		state->Run(this);
	}
	else if (state == G_ATTACK)
	{
		state->Attack(this);
	}
	else if (state == G_DEATH)
	{
		state->Death(this);
	}
	
}
