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

//���� ������� Ŭ����-----------------------------------------------------------
ElderStomp::ElderStomp()
{
}

ElderStomp::~ElderStomp()
{
}
//������� �� �÷���Ÿ�� 0.45
//������� �Ÿ� 4.0
void ElderStomp::ElderStompPatern(Elder* elder)
{
	if (elder->GetState() != E_OPENING)
	{
		//�� ���� �� �������ϱ��� �޽Ľð� = paternTime
		if (elder->paternTime < 0)
		{
			float distance = (PLAYER->GetPlayer()->GetWorldPos() - elder->GetActor()->GetWorldPos()).Length();

			//���� ���� ��
			if (elder->GetState() == E_STOMP)
			{
				//�� ������� ������ �̵�, ȸ���� ����
				if (elder->actor->anim->GetPlayTime() <= 0.45f)
				{
					elder->moveSpeed = 1.0f;
					elder->rotationScale = 1.0f;
					elder->RotationForMove();
				}
				//�� ������� �����ӿ� Ÿ�� �ݶ��̴� ũ�� Ȯ��
				if (elder->actor->anim->currentAnimator.currentFrame >= 23
					&& elder->actor->anim->currentAnimator.currentFrame <= 30)
				{
					if (elder->actor->Find("mixamorig:RightLeg")->collider->scale.x < 500.0f)
					{
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.x *= 2.5f;
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.z *= 2.5f;
					}
				}
				//�� �ŵ� �� Ÿ�� �ݶ��̴� �ٽ� ���
				else
				{
					if (elder->actor->Find("mixamorig:RightLeg")->collider->scale.x > 500.0f)
					{
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.x /= 2.5f;
						elder->actor->Find("mixamorig:RightLeg")->collider->scale.z /= 2.5f;
					}
				}
			}
			//���� �̵���
			else
			{
				//�÷��̾� ��� ����ġ�� ���� �ӵ� ���� ����
				if (elder->moveSpeed < 2.0f) elder->moveSpeed = 2.0f;
				else if (elder->moveSpeed <= 15.0f)
				{
					elder->moveSpeed += DELTA;
					if (elder->actor->anim->aniScale < 1.0f) elder->actor->anim->aniScale += DELTA * 0.05f;
				}
				elder->rotationScale = 0.4f;
			}
			//���� - �÷��̾� �Ÿ� 4 �̻��̸� �Ѿư���
			if (distance > 4.0f && elder->GetState() != E_STOMP)
			{
				elder->Astar();
				elder->GetState()->Walk(elder);
			}
			//���� - �÷��̾� �Ÿ� 4 ���ϸ� �����ض�
			else if (distance <= 4.0f)
			{
				if (elder->actor->anim->aniScale > 0.4f) elder->actor->anim->aniScale = 0.4f;
				elder->GetState()->Stomp(elder);
			}
			//���� ���� �������� Idle�� �����ض�
			if (elder->GetState() == E_STOMP && elder->GetActor()->anim->GetPlayTime() >= 1.0f)
			{
				elder->GetState()->Idle(elder);
				elder->paternTime = 2.5f;
			}
		}
	}
}

//���� ������? Ŭ����-----------------------------------------------------------
ElderVineShoot::ElderVineShoot()
{
}

ElderVineShoot::~ElderVineShoot()
{
}

void ElderVineShoot::ElderVineShootPatern(Elder* elder)
{

}

//���� â ��ȯ Ŭ����-----------------------------------------------------------
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
//�۾���
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
