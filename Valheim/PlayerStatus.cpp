#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
}

PlayerStatus::~PlayerStatus()
{
}

void PlayerStatus::RunExp()
{
	if (PLAYER->state == RunState::GetInstance())
	{
		runExp += DELTA;
	}

	if (runExp >= runLevel[4])
	{
		runAnimSpeed = 1.2f;
		runStaminar = 4.0f;
		runSpeed = 10.0;
	}
	else if (runExp >= runLevel[3])
	{
		runAnimSpeed = 1.1f;
		runStaminar = 6.0f;
		runSpeed = 8.0;
	}
	else if (runExp >= runLevel[2])
	{
		runAnimSpeed = 1.0f;
		runStaminar = 7.0f;
		runSpeed = 7.0;
	}
	else if (runExp >= runLevel[1])
	{
		runAnimSpeed = 0.9f;
		runStaminar = 8.0f;
		runSpeed = 7.0;
	}
	else if (runExp >= runLevel[0])
	{
		runAnimSpeed = 0.8f;
		runStaminar = 9.0f;
		runSpeed = 6.0;
	}
}
