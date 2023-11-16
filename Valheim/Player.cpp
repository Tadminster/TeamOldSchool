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
	else isPlayerCam = false;
	//중력 구현
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;

	actor->Update();
}

void Player::LateUpdate()
{
	//Player - Terrain 충돌판정
    Ray playerTop;
	playerTop.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
    playerTop.direction = Vector3(0, -1, 0);
    Vector3 hit;
    if (Utility::RayIntersectMap(playerTop, MAP, hit))
    {
		if (actor->GetWorldPos().y - hit.y < 0.1f) {
			actor->SetWorldPosY(hit.y);
			isLand = true;
		}
		else isLand = false;
    }

	//ImGui::Text("%f actor y", actor->GetWorldPos().y);
	//ImGui::Text("%f hit y", hit.y);
	
    actor->Update();

	//경사 충돌(자연스럽게 손보기)
	Vector3 dir = actor->GetWorldPos() - lastPos;
	Vector3 dir2 = dir;
	dir2.y = 0;
	dir.Normalize();
	dir2.Normalize();
	float dot = dir.Dot(dir2);
	if (state==WalkState::GetInstance())
	{
		if (dot < 0.7 and (actor->GetWorldPos().y > lastPos.y))
		{
			actor->SetWorldPos(lastPos);
			actor->Update();
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

bool Player::CleanHit(string name, Collider* object)
{
	if (actor->Find(name))
	{
		return actor->Find(name)->collider->Intersect(object);
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
	//마우스좌표 화면 중앙 고정 & 플레이어가 카메라 회전값 받기2
	POINT ptMouse;
	ptMouse.x = App.GetHalfWidth();
	ptMouse.y = App.GetHalfHeight();
	Vector3 Rot;
	Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
	Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
	actor->rotation.y += Rot.y;
	Camera::main->rotation.x += Rot.x;
	ClientToScreen(App.GetHandle(), &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
	//프러스텀 컬링용 캠 로테이션 받아오기
	actor->Find("FrustumCam")->rotation.x = actor->Find("PlayerCam")->rotation.x;
	actor->Find("FrustumCam")->rotation.y = actor->rotation.y;
	
	//카메라-터레인 충돌 레이
	Ray PlayerCamRay;
	PlayerCamRay.position = actor->Find("PlayerCam")->GetWorldPos();
	PlayerCamRay.direction = (actor->GetWorldPos()+Vector3(0,2.0f,0)) - actor->Find("PlayerCam")->GetWorldPos();
	PlayerCamRay.direction.Normalize();
	Vector3 hit;
	//카메라가 복귀할 조건, 좌표 레이
	Ray PlayerOriginCamRay;
	PlayerOriginCamRay.position = actor->Find("PlayerOriginCam")->GetWorldPos();
	//PlayerOriginCamRay.direction = actor->GetWorldPos() - actor->Find("PlayerOriginCam")->GetWorldPos();
	PlayerOriginCamRay.direction = (actor->GetWorldPos() + Vector3(0, 2.0f, 0)) - actor->Find("PlayerCam")->GetWorldPos();
	PlayerOriginCamRay.direction.Normalize();
	Vector3 hit2;
	Ray PlayerReverseOriginCamRay;
	PlayerReverseOriginCamRay.position = actor->Find("PlayerOriginCam")->GetWorldPos();
	PlayerReverseOriginCamRay.direction = -(actor->Find("PlayerOriginCam")->GetForward()+ actor->Find("PlayerOriginCam")->GetUp()*2.0f);
	PlayerReverseOriginCamRay.direction.Normalize();
	Vector3 hit3;
	if (Utility::RayIntersectMap(PlayerCamRay, MAP, hit))
	{
		if ((actor->Find("PlayerCam")->GetWorldPos() - hit).Length() < 0.1f)
		{
			actor->Find("PlayerCam")->SetWorldPos(hit+(-actor->Find("RootNode")->GetForward() + actor->Find("RootNode")->GetUp()));
		}
	}
	else
	{
		if (Utility::RayIntersectMap(PlayerReverseOriginCamRay, MAP, hit3))
		{
			if ((actor->Find("PlayerOriginCam")->GetWorldPos() - hit3).Length() >= 0.1f)
			{
				ImGui::Text("hit3.y %f", hit3.y);
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

	//if (state == SwingState::GetInstance()) ImGui::Text("%d state", 1);
	//else if (state == WalkState::GetInstance()) ImGui::Text("%d state", 2);
	//else if (state == RunState::GetInstance()) ImGui::Text("%d state", 3);
}

void Player::PlayerMove()
{
	//상태값에 따른 이동속도
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == IdleState::GetInstance()) moveSpeed = 0;
	else if (state == SwingState::GetInstance()) moveSpeed = 0;
	
	if (!istouch)
	{
		//이동 각도 계산
		if (INPUT->KeyPress('W') && INPUT->KeyPress('A'))
		{
			moveDir = actor->GetForward() - actor->GetRight();
			moveDir.Normalize();
			//actor->MoveWorldPos(normalize * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('W') && INPUT->KeyPress('D'))
		{
			moveDir = actor->GetForward() + actor->GetRight();
			moveDir.Normalize();
			//actor->MoveWorldPos(normalize * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S') && INPUT->KeyPress('A'))
		{
			moveDir = -actor->GetForward() - actor->GetRight();
			moveDir.Normalize();
			//actor->MoveWorldPos(normalize * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S') && INPUT->KeyPress('D'))
		{
			moveDir = -actor->GetForward() + actor->GetRight();
			moveDir.Normalize();
			//actor->MoveWorldPos(normalize * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('W'))
		{
			moveDir = actor->GetForward();
			//actor->MoveWorldPos(actor->GetForward() * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('A'))
		{
			moveDir = -actor->GetRight();
			//actor->MoveWorldPos(-actor->GetRight() * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('S'))
		{
			moveDir = -actor->GetForward();
			//actor->MoveWorldPos(-actor->GetForward() * moveSpeed * DELTA);
		}
		else if (INPUT->KeyPress('D'))
		{
			moveDir = actor->GetRight();
			//actor->MoveWorldPos(actor->GetRight() * moveSpeed * DELTA);
		}
	}
	//실제 이동
	actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
}
//나중에 인벤토리 클래스로 매개변수 바꾸기
void Player::EquipToHand(Prototype* item)
{
	actor->Find("mixamorig:RightHandIndex1")->AddChild(item->GetActor());
	actor->Find(item->GetActor()->name)->scale = Vector3(50, 50, 50);
	actor->Find(item->GetActor()->name)->SetLocalPos(Vector3(-0.1f, 0, -0.05f));
	actor->Find(item->GetActor()->name)->rotation = Vector3(0, 90.0f, 0) * ToRadian;

	isEquip = true;
}

void Player::ReleaseToHand()
{
	//
}

void Player::MoveBack(Actor* col)
{
	slidingVector.position = actor->GetWorldPos() + Vector3(0, 1.5f, 0);
	
	if (col->collider->Intersect(slidingVector, slidingVectorHit))
	{
		moveDir = moveDir - -col->GetForward() * (moveDir.Dot(-col->GetForward()));
	}
	moveDir.Normalize();
	
}

bool Player::GetItem(ItemProto* item)
{	
	//충돌값 트루일 때, 아이템 주을건지 ui생성
	Ray GetItem = Utility::MouseToRay((Camera*)(actor->Find("PlayerCam")));
	Vector3 hit = {};
		if (Utility::RayIntersectTri(GetItem, item->GetActor()->Find("Mesh"), hit))
		{
			if (INPUT->KeyDown('E'))
			{
				INVEN->AddItem(item);
				return true;
			}
		}
	return false;
}

bool Player::IsDestroyed()
{
	return false;
}

void Player::DestructionEvent()
{
}
