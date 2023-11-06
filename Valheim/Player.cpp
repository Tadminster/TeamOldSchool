#include "stdafx.h"

Player::Player()
{
	actor = Actor::Create();
	actor->name = "Player";
	actor->LoadFile("Player_Male.xml");

	
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	actor->RenderHierarchy();
	

	actor->Update();
	
}

void Player::LateUpdate()
{
}

void Player::Render()
{
	actor->Render();
	
}
