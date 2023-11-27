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

	actor->anim->aniScale = 0.6f;
	hitPoint = 50.0f;
	moveSpeed = 3.0f;
	rotationScale = 1.0f;
}

Goblin::~Goblin()
{

}

void Goblin::Init()
{
	Vector3 temp = {};
	idlePos.push_back(actor->GetWorldPos());
	idlePos.push_back(actor->GetWorldPos()+actor->GetForward()* MOVINGSPACE);
	idlePos.push_back(actor->GetWorldPos()-actor->GetForward()* MOVINGSPACE);
	idlePos.push_back(actor->GetWorldPos()+actor->GetRight()* MOVINGSPACE);
	idlePos.push_back(actor->GetWorldPos()-actor->GetRight()* MOVINGSPACE);
	temp = actor->GetForward() + actor->GetRight();
	temp.Normalize();
	idlePos.push_back(actor->GetWorldPos() + temp * MOVINGSPACE);
	idlePos.push_back(actor->GetWorldPos() - temp * MOVINGSPACE);
	temp = actor->GetForward() - actor->GetRight();
	temp.Normalize();
	idlePos.push_back(actor->GetWorldPos() + temp * MOVINGSPACE);
	idlePos.push_back(actor->GetWorldPos() - temp * MOVINGSPACE);
}

void Goblin::Update()
{
	if (ImGui::Button("astar"))
	{
		if (astar != nullptr) delete astar;
		astar = new AStar();
		astar->CreateNode(MAP, MAP->rowSize * 2.5f, OBJ->GetColliders());
	}

	actor->Find("Hp_Red")->scale.x = hitPoint / 50.0f;
	if (hitPoint <= 0) Death();
	else
	{
		BehaviorPatern();
		ApplyGravity();
	}

	DoFSM();
	SetOnTerrain();

	

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
		cout << hitPoint << endl;
	}
	else
	{
		hitPoint -= damage;
		cout << hitPoint << endl;
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

		if ((Vector2(idlePos[idlePosNum].x, idlePos[idlePosNum].z) - Vector2(actor->GetWorldPos().x, actor->GetWorldPos().z)).Length() < 1.5f)
		{
			state = G_IDLE2;
		}
	}
	else
	{
		//Chase & Attack
		if ((PLAYER->GetPlayer()->GetWorldPos() - actor->GetWorldPos()).Length() < 1.5f)
		{
			state = G_ATTACK;
			RotationForMove();
			waitingTime = 0;
			/*if (state == G_ATTACK)
			{
				attackTime += DELTA;
				if (attackTime >= 2.2f)
				{
					state = G_ATTACK;
					attackTime = 0;
				}
			}
			else
			{
				state = G_ATTACK;
				attackTime = 0;
			}*/
		}
		else
		{
			if (waitingTime > 2.1f)
			{
				//Astar();
				RotationForMove();
				MonsterMove();
				state = G_RUN;
			}
			else
			{
				if (state != G_ATTACK) state = G_IDLE2;
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

void Goblin::Death()
{
	state = G_DEATH;
	Ray deathRay;
	deathRay.position = actor->GetWorldPos() + (-actor->GetForward()) * 5.0f + Vector3(0, 1000, 0);
	deathRay.direction = Vector3(0, -1, 0);
	Vector3 temp;
	if (Utility::RayIntersectMap(deathRay, MAP, temp))
	{
		Vector3 dir = temp - actor->GetWorldPos();
		dir.Normalize();
		actor->rotation.x = asinf(dir.y);
	}
	actor->DeleteObject("Hp_Black");
}
