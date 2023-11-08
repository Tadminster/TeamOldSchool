#include "stdafx.h"
#include "PlayerState.h"

Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player_Male.xml");
	actor->name = "Player";

	state = IdleState::GetInstance();
}

Player::~Player()
{
}

void Player::Init()
{

}

void Player::Update()
{
	lastPos = actor->GetWorldPos();
	
	PlayerControl();

	actor->Update();
}

void Player::LateUpdate()
{
    Ray playerTop;
    playerTop.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
    playerTop.direction = Vector3(0, -1, 0);
    Vector3 hit;
    if (Utility::RayIntersectMap(playerTop, MAP, hit))
    {
        actor->SetWorldPosY(hit.y);
    }
    actor->Update();

	Vector3 dir = actor->GetWorldPos() - lastPos;
	Vector3 dir2 = dir;
	dir2.y = 0;
	dir.Normalize();
	dir2.Normalize();
	float dot = dir.Dot(dir2);
	//cout << dot << endl;
	if (state==MoveState::GetInstance())
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
	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
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
	if (INPUT->KeyPress('W')) state->Move('W');
	else if (INPUT->KeyPress('S')) state->Move('S');
	if (INPUT->KeyPress('A')) state->Move('A');
	else if (INPUT->KeyPress('D')) state->Move('D');

	if (state == MoveState::GetInstance()) {
		if (INPUT->KeyUp('W') && INPUT->KeyUp('A') && INPUT->KeyUp('S') && INPUT->KeyUp('D')) {
			state->Idle();
		}
	}

	
}
