#include "stdafx.h"
#include "PlayerState.h"
#include "ItemProto.h"


Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player_Male.xml");
	actor->name = "Player";
	actor->anim->aniScale = 0.65f;
	
	playerHp = UI::Create();
	playerHp->LoadFile("Player_Hp.xml");
	playerHp->name = "Player_Hp";

	state = IdleState::GetInstance();

	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));

	hitPoint = 30.0f;
	maxHitpoint = 30.0f;
}

Player::~Player()
{
}

void Player::Init()
{
	actor->SetWorldPos(Vector3(0,10,0));
	//Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
	slidingVector.direction = actor->GetForward();
}

void Player::Update()
{
	lastPos = actor->GetWorldPos();
	
	if (DEBUGMODE) 
	{
		isPlayerCam = false;
	}

	if(hitTime >= 0) hitTime -= DELTA;
	
	//��� �Լ�
	PlayerControl();
	PlayerMove();
	PlayerHealth();
	ApplyGravity();
	GrowthAbility();

	actor->Update();
	playerHp->Update();
}

void Player::LateUpdate()
{
	//�÷��̾� - �ͷ��� �浹
	SetOnTerrain();

	//��� �浹(�ڿ������� �պ���)
	Vector3 dir = actor->GetWorldPos() - lastPos;
	Vector3 dir2 = dir;
	dir2.y = 0;
	dir.Normalize();
	dir2.Normalize();
	float dot = dir.Dot(dir2);
	if (moveSpeed != 0)
	{
		if (dot < 0.7 and (actor->GetWorldPos().y > lastPos.y))
		{
			//actor->SetWorldPos(lastPos);
			//actor->Update();
		}
	}
}

void Player::Render()
{
	actor->Render();
	playerHp->Render();
}

void Player::Release()
{
}

void Player::RenderHierarchy()
{
	actor->RenderHierarchy();
	playerHp->RenderHierarchy();
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
		if (actor->Find("mixamorig:RightHand")->collider->Intersect(object)) return true;
		else if (actor->Find("mixamorig:LeftHand")->collider->Intersect(object)) return true;
	}
	return false;
}

