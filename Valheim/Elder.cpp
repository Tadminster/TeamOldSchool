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

	ment1 = UI::Create();
	ment1->LoadFile("/Unit/Elder_Ment.xml");
	ment1->name = "Ment1";

	ment2 = UI::Create();
	ment2->LoadFile("/Unit/Elder_Ment2.xml");
	ment2->name = "Ment2";

	ment3 = UI::Create();
	ment3->LoadFile("/Unit/Elder_Ment3.xml");
	ment3->name = "Ment3";

	ment4 = UI::Create();
	ment4->LoadFile("/Unit/Elder_Ment4.xml");
	ment4->name = "Ment4";

	hp = UI::Create();
	hp->LoadFile("Unit/Elder_HP.xml");
	hp->name = "elder_hp";
	
	hitPoint = 200;
	maxHitpoint = 200;
}

Elder::~Elder()
{
}

void Elder::Init()
{
	moveSpeed = 2.0f;
	state = Elder_OpeningState::GetInstance();
	actor->SetWorldPos(Vector3(0,0,0));
	ment1->visible = false;
	ment2->visible = false;
	ment3->visible = false;
	ment4->visible = false;
	hp->visible = false;
}

void Elder::Update()
{
	if (hitPoint <= 0)
	{
		deathTime += DELTA;
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
		//hp->visible = false;
	}
	else
	{
		if (isElder)
		{
			BehaviorPatern();
			ApplyGravity();
			if (hp->Find("front_hp")->scale.x < 0.1f) hp->Find("front_hp")->scale.x = 0;
			else hp->Find("front_hp")->scale.x = hitPoint / maxHitpoint;

			if ((PLAYER->GetActor()->GetWorldPos() - actor->GetWorldPos()).Length() <= 30.0f)
			{
				if (hp->visible == false) hp->visible = true;
			}

		}
		if (PLAYER->GetTreeCount() >= 3)
		{
			if (ment4) mentTime += DELTA;
			//숲의 수호신 엘더가 깨어납니다!
			if (mentTime >= 10.0f)
			{
				delete ment4;
				ment4 = nullptr;
				actor->LoadFile("/Unit/Monster_Elder.xml");
				isElder = true;
				SOUND->Stop(BGM_HOMEBASE);
				SOUND->Play(ELDER_BGM_01);
				LIGHT->isBoss = true;
				mentTime = 0;
			}
			//더이상 분노를 참을 수 없습니다!
			else if (mentTime >= 5.0f)
			{
				delete ment3;
				ment3 = nullptr;
				ment4->visible = true;
				Camera::main->SetLocalPos
				(Vector3(RANDOM->Float(-0.1f, 0.1f), RANDOM->Float(-0.1f, 0.1f) , RANDOM->Float(-0.1f, 0.1f)));
			}
			else if (mentTime >= 1.0f)
			{
				ment3->visible = true;
			}
		}
		//숲이 분노합니다.
		else if (PLAYER->GetTreeCount() >= 2)
		{
			if (ment2) mentTime += DELTA;
			if (mentTime >= 7.0f)
			{
				delete ment2;
				ment2= nullptr;
				mentTime = 0;
			}
			else if (mentTime >= 1.0f)
			{
				ment2->visible = true;
			}
		}	
		//숲이 언짢아 하고 있습니다.
		else if (PLAYER->GetTreeCount() >= 1)
		{
			if(ment1) mentTime += DELTA;
			if (mentTime >= 7.0f)
			{
				delete ment1;
				ment1 = nullptr;
				mentTime = 0;
			}
			else if (mentTime >= 1.0f)
			{
				ment1->visible = true;
			}
		}
	}

	//Elder - Terrain 충돌
	DoFSM();
	UpdateLight();
	SetOnTerrain();

	actor->Update();
	patern->Update();
	hp->Update();
	if (ment1) ment1->Update();
	if (ment2) ment2->Update();
	if (ment3) ment3->Update();
	if (ment4) ment4->Update();
}

void Elder::LateUpdate()
{
	if (isElder && hitPoint > 0)
	{
		//Elder_BossStone - Player 충돌
		if (PLAYER->GetCollider()->Intersect(actor->collider)) PLAYER->MoveBack(actor);

		//Elder 공격 -> Player 피격
		if (PLAYER->GetPlayerHit(actor->Find("mixamorig:RightLeg")->collider) && state == E_STOMP)
		{
			PLAYER->PlayerHit(10.0f);
		}
		else if (PLAYER->GetPlayerHit(actor->collider) && state == E_JumpAttack)
		{
			PLAYER->PlayerHit(15.0f);
		}

		//Player 공격 -> Elder 피격
		if (PLAYER->GetWeoponCollider(actor->Find("RootNode")->collider))
		{
			if (PLAYER->CleanHit(actor->Find("RootNode")->collider) && PLAYER->CleanFrame())
			{
				this->ReceivedDamageEvent(PLAYER->GetWeaponDMG(), PLAYER->GetWeaponType());
			}
		}
	}
}

void Elder::Render()
{
	actor->Render();
	patern->Render();
	hp->Render();
	if (ment1) ment1->Render();
	if (ment2) ment2->Render();
	if (ment3) ment3->Render();
	if (ment4) ment4->Render();
}

void Elder::Release()
{
	delete this;
}

void Elder::RenderHierarchy()
{
	actor->RenderHierarchy();
	hp->RenderHierarchy();
	
	if (ment1) ment1->RenderHierarchy();
	if (ment2) ment2->RenderHierarchy();
	if (ment3) ment3->RenderHierarchy();
	if (ment4) ment4->RenderHierarchy();
}

void Elder::UpdateLight()
{
	float lightRatio = max(0.2f, LIGHT->GetTimeRatio());
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);
	if (isElder)
	{
		actor->Find("gd_king_001")->material->ambient = color;
		actor->Find("gd_king_001")->material->diffuse = color;
	}
	else
	{
		actor->Find("Model")->material->ambient = color;
		actor->Find("Model")->material->diffuse = color;
	}
}

bool Elder::IsDestroyed()
{
	if (!isDeath)
	{
		if (deathTime >= 5.0f)
		{
			DestructionEvent();
			isDeath = true;
			actor->visible = false;
			return true;
		}
		return false;
	}
	
}

bool Elder::ReceivedDamageEvent(float damage, WeaponType wType)
{
	PARTICLE->PlayParticleEffect(EffectType::HITWOOD, PLAYER->GetCollisionPoint());
	SOUND->Play(PLAYER_AXE_HIT_01);
	if (wType == WeaponType::Blunt)
	{
		hitPoint -= damage * 2.0f;
	}
	else if (wType == WeaponType::Fist)
	{
		hitPoint -= PLAYER->GetFistDMG();
	}
	else
	{
		hitPoint -= damage;
	}
	
	return false;
}

void Elder::DestructionEvent()
{
	ItemProto* item = ItemProto::Create(Item::ElderTrophy);
	item->GetActor()->SetWorldPos(actor->GetWorldPos() - actor->GetForward() * actor->scale.y * 0.5f);
	OBJ->AddItem(item);
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
	if (stompPatern)
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



