#include "stdafx.h"
#include "PlayerState.h"
#include "ItemProto.h"


Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player_Male.xml");
	actor->name = "Player";
	actor->anim->aniScale = 0.65f;
	
	state = IdleState::GetInstance();
	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
}

Player::~Player()
{
}

void Player::Init()
{
	actor->SetWorldPos(Vector3(0,20,0));
	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));

	slidingVector.direction = actor->GetForward();
}

void Player::Update()
{
	lastPos = actor->GetWorldPos();
	if (!DEBUGMODE) 
	{
		PlayerControl();
		PlayerMove();
	}
	else
	{
		isPlayerCam = false;
	}
	if(hitTime >= 0) hitTime -= DELTA;
	//중력 구현
	ApplyGravity();

	actor->Update();
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
}

void Player::Release()
{
}

void Player::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Player::CleanHit(Collider* object)
{
	if (equippedHand)
	{
		return equippedHand->GetActor()->collider->Intersect(object);
	}
	else return false;
}

bool Player::CleanFrame()
{
	//충돌 프레임 31 58 89
	if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 31)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 58)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 89)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else return false;
}

void Player::SetState(PlayerState* state)
{
	this->state = state;
}

void Player::AvtivatePlayerCam()
{
	//마우스좌표 화면 중앙 고정 & 플레이어가 카메라 회전값 받기1
	if (!DEBUGMODE && !isPlayerCam) 
	{
		Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
		isPlayerCam = true;
	}
	//카메라 전환 시 화면 짤리는 부분 방지
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
	playerCamRay.direction = (actor->GetWorldPos()+Vector3(0,2.0f,0)) - actor->Find("PlayerCam")->GetWorldPos();
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
	else if (state == SwingState::GetInstance())
	{
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			state->Idle();
		}
	}
	//Walk & Run--------------------------------------------------------------------------------------------
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
	//Swing--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress(VK_LBUTTON)) 
	{
		state->Swing();
	}
}

void Player::PlayerMove()
{
	//상태값에 따른 이동속도(FSM완료후 다듬을 예정)
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == IdleState::GetInstance()) moveSpeed = 0;
	else if (state == SwingState::GetInstance()) moveSpeed = 0;

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

void Player::EquipToHand(ItemProto* item)
{
	if (!equippedHand)
	{
		//아이템 완성단계에서 스케일, 각도 조절하기
		equippedHand = item;
		actor->Find("mixamorig:RightHandIndex1")->AddChild(equippedHand->GetActor());
		equippedHand->GetActor()->scale = Vector3(50, 50, 50);
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

void Player::MoveBack(Actor* col)
{
	Vector3 slidingDir =  col->GetWorldPos() - actor->GetWorldPos();
	slidingDir.y = 0;
	slidingDir.Normalize();
	Vector3 normal = col->collider->GetNormalVector(slidingDir);

	moveDir = slidingDir - normal * (slidingDir.Dot(normal));
	moveDir.Normalize();
	moveDir = -moveDir;
	actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
}

bool Player::GetItem(ItemProto* item)
{	
	//충돌값 트루일 때, 아이템 주을건지 ui생성
	Ray GetItem = Utility::MouseToRay((Camera*)(actor->Find("PlayerCam")));
	Vector3 hit = {};
		if (Utility::RayIntersectTri(GetItem, item->GetActor()->Find("Mesh"), hit))
		{
			item->SetIsInteraction(true);

			if (INPUT->KeyDown('E'))
			{
				INVEN->AddItem(item);
				return true;
			}
		}
		else
		{
			item->SetIsInteraction(false);
		}
	return false;
}

void Player::PlayerHit()
{
	if (hitTime < 0)
	{
		cout << "PlayerHit!";
		hitTime = 1.0f;
		isHit = false;
	}
}

bool Player::IsDestroyed()
{
	return false;
}

void Player::DestructionEvent()
{
}
