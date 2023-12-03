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

//���� ����� Ŭ����-----------------------------------------------------------
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
			distance = (PLAYER->GetPlayer()->GetWorldPos() - elder->GetActor()->GetWorldPos()).Length();

			//���� ���� ��
			if (elder->GetState() == E_STOMP)
			{
				if (elder->actor->anim->currentAnimator.currentFrame == 23)
					SOUND->Play(ELDER_STOMP);

				//�� ������� ������ �̵�, ȸ���� ����
				if (elder->actor->anim->GetPlayTime() <= 0.3f)
				{
					Vector3 moveDir = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
					moveDir.Normalize();
					elder->actor->rotation.y = atan2f(moveDir.x, moveDir.z);
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
				elder->rotationScale = 0.6f;
			}
			
			//���� - �÷��̾� �Ÿ� 4 ���ϸ� �����ض�
			if (distance <= 4.0f)
			{
				if (elder->actor->anim->aniScale > 0.5f) elder->actor->anim->aniScale = 0.5f;
				elder->GetState()->Stomp(elder);
			}
			//���� - �÷��̾� �Ÿ� 4 �̻��̸� �Ѿư���
			else if (distance > 4.0f && elder->GetState() != E_STOMP)
			{
				elder->Astar();
				elder->GetState()->Walk(elder);
			}
		
			//���� ���� �������� Idle�� �����ض�
			if (elder->GetState() == E_STOMP && elder->GetActor()->anim->GetPlayTime() >= 0.95f)
			{
				elder->GetState()->Idle(elder);
				elder->stompPatern = false;
				elder->paternTime = 2.5f;
			}
		}
	}
}

