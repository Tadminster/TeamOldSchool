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
	if (INPUT->KeyDown('1')) state->Idle();
	else if (INPUT->KeyDown('2')) state->Move();
	actor->Update();
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	actor->Render();
}

void Player::SetState(PlayerState* state)
{
	this->state = state;
}