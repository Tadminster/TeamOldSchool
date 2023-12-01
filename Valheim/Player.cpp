#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerStatus.h"
#include "ItemProto.h"


Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("/Unit/Player_Male.xml");
	actor->name = "Player";
	actor->anim->aniScale = 0.65f;
	
	playerHp = UI::Create();
	playerHp->LoadFile("/Unit/Player_Hp.xml");
	playerHp->name = "Player_Hp";

	playerSt = UI::Create();
	playerSt->LoadFile("/Unit/Player_St.xml");
	playerSt->name = "Player_St";

	state = IdleState::GetInstance();
	status = new PlayerStatus();

	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));

	hitPoint = 30.0f;
	maxHitpoint = 30.0f;
}

Player::~Player()
{
}

void Player::Init()
{
	actor->SetWorldPos(OBJ->GetStartingPosition());
	//Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
	slidingVector.direction = actor->GetForward();
	playerhitPos = this->GetActor()->GetWorldPos() + Vector3(0, actor->scale.y * 1.5f, 0);
}

void Player::Update()
{
	lastPos = actor->GetWorldPos();
	ImGui::Text("sta %f", staminar);
	ImGui::Text("blocksta %f", blockStaminar);
	if (DEBUGMODE) 
	{
		isPlayerCam = false;
	}
	
	if(hitTime >= 0) hitTime -= DELTA;

	//��� �Լ�--------------------------------------
	//// y�� �ͷ��ο� ���̱�
	SetOnTerrain();
	//// �߷°� ����
	ApplyGravity();
	//// �÷��̾� ��Ʈ��
	PlayerControl();
	PlayerMove();
	//// �÷��̾� �ڿ� ġ��(5�ʵ��� �ǰݴ����� ������ 2�ʴ� 1ȸ��)
	PlayerHealth();
	//// �÷��̾� ���׹̳�(1�ʵ��� ���׹̳� ���� �ൿ ���� ������ �ʴ� 5ȸ��)
	PlayerStaminar();
	//// �÷��̾� ����ġ ����
	GrowthAbility();
	//// �÷��̾� embient, diffuse ����
	UpdateLight();

	status->Update();
	actor->Update();
	playerHp->Update();
	playerSt->Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	actor->Render();
	playerHp->Render();
	playerSt->Render();
}

void Player::Release()
{
}

void Player::RenderHierarchy()
{
	actor->RenderHierarchy();
	playerHp->RenderHierarchy();
	playerSt->RenderHierarchy();
}

bool Player::GetPlayerHit(Collider* atkcol)
{
	if (equippedShield)
	{
		if (state == ShieldState::GetInstance())
		{
			if (equippedShield->GetActor()->collider->Intersect(atkcol))
			{
				if (!isGuard) isGuard = true;
				return true;
			}
			else if (actor->collider->Intersect(atkcol))
			{
				isGuard = false;
				return true;
			}
		}
		else
		{
			if (actor->collider->Intersect(atkcol))
			{
				isGuard = false;
				return true;
			}
		}
	}
	else
	{
		if (actor->collider->Intersect(atkcol))
		{
			isGuard = false;
			return true;
		}
	}
	return false;
}

bool Player::CleanHit(Collider* object)
{
	if (equippedWeapon)
	{
		return equippedWeapon->GetActor()->collider->Intersect(object);
	}
	else if(equippedShield)
	{
		if (actor->Find("mixamorig:RightHand")->collider->Intersect(object)) return true;
	}
	else
	{
		if (actor->Find("mixamorig:RightHand")->collider->Intersect(object))
		{
			
			return true;
		}
		if (actor->Find("mixamorig:LeftHand")->collider->Intersect(object))
		{
			
			return true;
		}
	}
	return false;
}