bool Player::CleanFrame()
{
	//�浹 ������ 31 58 89
	if (state == SwingState::GetInstance())
	{
		if (actor->anim->currentAnimator.currentFrame == 31)
		{
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
		else if (actor->anim->currentAnimator.currentFrame == 59)
		{
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
		else if (actor->anim->currentAnimator.currentFrame == 89)
		{
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
	}
	else if (state == AxeState::GetInstance())
	{
		if (actor->anim->currentAnimator.currentFrame == 24)
		{
			actor->anim->currentAnimator.currentFrame++;
			return true;
		}
	}
	else if (state == FistState::GetInstance())
	{
		if (equippedShield)
		{
			if (actor->anim->currentAnimator.currentFrame == 12)
			{
				actor->anim->currentAnimator.currentFrame++;
				return true;
			}
		}
		else
		{
			if (actor->anim->currentAnimator.currentFrame == 12)
			{
				actor->anim->currentAnimator.currentFrame++;
				return true;
			}
			else if (actor->anim->currentAnimator.currentFrame == 20)
			{
				actor->anim->currentAnimator.currentFrame++;
				return true;
			}
		}
	}
	return false;
	/*if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 31)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 59)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 89)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}*/
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
		Camera::main->rotation.x += Rot.x;
		ClientToScreen(App.GetHandle(), &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);
	}

	//�������� �ø��� ķ �����̼� �޾ƿ���
	actor->Find("FrustumCam")->rotation.x = actor->Find("PlayerCam")->rotation.x;
	actor->Find("FrustumCam")->rotation.y = actor->rotation.y;
	
	//ī�޶�-�ͷ��� �浹 ����
	playerCamRay.position = actor->Find("PlayerCam")->GetWorldPos();
	playerCamRay.direction = (actor->GetWorldPos() + Vector3(0, 2.0f, 0)) - actor->Find("PlayerCam")->GetWorldPos();
	playerCamRay.direction.Normalize();
	
	playerReverseCamRay.position = actor->Find("PlayerOriginCam")->GetWorldPos();
	playerReverseCamRay.direction = -(actor->Find("PlayerOriginCam")->GetForward()+ actor->Find("PlayerOriginCam")->GetUp()*2.0f);
	playerReverseCamRay.direction.Normalize();

	//��ǻƮ��ŷ ���� ������ 40���� ������ O_O
	//������ ���� �� ���� + ī�޶� ȸ���� ���� �ϸ� ���������� ������ �ȵǴ� ���� ����
	if (Utility::RayIntersectMap(playerCamRay, MAP, playerCamHit))
	{
		actor->Find("PlayerCam")->SetWorldPos(playerCamHit + (-actor->Find("RootNode")->GetForward() + actor->Find("RootNode")->GetUp()));
	}
	else
	{
		if (Utility::RayIntersectMap(playerReverseCamRay, MAP, playerReverseCamRayHit))
		{
			if ((actor->Find("PlayerOriginCam")->GetWorldPos() - playerReverseCamRayHit).Length() >= 0.1f)
			{
				actor->Find("PlayerCam")->SetWorldPos(actor->Find("PlayerOriginCam")->GetWorldPos());
			}
		}
	}
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
	//Walk && Run--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('S') || INPUT->KeyPress('D'))
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
	//Jump--------------------------------------------------------------------------------------------
	if (INPUT->KeyDown(VK_SPACE) && !isJump) 
	{
		state = JumpState::GetInstance();
		state->Jump();
	}
	//Fist && Swing--------------------------------------------------------------------------------------------
	if (!INVEN->isOpen && !CRAFT->isOpen)
	{
		if (INPUT->KeyPress(VK_LBUTTON)) 
		{
			if(!equippedWeapon) state->Fist();
			else
			{
				if (equippedWeapon->wType == WeaponType::Blunt) state->Swing();
				else if (equippedWeapon->wType == WeaponType::Axe || equippedWeapon->wType == WeaponType::Pickaxe) state->Axe();
			}
		}
	}
	//Shield--------------------------------------------------------------------------------------
	if (!INVEN->isOpen && !CRAFT->isOpen)
	{
		if (INPUT->KeyPress(VK_RBUTTON)) if (equippedShield) state->Shield();
	}
}

void Player::PlayerMove()
{
	//���°��� ���� �̵��ӵ�(FSM�Ϸ��� �ٵ��� ����)
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == FistState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == SwingState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == ShieldState::GetInstance()) moveSpeed = SWINGSPEED;
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
		//�ӽ÷� �÷��̾� Ÿ�ݽ� ���� ����Ʈ �߰��մϴ�
		Vector3 playerhitPos = this->GetActor()->GetWorldPos() + Vector3(0, 2, 0);
		PARTICLE->PlayParticleEffect(EffectType::HITBLOOD, playerhitPos);
		//------------------------------------------------------------
		hitPoint -= damage;
		hitTime = 1.0f;
		isHit = false;
		healTime = 0;
	}
}

void Player::GrowthAbility()
{
	if (state == RunState::GetInstance())
	{
		actor->anim->aniScale = 0.7f;
	}
	else if (state == JumpState::GetInstance())
	{
		actor->anim->aniScale = 0.7f;
	}
	else if (state == FistState::GetInstance())
	{
		actor->anim->aniScale = 0.5f;
	}
	else if (state == SwingState::GetInstance())
	{
		actor->anim->aniScale = 0.6f;
	}
	else if (state == AxeState::GetInstance())
	{
		actor->anim->aniScale = 0.6f;
	}
	else
	{
		actor->anim->aniScale = 1.0f;
	}
}

void Player::PlayerHealth()
{
	playerHp->scale.y = growthHp;
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

bool Player::IsDestroyed()
{
	return false;
}

WeaponProto* Player::GetPlayerWeapon()
{
	if (equippedWeapon) return equippedWeapon;
}

float Player::GetWeaponDMG()
{
	if (equippedWeapon) return equippedWeapon->damage;
	else return fistDMG;
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
