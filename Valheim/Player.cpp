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
	
	//기능 함수
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
	//플레이어 - 터레인 충돌
	SetOnTerrain();

	//경사 충돌(자연스럽게 손보기)
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
	if (equippedHand)
	{
		return equippedHand->GetActor()->collider->Intersect(object);
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
	//충돌 프레임 31 58 89
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
	//마우스좌표 화면 중앙 고정 & 플레이어가 카메라 회전값 받기1
	//if (!DEBUGMODE && !isPlayerCam) 
	//{
	//	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
	//	isPlayerCam = true;
	//}
	//카메라 전환 시 화면 짤리는 부분 방지

	if(actor->anim->currentAnimator.animIdx==0) actor->Update();
	
	{
		Camera::main->viewport.x = 0.0f;
		Camera::main->viewport.y = 0.0f;
		Camera::main->viewport.width = App.GetWidth();
		Camera::main->viewport.height = App.GetHeight();

		Camera::main->width = App.GetWidth();
		Camera::main->height = App.GetHeight();
	}
	//인벤 열리면 커서 고정 해제----------------------------------
	if (!INVEN->isOpen)
	{
		//마우스좌표 화면 중앙 고정 & 플레이어가 카메라 회전값 받기2
		ptMouse.x = App.GetHalfWidth();
		ptMouse.y = App.GetHalfHeight();
		Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
		Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
		actor->rotation.y += Rot.y;
		Camera::main->rotation.x += Rot.x;
		ClientToScreen(App.GetHandle(), &ptMouse);
		SetCursorPos(ptMouse.x, ptMouse.y);
	}

	//프러스텀 컬링용 캠 로테이션 받아오기
	actor->Find("FrustumCam")->rotation.x = actor->Find("PlayerCam")->rotation.x;
	actor->Find("FrustumCam")->rotation.y = actor->rotation.y;
	
	//카메라-터레인 충돌 레이
	playerCamRay.position = actor->Find("PlayerCam")->GetWorldPos();
	playerCamRay.direction = (actor->GetWorldPos() + Vector3(0, 2.0f, 0)) - actor->Find("PlayerCam")->GetWorldPos();
	playerCamRay.direction.Normalize();
	
	playerReverseCamRay.position = actor->Find("PlayerOriginCam")->GetWorldPos();
	playerReverseCamRay.direction = -(actor->Find("PlayerOriginCam")->GetForward()+ actor->Find("PlayerOriginCam")->GetUp()*2.0f);
	playerReverseCamRay.direction.Normalize();

	//컴퓨트피킹 쓰면 프레임 40정도 떨어짐 O_O
	//가끔씩 원인 모를 이유 + 카메라 회전을 빨리 하면 간헐적으로 적용이 안되는 현상 존재
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
	//Idle로 복귀--------------------------------------------------------------------------------------------
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
	else if (state == SwingState::GetInstance() || state == FistState::GetInstance())
	{
		if (INPUT->KeyUp(VK_LBUTTON))
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
			if(!equippedHand) state->Fist();
			else
			{
				if (equippedHand->wType == WeaponType::Blunt) state->Swing();
				else if (equippedHand->wType == WeaponType::Axe || equippedHand->wType == WeaponType::Pickaxe) state->Axe();
			}
		}
	}
}

void Player::PlayerMove()
{
	//상태값에 따른 이동속도(FSM완료후 다듬을 예정)
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == FistState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == SwingState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == AxeState::GetInstance()) moveSpeed = SWINGSPEED;
	else if (state == IdleState::GetInstance()) moveSpeed = 0;
	//타 콜라이더와 충돌상태일 때, 이동각도를 슬라이딩 벡터로 받기 위한 조건문
	if (!istouch)
	{
		moveDir = Vector3();

		if (INPUT->KeyPress('W')) moveDir += actor->GetForward();
		else if (INPUT->KeyPress('S')) moveDir += -actor->GetForward();
		if (INPUT->KeyPress('A')) moveDir += -actor->GetRight();
		else if (INPUT->KeyPress('D')) moveDir += actor->GetRight();
		moveDir.Normalize();

		actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
	}
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

