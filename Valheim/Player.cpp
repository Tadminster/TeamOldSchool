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