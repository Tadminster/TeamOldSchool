#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"
#include "ElderPatern.h"

ElderPatern::ElderPatern()
{
}
ElderPatern::ElderPatern(Elder* elder)
{
	stomp = new ElderStomp();
	jumpAttack = new ElderJumpAttack(elder);
	summonSpear = new ElderSummonSpear();
	
}
ElderPatern::~ElderPatern()
{
}
void ElderPatern::Update()
{
	summonSpear->Update();
	jumpAttack->Update();
}
void ElderPatern::Render()
{
	summonSpear->Render();
	jumpAttack->Render();
}
void ElderPatern::StompPatern(Elder* elder)
{
	stomp->ElderStompPatern(elder);
}
void ElderPatern::JumpAttackPatern(Elder* elder)
{
	jumpAttack->ElderJumpAttackPatern(elder);
}
void ElderPatern::SummonPatern(Elder* elder)
{
	summonSpear->SummonSpearPatern(elder);
}

//엘더 발찍기 클래스-----------------------------------------------------------
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

//엘더 점프어택 클래스-----------------------------------------------------------
ElderJumpAttack::ElderJumpAttack(Elder* elder)
{
	interval = RANDOM->Float(elder->GetActor()->scale.x, 3.0f);
	spearRay.direction = Vector3(0, -1, 0);
}
ElderJumpAttack::~ElderJumpAttack()
{

}
void ElderJumpAttack::Update()
{
	for (auto& it : spearBundle)
	{
		it->Update();
	}
}
void ElderJumpAttack::Render()
{
	for (auto& it : spearBundle)
	{
		it->Render();
	}
}
void ElderJumpAttack::ElderJumpAttackPatern(Elder* elder)
{

	if (elder->GetState() != E_OPENING)
	{
		if (elder->paternTime < 0)
		{
			targetInfo = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
			distance = targetInfo.Length();
			targetInfo.Normalize();
			dir = targetInfo;

			elder->RotationForMove();
			if (elder->rotationTime <= 0 )
			{
				if(elder->state != E_JumpAttack)
					elder->state = E_JumpAttack;
				//(할일)이동해야 할 프레임 조절
				if (elder->actor->anim->currentAnimator.animState != AnimationState::STOP)
					elder->GetActor()->MoveWorldPos(dir * distance / 3.0f * DELTA);
			}
			if (spearIdx <= 56)
			{
				if (elder->actor->anim->currentAnimator.animState == AnimationState::STOP)
				{
						Vector3 direction = {};
						switch (spearIdx % 8)
						{
						case 0:
							direction = elder->GetActor()->GetForward();
							break;
						case 1:
							direction = -elder->GetActor()->GetForward();
							break;
						case 2:
							direction = elder->GetActor()->GetRight();
							break;
						case 3:
							direction = -elder->GetActor()->GetRight();
							break;
						case 4:
							direction = elder->GetActor()->GetForward() + elder->GetActor()->GetRight();
							direction.Normalize();
							break;
						case 5:
							direction = elder->GetActor()->GetForward() - elder->GetActor()->GetRight();
							direction.Normalize();
							break;
						case 6:
							direction = -elder->GetActor()->GetForward() + elder->GetActor()->GetRight();
							direction.Normalize();
							break;
						case 7:
							direction = -elder->GetActor()->GetForward() - elder->GetActor()->GetRight();
							direction.Normalize();
							break;
						}

						Vector3 temp = { RANDOM->Float(-2.0f, 2.0f), 0, RANDOM->Float(-2.0f, 2.0f) };
						Actor* spear = Actor::Create();
						spear->LoadFile("SummonSpear.xml");
						spear->SetWorldPos(elder->GetActor()->GetWorldPos() + direction * interval + temp);
						spear->Update();
						spear->rotation = direction;
						spearRay.position = spear->GetWorldPos() + Vector3(0, 1000, 0);
						if (Utility::RayIntersectMap(spearRay, MAP, spearY))
						{
							spear->SetWorldPosY(spearY.y);
						}
						
						spearBundle.emplace_back(spear);
					
					spearIdx++;
				}
			}
			else
			{
				respawnTime += DELTA;
				
				if (respawnTime >= 2.5f)
				{
					if (respawnPhase == 0)
					{
						respawnTime = 0;
						spearIdx = 0;
						interval = RANDOM->Float(3.0f, 6.0f);
						respawnPhase++;
						elder->jumpAttackMotion++;
					}
					else
					{
						respawnTime = 0;
						spearIdx = 0;
						respawnPhase = 0;
						interval = RANDOM->Float(elder->GetActor()->scale.x, 3.0f);
						elder->jumpAttackMotion = 0;
						spearBundle.clear();
						elder->state = E_IDLE;
					}
				}
			}
		}
	}
}

