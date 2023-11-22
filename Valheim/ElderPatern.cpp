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
			//â�� ������ �÷��̾� ������� ���� ����
			if (spearIdx < spearCount * 0.5f)
			{
				targetInfo = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
				distance = targetInfo.Length();
				targetInfo.Normalize();
				dir = targetInfo;
			}
			//�Ÿ��� ���� ��ȯ�� â ����
			spearCount = distance / 2.0f + 5;
			if (spearBundle.size() < spearCount * BUNDLENUM)
			{
				if (TIMER->GetTick(summonTime, 0.2f))
				{
					for (int j = 0; j < BUNDLENUM; j++)
					{
						Actor* spear = Actor::Create();
						spear->LoadFile("SummonSpear.xml");
						spear->SetWorldPos
						(elder->actor->GetWorldPos() + dir * 2.0f * (spearIdx + 1)+Vector3(RANDOM->Float(-1.0f,1.0f),0, RANDOM->Float(-1.0f, 1.0f)));
						spear->Update();
						//��翡 �ٸ� â ����
						if(dir.y>0)
							spear->rotation.x = RANDOM->Float(50.0f, 70.0f) * ToRadian;
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
				if (summonToIdle > 4.0f)
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