bool Player::CleanFrame()
{
	//�浹 ������ 31 58 89
	// 29~32 57~59 88~91
	if (state == SwingState::GetInstance())
	{
		if (actor->anim->currentAnimator.currentFrame == 31)
		{
			swingCount++;
			staminar -= status->swingStaminar;
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
		else if (actor->anim->currentAnimator.currentFrame == 59)
		{
			swingCount++;
			staminar -= status->swingStaminar;
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
		else if (actor->anim->currentAnimator.currentFrame == 89)
		{
			swingCount++;
			staminar -= status->swingStaminar;
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
	}
	else if (state == AxeState::GetInstance())
	{
		if (actor->anim->currentAnimator.currentFrame == 24)
		{
			axeCount++;
			staminar -= status->axeStaminar;
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
	}
	//11~13 // 19~21
	else if (state == FistState::GetInstance())
	{
		if (equippedShield)
		{
			if (actor->anim->currentAnimator.currentFrame == 12)
			{
				fistCount++;
				staminar -= status->fistStaminar;
				actor->anim->currentAnimator.currentFrame++;
				return true;
			}
		}
		else
		{
			if (actor->anim->currentAnimator.currentFrame == 12)
			{
				fistCount++;
				staminar -= status->fistStaminar;
				actor->anim->currentAnimator.currentFrame++;
				return true;
			}
			else if (actor->anim->currentAnimator.currentFrame == 20)
			{
				fistCount++;
				staminar -= status->fistStaminar;
				actor->anim->currentAnimator.currentFrame++;
				return true;
			}
		}
	}
	return false;
}

void Player::SetState(PlayerState* state)
{
	this->state = state;
}

void Player::AvtivatePlayerCam()
{
	//���콺��ǥ ȭ�� �߾� ���� & �÷��̾ ī�޶� ȸ���� �ޱ�1
	//if (!DEBUGMODE && !isPlayerCam) 
	//{
	//	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
	//	isPlayerCam = true;
	//}
	//ī�޶� ��ȯ �� ȭ�� ©���� �κ� ����

	if(actor->anim->currentAnimator.animIdx==0) actor->Update();
	
	{
		Camera::main->viewport.x = 0.0f;
		Camera::main->viewport.y = 0.0f;
		Camera::main->viewport.width = App.GetWidth();
		Camera::main->viewport.height = App.GetHeight();

		Camera::main->width = App.GetWidth();
		Camera::main->height = App.GetHeight();
	}
	//�κ� ������ Ŀ�� ���� ����----------------------------------
	if (!INVEN->isOpen && !CRAFT->isOpen)
	{
		//���콺��ǥ ȭ�� �߾� ���� & �÷��̾ ī�޶� ȸ���� �ޱ�2
		ptMouse.x = App.GetHalfWidth();
		ptMouse.y = App.GetHalfHeight();
		Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
		Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
		actor->rotation.y += Rot.y;
		if (Camera::main->rotation.x <= 60.0f * ToRadian && Camera::main->rotation.x >= -30.0f * ToRadian)
		{
			actor->rotation.x += Rot.x * 0.35f;
			Camera::main->rotation.x += Rot.x;
		}
		if (Camera::main->rotation.x > 60.0f * ToRadian) Camera::main->rotation.x = 60.0f * ToRadian;
		else if(Camera::main->rotation.x < -30.0f * ToRadian) Camera::main->rotation.x = -30.0f * ToRadian;
		if (actor->rotation.x > 17.0f * ToRadian) actor->rotation.x = 17.0f * ToRadian;
		else if (actor->rotation.x < -15.0f * ToRadian) actor->rotation.x = -15.0f * ToRadian;
		ClientToScreen(App.GetHandle(), &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);
	}
	actor->Find("PlayerCam")->SetLocalPosY(actor->Find("PlayerCam")->rotation.x * 1.5f + 4.0f);
	actor->Find("PlayerCam")->SetLocalPosZ(actor->Find("PlayerCam")->rotation.x * 4.0f - 6.0f);
	//�������� �ø��� ķ �����̼� �޾ƿ���
	actor->Find("FrustumCam")->SetLocalPos(actor->Find("PlayerCam")->GetLocalPos()+Vector3(0,0,-1.5f));
	actor->Find("FrustumCam")->rotation.x = actor->Find("PlayerCam")->rotation.x;
	actor->Find("FrustumCam")->rotation.y = actor->rotation.y;
	//
	////ī�޶�-�ͷ��� �浹 ����
	//playerCamRay.position = actor->Find("PlayerCam")->GetWorldPos();
	//playerCamRay.direction = (actor->GetWorldPos() + Vector3(0, 2.0f, 0)) - actor->Find("PlayerCam")->GetWorldPos();
	//playerCamRay.direction.Normalize();
	//
	//playerReverseCamRay.position = actor->Find("PlayerOriginCam")->GetWorldPos();
	//playerReverseCamRay.direction = -(actor->Find("PlayerOriginCam")->GetForward()+ actor->Find("PlayerOriginCam")->GetUp()*2.0f);
	//playerReverseCamRay.direction.Normalize();

	////��ǻƮ��ŷ ���� ������ 40���� ������ O_O
	////������ ���� �� ���� + ī�޶� ȸ���� ���� �ϸ� ���������� ������ �ȵǴ� ���� ����
	//if (Utility::RayIntersectMap(playerCamRay, MAP, playerCamHit))
	//{
	//	actor->Find("PlayerCam")->SetWorldPos(playerCamHit + (-actor->Find("RootNode")->GetForward() + actor->Find("RootNode")->GetUp()));
	//}
	//else
	//{
	//	if (Utility::RayIntersectMap(playerReverseCamRay, MAP, playerReverseCamRayHit))
	//	{
	//		if ((actor->Find("PlayerOriginCam")->GetWorldPos() - playerReverseCamRayHit).Length() >= 0.1f)
	//		{
	//			actor->Find("PlayerCam")->SetWorldPos(actor->Find("PlayerOriginCam")->GetWorldPos());
	//		}
	//	}
	//}
}

void Player::PlayerControl()
{
	//Idle�� ����--------------------------------------------------------------------------------------------
	if (state == WalkState::GetInstance() || state == RunState::GetInstance()) 
	{
		if (INPUT->KeyUp('W') || INPUT->KeyUp('A') || INPUT->KeyUp('S') || INPUT->KeyUp('D'))
		{
			state->Idle();
		}
	}
	else if (state == JumpState::GetInstance())
	{
		if (isLand) 
		{
			isJump = false;
			state->Idle();
		}
	}
	else if (state == SwingState::GetInstance() || state == AxeState::GetInstance() || state == FistState::GetInstance())
	{
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			state->Idle();
		}
	}
	else if (state == ShieldState::GetInstance())
	{
		if (INPUT->KeyUp(VK_RBUTTON))
		{
			state->Idle();
		}
	}
	if (staminar <= 0)
	{
		if (actor->anim->GetPlayTime() >= 0.95f)
		{
			if (state == JumpState::GetInstance())
			{
				if (isLand)
				{
					state->Idle();
					staminar = 0.01f;
				}
			}
			else
			{
				state->Idle();
				staminar = 0.01f;
			}
		}
	}
	if (state != JumpState::GetInstance() && isLand)
	{
		isJump = false;
	}
	

	//Walk && Run--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('S') || INPUT->KeyPress('D'))
	{
		if (staminar > 0.1f)
		{
			if (INPUT->KeyPress(VK_SHIFT))
			{
				state->Run();
			}
			else
			{
				state->Walk();
			}
		}
		else state->Walk();
		
	}
	//Jump--------------------------------------------------------------------------------------------
	if (staminar > 0.1f)
	{
		if (INPUT->KeyDown(VK_SPACE) && !isJump)
		{
			gravity = -status->jumpPower;
			cout << gravity;
			state = JumpState::GetInstance();
			state->Jump();
			staminar -= status->jumpStaminar;
			jumpCount++;
		}
	}
	//Fist && Swing--------------------------------------------------------------------------------------------
	if (!INVEN->isOpen && !CRAFT->isOpen)
	{
		if (staminar > 0.1f)
		{
			if (INPUT->KeyPress(VK_LBUTTON))
			{
				if (!equippedWeapon) state->Fist();
				else
				{
					if (equippedWeapon->wType == WeaponType::Blunt) state->Swing();
					else if (equippedWeapon->wType == WeaponType::Axe || equippedWeapon->wType == WeaponType::Pickaxe) state->Axe();
				}
			}
		}
	}
	//Shield--------------------------------------------------------------------------------------
	if (!INVEN->isOpen && !CRAFT->isOpen)
	{
		if (staminar > 0.1f)
		{
			if (INPUT->KeyPress(VK_RBUTTON)) 
				if (equippedShield && state!=BlockFailState::GetInstance())
				{
					state->Shield();
				}
		}
	}
}

void Player::PlayerMove()
{
	//���°��� ���� �̵��ӵ�(FSM�Ϸ��� �ٵ��� ����)
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = status->runSpeed;
	else if (state == FistState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == SwingState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == ShieldState::GetInstance()) moveSpeed = status->shieldSpeed;
	else if (state == AxeState::GetInstance()) moveSpeed = 0;
	else if (state == IdleState::GetInstance()) moveSpeed = 0;
	//Ÿ �ݶ��̴��� �浹������ ��, �̵������� �����̵� ���ͷ� �ޱ� ���� ���ǹ�
	moveDir = Vector3();

	if (INPUT->KeyPress('W')) moveDir += actor->GetForward();
	else if (INPUT->KeyPress('S')) moveDir += -actor->GetForward();
	if (INPUT->KeyPress('A')) moveDir += -actor->GetRight();
	else if (INPUT->KeyPress('D')) moveDir += actor->GetRight();
	moveDir.Normalize();

	actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
}

void Player::MoveBack(Actor* col)
{
	Vector3 slidingDir = col->GetWorldPos() - actor->GetWorldPos();
	slidingDir.y = 0;
	slidingDir.Normalize();
	Vector3 normal = col->collider->GetNormalVector(slidingDir);

	moveDir = slidingDir - normal * (slidingDir.Dot(normal));
	moveDir.Normalize();
	moveDir = -moveDir;
	actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
}

void Player::EquipToHand(ItemProto* item)
{
	if (item->GetType() == ItemType::Shield)
	{
		if (!equippedShield)
		{
			equippedShield = static_cast<ShieldProto*>(item);
			actor->Find("mixamorig:LeftHand")->AddChild(equippedShield->GetActor());
			equippedShield->GetActor()->scale = Vector3(80, 80, 80);
			equippedShield->GetActor()->SetLocalPos(Vector3(0, 0.1f, 0.08f));
			equippedShield->GetActor()->rotation = Vector3(90.0f, 0, 0) * ToRadian;
		}
	}
	else
	{
		if (!equippedWeapon)
		{
			//������ �ϼ��ܰ迡�� ������, ���� �����ϱ�
			equippedWeapon = static_cast<WeaponProto*>(item);;
			actor->Find("mixamorig:RightHandIndex1")->AddChild(equippedWeapon->GetActor());
			equippedWeapon->GetActor()->scale = Vector3(100, 100, 100);
			equippedWeapon->GetActor()->rotation = Vector3(0, 90.0f, 0) * ToRadian;
			equippedWeapon->GetActor()->SetLocalPos(Vector3(-0.1f, 0, -0.05f));
		}
	}
}

void Player::ReleaseToHand(ItemProto* item)
{
	if (item->GetType() == ItemType::Shield)
	{
		if (equippedShield)
		{
			actor->ReleaseNode(equippedShield->GetActor()->name);
			equippedShield = nullptr;
		}
	}
	else
	{
		if (equippedWeapon)
		{
			actor->ReleaseNode(equippedWeapon->GetActor()->name);
			equippedWeapon = nullptr;
		}
	}
}

bool Player::GetItem(ItemProto* item)
{	
	// �����۰� �÷��̾��� �Ÿ� ���
	float distance = Vector3::DistanceSquared(actor->GetWorldPos(), item->GetActor()->GetWorldPos());

	// �Ÿ��� 20 ������ ��
	if (distance < 20)
	{
		// ī�޶� ��ġ -> ���콺�� ���̸� ����
		Ray GetItem = Utility::MouseToRay((Camera*)(actor->Find("PlayerCam")));
		Vector3 hit = {};

		// �����۰� ���̰� �浹���� ��
		if (Utility::RayIntersectTri(GetItem, item->GetActor()->Find("Mesh"), hit))
		{
			// �������� ��ȣ�ۿ� ���� ���θ� true�� ����
			item->SetIsInteraction(true);

			// EŰ�� ������
			if (INPUT->KeyDown('E'))
			{
				// �κ��丮�� ������ �߰��ϰ�	
				INVEN->AddItem(item);
				// ã�Ƴ� ������ ��� ������Ʈ
				RECIPE->DiscoveryItemUpdate(item);
				// �������� ��ȣ�ۿ� ���� ���θ� true�� ����
				item->SetIsInteraction(false);
				return true;
			}
		}
		// �浹���� �ʾ��� ��
		else
		{
			// �������� ��ȣ�ۿ� ���� ���θ� false�� ����
			item->SetIsInteraction(false);
			return false;
		}
	}
	// �Ÿ��� 20 ������ ����
	else
	{
		// �������� ��ȣ�ۿ� ���� ���θ� false�� ����
		item->SetIsInteraction(false);
		return false;
	}
}

void Player::PlayerHit(float damage)
{
	if (hitTime < 0)
	{
		if (isGuard)
		{
			hitPoint -= damage * (1 - (equippedShield->damageReduced + status->blockAbility));
			if (staminar >= blockStaminar)
			{
				state = BlockState::GetInstance();
				state->Block();
			}
			else
			{
				state = BlockFailState::GetInstance();
				state->BlockFail();
			}
			staminar -= blockStaminar;
			blockCount++;
		}
		else
		{
			//�ӽ÷� �÷��̾� Ÿ�ݽ� ���� ����Ʈ �߰��մϴ�
			PARTICLE->PlayParticleEffect(EffectType::HITBLOOD, playerhitPos);
			hitPoint -= damage;
		}
		hitTime = 1.0f;
		healTime = 0;
		isHit = false;
		isGuard = false;
		state->Idle();
	}
}

void Player::GrowthAbility()
{
	if (state == RunState::GetInstance())
	{
		if(actor->anim->aniScale != status->runAnimSpeed) actor->anim->aniScale = status->runAnimSpeed;
		if(!staminarOn) staminarOn = true;
		staminar -= status->runStaminar * DELTA;
	}
	else if (state == JumpState::GetInstance())
	{
		if (actor->anim->aniScale != 0.7f) actor->anim->aniScale = 0.7f;
		if (!staminarOn) staminarOn = true;
		
	}
	else if (state == FistState::GetInstance())
	{
		if (actor->anim->aniScale != status->fistAnimSpeed) actor->anim->aniScale = status->fistAnimSpeed;
		if (!staminarOn) staminarOn = true;
		
	}
	else if (state == SwingState::GetInstance())
	{
		if (actor->anim->aniScale != status->swingAnimSpeed) actor->anim->aniScale = status->swingAnimSpeed;
		if (!staminarOn) staminarOn = true;
	}
	else if (state == AxeState::GetInstance())
	{
		if (actor->anim->aniScale != status->swingAnimSpeed) actor->anim->aniScale = 0.6f;
		if (!staminarOn) staminarOn = true;
	}
	else if (state == ShieldState::GetInstance())
	{
		if (actor->anim->aniScale != 1.0f) actor->anim->aniScale = 1.0f;
		if (!staminarOn) staminarOn = true;
		staminar -= status->shieldStaminar * DELTA;
	}
	else if (state == BlockState::GetInstance())
	{
		state->Block();
		if (actor->anim->aniScale != 0.5f) actor->anim->aniScale = 0.5f;
		if (!staminarOn) staminarOn = true;
	}
	else if (state == BlockFailState::GetInstance())
	{
		state->BlockFail();
		if (actor->anim->aniScale != 0.5f) actor->anim->aniScale = 0.5f;
		if (!staminarOn) staminarOn = true;
	}
	else
	{
		staminarOn = false;
		actor->anim->aniScale = 1.0f;
	}
}

void Player::PlayerHealth()
{
	playerHp->scale.y = growthHp + (float)status->totalLevel * 0.0017f;
	playerHp->Find("FrontHp")->scale.y = hitPoint / maxHitpoint;

	if (hitTime < 0)
	{
		healTime += DELTA;
	}

	if (healTime >= 5.0f)
	{
		if (hitPoint < maxHitpoint)
		{
			if (TIMER->GetTick(healGetTick, 2.0f))
			{
				hitPoint += 1.0f;
				cout << "1ȸ��!" << endl;
			}
		}
	}
	if (hitPoint > maxHitpoint) hitPoint = maxHitpoint;
}

void Player::PlayerStaminar()
{
	playerSt->scale.x = growthStaminar + (float)status->totalLevel * 0.0025f;
	playerSt->Find("Front_St")->scale.x = staminar / maxStaminar;

	if (staminarOn)
	{
		staminarTime = 0;
	}
	else
	{
		if(staminarTime < 1.0f)	staminarTime += DELTA;
		else
		{
			if(staminar < maxStaminar) staminar += 5.0f * DELTA;
		}
		
	}
	if (staminar > maxStaminar) staminar = maxStaminar;
	else if (staminar < 0) staminar = 0;

	if (staminar == maxStaminar) playerSt->visible = false;
	else playerSt->visible = true;
}

bool Player::IsDestroyed()
{
	return false;
}

void Player::UpdateLight()
{
	float lightRatio = max(0.2f, LIGHT->GetTimeRatio());
	actor->Find("body")->material->ambient = Color(lightRatio, lightRatio, lightRatio, 1.0f);
}

WeaponProto* Player::GetPlayerWeapon()
{
	if (equippedWeapon) return equippedWeapon;
}

float Player::GetWeaponDMG()
{
	if (equippedWeapon)
	{
		randomDMG = RANDOM->Float(-equippedWeapon->damage * 0.2f, equippedWeapon->damage * 0.2f);
		return equippedWeapon->damage + randomDMG;
	}
	else
	{
		randomDMG = RANDOM->Float(-fistDMG * 0.2f, fistDMG * 0.2f);
		return fistDMG + randomDMG;
	}
}

Vector3 Player::GetCollisionPoint()
{
	if (equippedWeapon) return equippedWeapon->GetActor()->Find("CollisionPoint")->GetWorldPos();
	else return actor->Find("mixamorig:RightHand")->GetWorldPos();
}

bool Player::GetWeoponCollider(Collider* object)
{
	if (equippedWeapon)
	{
		return equippedWeapon->actor->collider->Intersect(object);
	}
	else if(equippedShield)
	{
		if (actor->Find("mixamorig:RightHand")->collider->Intersect(object)) return true;
	}
	else
	{
		if (actor->Find("mixamorig:RightHand")->collider->Intersect(object)) return true;
		else if (actor->Find("mixamorig:LeftHand")->collider->Intersect(object)) return true;
	}
}

WeaponType Player::GetWeaponType()
{		
	if (equippedWeapon) return equippedWeapon->wType;
	else return WeaponType::Fist;
}

void Player::DestructionEvent()
{
}