//엘더 창 소환 클래스-----------------------------------------------------------
ElderSummonSpear::ElderSummonSpear()
{
	spearRay.direction = Vector3(0, -1, 0);
}
ElderSummonSpear::~ElderSummonSpear()
{
}
void ElderSummonSpear::Update()
{
	for (auto& it : spearBundle)
	{
		it->Update();
	}
}
void ElderSummonSpear::Render()
{
	for (auto& it : spearBundle)
	{
		it->Render();
	}
}
void ElderSummonSpear::SummonSpearPatern(Elder* elder)
{
	if (elder->GetState() != E_OPENING)
	{
		if (elder->paternTime < 0)
		{
			elder->state = E_SUMMON;
			elder->RotationForMove();
			//플레이어 추적을 제한하기 위한 조건
			float chaseTime = 0;
			if (distance >= 0 && distance < 15) chaseTime = 0.3f;
			else if (distance >= 15 && distance < 30) chaseTime = 0.4f;
			else chaseTime = 0.6f;

			//창이 끝까지 플레이어 따라오는 현상 방지
			if (spearIdx < spearCount * chaseTime)
			{
				targetInfo = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
				distance = targetInfo.Length();
				targetInfo.Normalize();
				dir = targetInfo;
			}
			//거리에 따라 창 소환 속도 조절
			float spearSpeed = 0;
			if (distance >= 0 && distance < 15) spearSpeed = 0.4f;
			else if (distance >= 15 && distance < 30) spearSpeed = 0.2f;
			else spearSpeed = 0.15f;
			//거리에 따른 소환할 창 갯수
			spearCount = distance / 2.0f + 5;
			if (spearBundle.size() < spearCount * BUNDLENUM)
			{
				if (TIMER->GetTick(summonTime, spearSpeed))
				{
					for (int j = 0; j < BUNDLENUM; j++)
					{
						Actor* spear = Actor::Create();
						spear->LoadFile("SummonSpear.xml");
						spear->SetWorldPos
						(elder->actor->GetWorldPos() + dir * 2.0f * (spearIdx + 1)+Vector3(RANDOM->Float(-2.0f,2.0f),0, RANDOM->Float(-2.0f, 2.0f)));
						spear->Update();
						//경사에 따른 창 기울기
						if (dir.x > 0.5f)
							spear->rotation.x = RANDOM->Float(25.0f, 45.0f) * ToRadian;
						else
							spear->rotation.x = RANDOM->Float(60.0f, 80.0f) * ToRadian;
						spear->rotation.y = elder->actor->rotation.y;
						spear->rotation.z = RANDOM->Float(-10.0f, 10.0f) * ToRadian;
						spearRay.position = spear->GetWorldPos() + Vector3(0, 1000, 0);
						if (Utility::RayIntersectMap(spearRay, MAP, spearY))
						{
							spear->SetWorldPosY(spearY.y);
						}
						spearBundle.emplace_back(spear);
					}
					spearIdx++;
				}
			}
			else
			{
				summonToIdle += DELTA;
				if (summonToIdle > 3.0f)
				{
					elder->state = E_IDLE;
					spearIdx = 0;
					summonToIdle = 0;
					spearBundle.clear();
				}
			}
		}
	}

}