#include "stdafx.h"
#include "PlayerState.h"
#include "Item.h"

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
	actor->SetWorldPosY(30);
	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
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

void Player::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Player::SetState(PlayerState* state)
{
	this->state = state;
}

void Player::AvtivatePlayerCam()
{
	//마우스좌표 화면 중앙 고정 & 플레이어가 카메라 회전값 받기
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
	//마우스좌표 화면 중앙 고정 & 플레이어가 카메라 회전값 받기
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
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == SwingState::GetInstance()) moveSpeed = 0;

	if (INPUT->KeyPress('W')) 
	{
		actor->MoveWorldPos(actor->GetForward() * moveSpeed * DELTA);
	}
	else if (INPUT->KeyPress('S'))
	{
		actor->MoveWorldPos(-actor->GetForward() * moveSpeed * DELTA);
	}
	if (INPUT->KeyPress('A'))
	{
		actor->MoveWorldPos(-actor->GetRight() * moveSpeed * DELTA);
	}
	else if (INPUT->KeyPress('D'))
	{
		actor->MoveWorldPos(actor->GetRight() * moveSpeed * DELTA);
	}
}
//나중에 인벤토리 클래스로 매개변수 바꾸기
void Player::EquipToHand(Prototype* item)
{
	actor->Find("mixamorig:RightHandIndex1")->AddChild(item->GetActor());
	actor->Find(item->GetActor()->name)->scale = Vector3(1, 1, 1);
}

void Player::ReleaseToHand()
{

}
