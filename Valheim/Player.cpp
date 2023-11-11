#include "stdafx.h"
#include "PlayerState.h"

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
	if (!DEBUGMODE) {
		PlayerControl();
		PlayerMove();
	}
	else isPlayerCam = false;
	//�߷� ����
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;

	actor->Update();
}

void Player::LateUpdate()
{
	//Player - Terrain �浹����
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

	ImGui::Text("%f actor y", actor->GetWorldPos().y);
	ImGui::Text("%f hit y", hit.y);
	ImGui::Text("%d island", isLand);
	ImGui::Text("%d jump", isJump);
	
    actor->Update();

	//��� �浹(�ڿ������� �պ���)
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
	//���콺��ǥ ȭ�� �߾� ���� & �÷��̾ ī�޶� ȸ���� �ޱ�
	if (!DEBUGMODE && !isPlayerCam) {
		Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
		isPlayerCam = true;
	}
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
	//Idle--------------------------------------------------------------------------------------------
	if (state == WalkState::GetInstance() || state == RunState::GetInstance()) {
		if (INPUT->KeyUp('W') || INPUT->KeyUp('A') || INPUT->KeyUp('S') || INPUT->KeyUp('D')) {
			state->Idle();
		}
	}
	if (isJump) {
		if (isLand) {
			isJump = false;
			state->Idle();
		}
	}
	//Run--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress(VK_SHIFT)) {
		if (INPUT->KeyPress('W')) state->Run('W');
		else if (INPUT->KeyPress('S')) state->Run('S');
		if (INPUT->KeyPress('A')) state->Run('A');
		else if (INPUT->KeyPress('D')) state->Run('D');
	}
	//Walk--------------------------------------------------------------------------------------------
	else {
		if (INPUT->KeyPress('W')) state->Walk('W');
		else if (INPUT->KeyPress('S')) state->Walk('S');
		if (INPUT->KeyPress('A')) state->Walk('A');
		else if (INPUT->KeyPress('D')) state->Walk('D');
	}
	//Jump--------------------------------------------------------------------------------------------
	if (INPUT->KeyDown(VK_SPACE)) {
		state = JumpState::GetInstance();
		state->Jump();
	}
	//Swing--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress(VK_LBUTTON)) {
		state->Swing();
	}


	if (state == IdleState::GetInstance()) ImGui::Text("%d state", 1);
	else if (state == WalkState::GetInstance()) ImGui::Text("%d state", 2);
	else if (state == RunState::GetInstance()) ImGui::Text("%d state", 3);
}

void Player::PlayerMove()
{
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	

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
