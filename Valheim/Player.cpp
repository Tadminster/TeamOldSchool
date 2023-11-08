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
	if (INPUT->KeyPress(VK_UP)) state->Move();
	actor->Update();
}

void Player::LateUpdate()
{
	
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
	//actor->Find("RootNode")->rotation.x += Rot.x;
	actor->rotation.y += Rot.y;
	//player->body->rotation.y += Rot.y;
	Camera::main->rotation.x += Rot.x;
	ClientToScreen(App.GetHandle(), &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}
