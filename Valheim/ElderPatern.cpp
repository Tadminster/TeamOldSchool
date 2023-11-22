#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"
#include "ElderPatern.h"

ElderPatern::ElderPatern(Elder* elder)
{
	stomp = new ElderStomp();
	summonSpear = new ElderSummonSpear();
	
}
ElderPatern::~ElderPatern()
{
}
void ElderPatern::Update()
{
	summonSpear->Update();
}
void ElderPatern::Render()
{
	summonSpear->Render();
}
void ElderPatern::StompPatern(Elder* elder)
{
	stomp->ElderStompPatern(elder);
}
void ElderPatern::VineShootPatern(Elder* elder)
{
}
void ElderPatern::SummonPatern(Elder* elder)
{
	summonSpear->SummonSpearPatern(elder);
}

//엘더 내려찍기 클래스-----------------------------------------------------------
ElderStomp::ElderStomp()
{
}

ElderStomp::~ElderStomp()
{
}
//내려찍기 전 플레이타임 0.45
//내려찍는 거리 4.0
void ElderStomp::ElderStompPatern(Elder* elder)
{
	if (elder->GetState() != E_OPENING)
	{
		//한 패턴 후 다음패턴까지 휴식시간 = paternTime
		if (elder->paternTime < 0)
		{
			float distance = (PLAYER->GetPlayer()->GetWorldPos() - elder->GetActor()->GetWorldPos()).Length();

			//엘더 공격 중
			if (elder->GetState() == E_STOMP)
			{
				//발 내려찍기 전까진 이동, 회전값 적용
				if (elder->actor->anim->GetPlayTime() <= 0.45f)
				{
					elder->moveSpeed = 1.0f;
					elder->rotationScale = 1.0f;
					elder->RotationForMove();
				}
				//발 내려찍는 프레임에 타격 콜라이더 크기 확대
				if (elder->actor->anim->currentAnimator.currentFrame >= 23
					&& elder->actor->anim->currentAnimator.currentFrame <= 30)
				{
					if (elder->actor->Find("mixamorig:RightLeg")->collider->scale.x < 500.0f)
					{
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.x *= 2.5f;
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.z *= 2.5f;
					}
				}
				//발 거둘 때 타격 콜라이더 다시 축소
				else
				{
					if (elder->actor->Find("mixamorig:RightLeg")->collider->scale.x > 500.0f)
					{
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.x /= 2.5f;
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.z /= 2.5f;
					}
				}
			}
			//엘더 이동중
			else
			{
				//플레이어 계속 도망치면 엘더 속도 점차 증가
				if (elder->moveSpeed < 2.0f) elder->moveSpeed = 2.0f;
				else if (elder->moveSpeed <= 15.0f)
				{
					elder->moveSpeed += DELTA;
					if (elder->actor->anim->aniScale < 1.0f) elder->actor->anim->aniScale += DELTA * 0.05f;
				}
				elder->rotationScale = 0.4f;
			}
			//엘더 - 플레이어 거리 4 이상이면 쫓아가라
			if (distance > 4.0f && elder->GetState() != E_STOMP)
			{
				elder->Astar();
				elder->GetState()->Walk(elder);
			}
			//엘더 - 플레이어 거리 4 이하면 공격해라
			else if (distance <= 4.0f)
			{
				if (elder->actor->anim->aniScale > 0.4f) elder->actor->anim->aniScale = 0.4f;
				elder->GetState()->Stomp(elder);
			}
			//엘더 공격 끝났으면 Idle로 복귀해라
			if (elder->GetState() == E_STOMP && elder->GetActor()->anim->GetPlayTime() >= 1.0f)
			{
				elder->GetState()->Idle(elder);
				elder->paternTime = 2.5f;
			}
		}
	}
}

//엘더 레이저? 클래스-----------------------------------------------------------
ElderVineShoot::ElderVineShoot()
{
}

ElderVineShoot::~ElderVineShoot()
{
}

void ElderVineShoot::ElderVineShootPatern(Elder* elder)
{

}

//엘더 창 소환 클래스-----------------------------------------------------------
ElderSummonSpear::ElderSummonSpear()
{
	for (int i = 0; i < SPEARNUM; i++)
	{
		spear[i] = Actor::Create();
		spear[i]->LoadFile("SummonSpear.xml");
		spear[i]->name = "spear" + to_string(i);

		//spearRay[i].position = spear[spearIdx]->GetWorldPos() + Vector3(0, 1000, 0);
		spearRay[i].direction = Vector3(0, -1, 0);
	}
}

ElderSummonSpear::~ElderSummonSpear()
{
}

void ElderSummonSpear::Update()
{
	for (int i = 0; i < 10; i++)
	{
		spear[i]->Update();
	}
}

void ElderSummonSpear::Render()
{
	for (int i = 0; i < 10; i++)
	{
		spear[i]->Render();
	}
}
//작업중
void ElderSummonSpear::SummonSpearPatern(Elder* elder)
{
	if (elder->GetState() != E_OPENING)
	{
		if (elder->paternTime < 0)
		{
			elder->state = E_SUMMON;
			elder->RotationForMove();
			targetInfo = PLAYER->GetPlayer()->GetWorldPos() - elder->GetActor()->GetWorldPos();
			distance = targetInfo.Length();
			targetInfo.Normalize();
			dir = targetInfo;
			
			if (spearIdx < SPEARNUM)
			{
				if (TIMER->GetTick(summonTime, 0.15f))
				{
					spear[spearIdx]->SetWorldPos(elder->GetActor()->GetWorldPos() + dir * distance / SPEARNUM * (spearIdx + 1));
					spear[spearIdx]->Update();
					spearRay[spearIdx].position = spear[spearIdx]->GetWorldPos() + Vector3(0, 1000, 0);

					if (Utility::RayIntersectMap(spearRay[spearIdx], MAP, spearY[spearIdx]))
					{
						//spear[spearIdx]->SetWorldPosY(spearY[spearIdx].y - spear[spearIdx]->scale.y * 2.5f);
						spear[spearIdx]->SetWorldPosY(spearY[spearIdx].y);
					}
					spearIdx++;
				}
			}
		}
	}
	if (spearIdx >= SPEARNUM-1)
	{
		summonToIdle += DELTA;
		if (summonToIdle >= 3.5f)
		{
			elder->state = E_IDLE;
			elder->paternTime = 2.5f;
			spearIdx = 0;
			for (int i = 0; i < SPEARNUM; i++)
			{
				spear[i]->SetWorldPos(spearPosition);
			}
			summonToIdle = 0;
		}
	}
}