void Player::EquipToHand(WeaponProto* item)
{
	if (!equippedHand)
	{
		//아이템 완성단계에서 스케일, 각도 조절하기
		equippedHand = item;
		actor->Find("mixamorig:RightHandIndex1")->AddChild(equippedHand->GetActor());
		equippedHand->GetActor()->scale = Vector3(100, 100, 100);
		equippedHand->GetActor()->rotation = Vector3(0, 90.0f, 0) * ToRadian;
		equippedHand->GetActor()->SetLocalPos(Vector3(-0.1f, 0, -0.05f));
	}
}

void Player::ReleaseToHand()
{
	if (equippedHand)
	{
		actor->ReleaseNode(equippedHand->GetActor()->name);
		equippedHand = nullptr;
	}
}



bool Player::GetItem(ItemProto* item)
{	
	// 아이템과 플레이어의 거리 계산
	float distance = Vector3::DistanceSquared(actor->GetWorldPos(), item->GetActor()->GetWorldPos());

	// 거리가 20 이하일 때
	if (distance < 20)
	{
		// 카메라 위치 -> 마우스로 레이를 생성
		Ray GetItem = Utility::MouseToRay((Camera*)(actor->Find("PlayerCam")));
		Vector3 hit = {};

		// 아이템과 레이가 충돌했을 때
		if (Utility::RayIntersectTri(GetItem, item->GetActor()->Find("Mesh"), hit))
		{
			// 아이템의 상호작용 가능 여부를 true로 설정
			item->SetIsInteraction(true);

			// E키를 누르면
			if (INPUT->KeyDown('E'))
			{
				// 인벤토리에 아이템 추가하고	
				INVEN->AddItem(item);
				// 찾아낸 아이템 목록 업데이트
				RECIPE->DiscoveryItemUpdate(item);
				// 아이템의 상호작용 가능 여부를 true로 설정
				item->SetIsInteraction(false);
				return true;
			}
		}
		// 충돌하지 않았을 때
		else
		{
			// 아이템의 상호작용 가능 여부를 false로 설정
			item->SetIsInteraction(false);
			return false;
		}
	}
	// 거리가 20 이하일 때도
	else
	{
		// 아이템의 상호작용 가능 여부를 false로 설정
		item->SetIsInteraction(false);
		return false;
	}
}

void Player::PlayerHit(float damage)
{
	if (hitTime < 0)
	{
		//임시로 플레이어 타격시 출혈 이펙트 추가합니다
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
		if (hitPoint <= maxHitpoint)
		{
			if (TIMER->GetTick(healGetTick, 2.0f))
			{
				hitPoint += 1.0f;
				cout << "1회복!" << endl;
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
	if (equippedHand) return equippedHand;
}

float Player::GetWeaponDMG()
{
	if (equippedHand) return equippedHand->damage;
	else return fistDMG;
}

Vector3 Player::GetCollisionPoint()
{
	if (equippedHand) return equippedHand->GetActor()->Find("CollisionPoint")->GetWorldPos();
	else return actor->Find("mixamorig:LeftHand")->GetWorldPos();
}

bool Player::GetWeoponCollider(Collider* object)
{
	if (equippedHand)
	{
		return equippedHand->actor->collider->Intersect(object);
	}
	else
	{
		if (actor->Find("mixamorig:RightHand")->collider->Intersect(object)) return true;
		else if (actor->Find("mixamorig:LeftHand")->collider->Intersect(object)) return true;
	}
}

WeaponType Player::GetWeaponType()
{		
	if (equippedHand) return equippedHand->wType;
	else return WeaponType::Fist;
}

void Player::DestructionEvent()
{
}
