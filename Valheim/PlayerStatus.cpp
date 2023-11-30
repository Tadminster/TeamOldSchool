#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
	
}

PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::Update()
{
	RunExp();
	JumpExp();
}

void PlayerStatus::RunExp()
{
	if (PLAYER->state == RunState::GetInstance())
	{
		runExp += DELTA;
	}

	if (runExp >= requiredExp_Run[4])
	{
		runAnimSpeed = 1.2f;
		runStaminar = 4.0f;
		runSpeed = 13.0;
		runLevel = 5;
	}
	else if (runExp >= requiredExp_Run[3])
	{
		runAnimSpeed = 1.1f;
		runStaminar = 6.0f;
		runSpeed = 11.0;
		runLevel = 4;
	}
	else if (runExp >= requiredExp_Run[2])
	{
		runAnimSpeed = 1.0f;
		runStaminar = 7.0f;
		runSpeed = 9.0;
		runLevel = 3;
	}
	else if (runExp >= requiredExp_Run[1])
	{
		runAnimSpeed = 0.9f;
		runStaminar = 8.0f;
		runSpeed = 7.0;
		runLevel = 2;
	}
	else if (runExp >= requiredExp_Run[0])
	{
		runAnimSpeed = 0.8f;
		runStaminar = 9.0f;
		runSpeed = 6.0;
		runLevel = 1;
	}
}

void PlayerStatus::JumpExp()
{
	if (PLAYER->jumpCount >= requiredExp_Jump[4])
	{
		jumpStaminar = 5.0f;
		jumpPower = 15.0f;
		jumpLevel = 5;
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[3])
	{
		jumpStaminar = 6.0f;
		jumpPower = 14.0f;
		jumpLevel = 4;
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[2])
	{
		jumpStaminar = 7.0f;
		jumpPower = 13.0f;
		jumpLevel = 3;
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[1])
	{
		jumpStaminar = 8.0f;
		jumpPower = 12.0f;
		jumpLevel = 2;
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[0])
	{
		jumpStaminar = 9.0f;
		jumpPower = 11.0f;
		jumpLevel = 1;
	}
	ImGui::Text("staminar %f", jumpStaminar);
	ImGui::Text("power %f", jumpPower);
	ImGui::Text("level %d", jumpLevel);
}

