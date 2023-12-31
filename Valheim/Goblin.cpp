#include "stdafx.h"
#include "GoblinState.h"
#include "ItemProto.h"
#include "Goblin.h"

Goblin::Goblin(Vector3 spawnPos)
{
	actor = Actor::Create();
	actor->LoadFile("/Unit/Monster_Goblin.xml");
	actor->name = "Monster_Goblin";
	//actor->SetWorldPos(spawnPos);
	actor->anim->aniScale = 0.6f;

	state = G_IDLE;

	maxHitpoint = 50.0f;
	hitPoint = 50.0f;

	atk = 5.0f;
	moveSpeed = 3.0f;
	rotationScale = 1.0f;

	this->spawnPos = spawnPos;
}

Goblin::~Goblin()
{
}

void Goblin::Init()
{
	actor->SetWorldPos(spawnPos);

	Vector3 temp = {};
	idlePos.push_back(spawnPos);
	idlePos.push_back(spawnPos +actor->GetForward()* MOVINGSPACE);
	idlePos.push_back(spawnPos -actor->GetForward()* MOVINGSPACE);
	idlePos.push_back(spawnPos +actor->GetRight()* MOVINGSPACE);
	idlePos.push_back(spawnPos -actor->GetRight()* MOVINGSPACE);
	temp = actor->GetForward() + actor->GetRight();
	temp.Normalize();
	idlePos.push_back(spawnPos + temp * MOVINGSPACE);
	idlePos.push_back(spawnPos - temp * MOVINGSPACE);
	temp = actor->GetForward() - actor->GetRight();
	temp.Normalize();
	idlePos.push_back(spawnPos + temp * MOVINGSPACE);
	idlePos.push_back(spawnPos - temp * MOVINGSPACE);
}

void Goblin::Update()
{
	actor->Find("Hp_Red")->scale.x = hitPoint / maxHitpoint;
	if (hitPoint <= 0) Death();
	else
	{
		BehaviorPatern();
		ApplyGravity();
	}
	DoFSM();
	SetOnTerrain();
	UpdateLight();
	actor->Update();
}

void Goblin::LateUpdate()
{
	//플레이어 - 고블린 슬라이딩벡터
	if (PLAYER->GetCollider()->Intersect(actor->collider)) PLAYER->MoveBack(actor);
	//Goblin 공격 -> Player 피격
	if(PLAYER->GetPlayerHit(actor->Find("mixamorig:RightHand")->collider) && state == G_ATTACK)
	{
		if (actor->anim->currentAnimator.currentFrame <= 30) PLAYER->PlayerHit(this->atk);
	}
	//Player 공격 -> Goblin 피격
	if(PLAYER->GetWeoponCollider(actor->collider))
	{
		if (PLAYER->CleanHit(actor->collider) && PLAYER->CleanFrame())
		{
			this->ReceivedDamageEvent(PLAYER->GetWeaponDMG(), PLAYER->GetWeaponType());
			firstHit = true;
		}
	}
}

void Goblin::Render()
{
	actor->Render();
}

void Goblin::Release()
{
	delete this;
}

void Goblin::RenderHierarchy()
{
	
}

void Goblin::UpdateLight()
{
	float lightRatio = max(0.2f, LIGHT->GetTimeRatio());
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);
	actor->Find("goblin")->material->ambient = color;
}

bool Goblin::ReceivedDamageEvent(float damage, WeaponType wType)
{
	PARTICLE->PlayParticleEffect(EffectType::HITBLOOD, actor->GetWorldPos() + Vector3(0, actor->scale.y * 0.5f, 0));
	SOUND->Play(PLAYER_AXE_HIT_01);
	if (wType == WeaponType::Blunt)
	{
		hitPoint -= damage * 2.0f;
	}
	else if(wType == WeaponType::Fist)
	{
		hitPoint -= PLAYER->GetFistDMG();
	}
	else
	{
		hitPoint -= damage;
	}
	return false;
}

bool Goblin::IsDestroyed()
{
	if (deathTime >= 3.0f)
	{
		DestructionEvent();
		return true;
	}
	return false;
}

void Goblin::DestructionEvent()
{
	ItemProto* item = ItemProto::Create(Item::Leather);
	Vector3 randomPos = Vector3(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(1.0f, 3.0f), RANDOM->Float(-1.0f, 1.0f));
	item->GetActor()->SetWorldPos(actor->GetWorldPos() + randomPos);
	OBJ->AddItem(item);
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
		/*RotationForMove(idlePos[idlePosNum]);
		MonsterMove();*/

		if ((Vector2(idlePos[idlePosNum].x, idlePos[idlePosNum].z) - Vector2(actor->GetWorldPos().x, actor->GetWorldPos().z)).Length() < 1.5f)
		{
			state = G_IDLE2;
		}

		if (firstHit) angryTime += DELTA;
		if (angryTime >= 0.3f) isAngry = true;
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
			if (waitingTime > 1.95f)
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