//���� �������� Ŭ����-----------------------------------------------------------
ElderJumpAttack::ElderJumpAttack(Elder* elder)
{
	interval = RANDOM->Float(2.0f, 4.0f);
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
			//���� �پ ������� ������ ���� ������������
			//if (elder->actor->anim->currentAnimator.animIdx == 4)
			{
				if (elder->actor->anim->currentAnimator.currentFrame <= 50 &&
					elder->jumpAttackMotion == 0)
				{
					elder->RotationForMove();
					/*Vector3 moveDir = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
					moveDir.Normalize();
					elder->actor->rotation.y = atan2f(moveDir.x, moveDir.z);*/
				}
			}

			for (auto& it : spearBundle)
			{
				if (PLAYER->GetPlayerHit(it->collider))
				{
					if (TIMER->GetTick(spearHitTime, 0.2f))
					{
						PARTICLE->PlayParticleEffect(EffectType::HITBLOOD, PLAYER->playerhitPos);
						PLAYER->hitPoint -= 0.05f;
					}
				}
			}

			//������ �÷��̾ �ٶ󺸸� ���� �پ��
			if (elder->rotationTime <= 0.1f )
			{
				if(elder->state != E_JumpAttack) elder->state = E_JumpAttack;
				//�̵����� ������ 19, ���� ������ 50
				if (elder->actor->anim->currentAnimator.currentFrame >= 14 &&
					elder->actor->anim->currentAnimator.currentFrame <= 50 &&
					elder->jumpAttackMotion == 0)
				{
					targetInfo = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
					distance = targetInfo.Length();
					targetInfo.Normalize();
					dir = targetInfo;
					elder->moveSpeed = distance * 1.5f;
					elder->MonsterMove();
				}
				else elder->moveSpeed = 2.0f;
			}
			//8���� * 7(����� ��ȯ�� â ����)
			if (elder->state == E_JumpAttack) {
				if (elder->actor->anim->currentAnimator.currentFrame == 50)
					SOUND->Play(ELDER_JUMPATTACK);

				if (spearIdx < 56)
				{
					Vector3 direction = {};
					float spearDirection = 0;
					if (elder->actor->anim->GetPlayTime() > 0.8f)
					{
						switch (spearIdx % 8)
						{
						case 0:
							direction = elder->GetActor()->GetForward();
							spearDirection = elder->GetActor()->rotation.y;
							break;
						case 1:
							direction = -elder->GetActor()->GetForward();
							spearDirection = -elder->GetActor()->rotation.y;
							break;
						case 2:
							direction = elder->GetActor()->GetRight();
							spearDirection = elder->GetActor()->rotation.y + 90.0f * ToRadian;
							break;
						case 3:
							direction = -elder->GetActor()->GetRight();
							spearDirection = -elder->GetActor()->rotation.y - 90.0f * ToRadian;
							break;
						case 4:
							direction = elder->GetActor()->GetForward() + elder->GetActor()->GetRight();
							direction.Normalize();
							spearDirection = elder->GetActor()->rotation.y + 45.0f * ToRadian;
							break;
						case 5:
							direction = elder->GetActor()->GetForward() - elder->GetActor()->GetRight();
							direction.Normalize();
							spearDirection = elder->GetActor()->rotation.y - 45.0f * ToRadian;
							break;
						case 6:
							direction = -elder->GetActor()->GetForward() + elder->GetActor()->GetRight();
							direction.Normalize();
							spearDirection = elder->GetActor()->rotation.y + 135.0f * ToRadian;
							break;
						case 7:
							direction = -elder->GetActor()->GetForward() - elder->GetActor()->GetRight();
							direction.Normalize();
							spearDirection = elder->GetActor()->rotation.y - 135.0f * ToRadian;
							break;
						}

						Vector3 temp = { RANDOM->Float(-2.0f, 2.0f), 0, RANDOM->Float(-2.0f, 2.0f) };
						Actor* spear = Actor::Create();
						spear->LoadFile("/Unit/SummonSpear.xml");
						spear->SetWorldPos(elder->GetActor()->GetWorldPos() + direction * interval + temp);
						spear->rotation.y = spearDirection;
						spear->rotation.x = RANDOM->Float(30.0f, 50.0f) * ToRadian;
						spear->Update();
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

					if (respawnTime >= RANDOM->Float(1.5f, 3.0f))
					{
						if (respawnPhase == 0)
						{
							respawnTime = 0;
							spearIdx = 0;
							if (RANDOM->Int(0, 1))
							{
								respawnPhase++;
								interval = RANDOM->Float(5.0f, 7.0f);
								elder->jumpAttackMotion++;
							}
							else
							{
								respawnPhase = 0;
								elder->jumpAttackMotion = 0;
								spearBundle.clear();
								elder->state = E_IDLE;
								elder->stompPatern = true;
								elder->paternTime = 2.5f;
							}
						}
						else
						{
							respawnTime = 0;
							spearIdx = 0;
							respawnPhase = 0;
							interval = RANDOM->Float(2.0f, 4.0f);
							elder->jumpAttackMotion = 0;
							spearBundle.clear();
							elder->state = E_IDLE;
							elder->stompPatern = true;
							elder->paternTime = 2.5f;
						}
					}
				}
			}
		}
	}
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
			if(spearBundle.size()==0) elder->RotationForMove();
			/*Vector3 moveDir = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
			moveDir.Normalize();
			elder->actor->rotation.y = atan2f(moveDir.x, moveDir.z);*/
			/*if (elder->state == E_SUMMON)
			{
				if (TIMER->GetTick(spearHitTime, 0.2f))
				{
					SOUND->Play(ELDER_SPEAR);
				}
			}*/
			
			//�÷��̾� ������ �����ϱ� ���� ����
			float chaseTime = 0;
			if (distance >= 0 && distance < 15) chaseTime = 0.3f;
			else if (distance >= 15 && distance < 30) chaseTime = 0.4f;
			else chaseTime = 0.6f;

			//â�� ������ �÷��̾� ������� ���� ����
			if (spearIdx < spearCount * chaseTime)
			{
				targetInfo = PLAYER->GetPlayer()->GetWorldPos() - elder->actor->GetWorldPos();
				distance = targetInfo.Length();
				targetInfo.Normalize();
				dir = targetInfo;
			}
			//�Ÿ��� ���� â ��ȯ �ӵ� ����
			float spearSpeed = 0;
			if (distance >= 0 && distance < 15) spearSpeed = 0.4f;
			else if (distance >= 15 && distance < 30) spearSpeed = 0.2f;
			else spearSpeed = 0.15f;
			//�Ÿ��� ���� ��ȯ�� â ����
			spearCount = distance / 2.0f + 5;

			for (auto& it : spearBundle)
			{
				if (PLAYER->GetPlayerHit(it->collider))
				{
					if (TIMER->GetTick(spearHitTime, 0.2f))
					{
						PARTICLE->PlayParticleEffect(EffectType::HITBLOOD, PLAYER->playerhitPos);
						PLAYER->hitPoint -= 0.05f;
					}
				}
			}

			if (spearBundle.size() < spearCount * BUNDLENUM)
			{
				if (TIMER->GetTick(summonTime, spearSpeed))
				{
					SOUND->Play(ELDER_SPEAR);
					for (int j = 0; j < BUNDLENUM; j++)
					{
						Actor* spear = Actor::Create();
						spear->LoadFile("/Unit/SummonSpear.xml");
						spear->SetWorldPos
						(elder->actor->GetWorldPos() + dir * 2.0f * (spearIdx + 1)+Vector3(RANDOM->Float(-2.0f,2.0f),0, RANDOM->Float(-2.0f, 2.0f)));
						spear->Update();
						//��翡 ���� â ����
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
					spearIdx = 0;
					summonToIdle = 0;
					spearBundle.clear();
					elder->state = E_IDLE;
					
					elder->paternTime = 2.5f;
				}
			}
		}
	}

}