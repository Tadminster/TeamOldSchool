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
	if (totalLevel < 35)
	{
		RunExp();
		JumpExp();
		FistExp();
		SwingExp();
		AxeExp();
		ShieldExp();
		BlockExp();
		totalLevel = runLevel + jumpLevel + fistLevel + swingLevel + axeLevel + shieldLevel + blcokdLevel;
	}
}
void PlayerStatus::RunExp()
{
	if (runExp < requiredExp_Run[4])
	{
		if (PLAYER->state == RunState::GetInstance())
		{
			runExp += DELTA;
		}
	}

	if (runExp >= requiredExp_Run[4])
	{
		if (runLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			runAnimSpeed = 1.2f;
			runStaminar = 4.0f;
			runSpeed = 13.0;
			runLevel = 5;
		}
	}
	else if (runExp >= requiredExp_Run[3])
	{
		if (runLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			runAnimSpeed = 1.1f;
			runStaminar = 6.0f;
			runSpeed = 11.0;
			runLevel = 4;
		}
	}
	else if (runExp >= requiredExp_Run[2])
	{
		if (runLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			runAnimSpeed = 1.0f;
			runStaminar = 7.0f;
			runSpeed = 9.0;
			runLevel = 3;
		}
	}
	else if (runExp >= requiredExp_Run[1])
	{
		if (runLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			runAnimSpeed = 0.9f;
			runStaminar = 8.0f;
			runSpeed = 7.0;
			runLevel = 2;
		}
	}
	else if (runExp >= requiredExp_Run[0])
	{
		if (runLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			runAnimSpeed = 0.8f;
			runStaminar = 9.0f;
			runSpeed = 6.0;
			runLevel = 1;
		}
	}
}
void PlayerStatus::JumpExp()
{
	if (PLAYER->jumpCount >= requiredExp_Jump[4])
	{
		
		if (jumpLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			jumpStaminar = 5.0f;
			jumpPower = 20.0f;
			jumpLevel = 5;
		}
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[3])
	{
		
		if (jumpLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			jumpStaminar = 6.0f;
			jumpPower = 17.0f;
			jumpLevel = 4;
		}
		
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[2])
	{
		
		if (jumpLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			jumpStaminar = 7.0f;
			jumpPower = 15.0f;
			jumpLevel = 3;
		}
		
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[1])
	{
	
		if (jumpLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			jumpStaminar = 8.0f;
			jumpPower = 13.0f;
			jumpLevel = 2;
		}
	
	}
	else if (PLAYER->jumpCount >= requiredExp_Jump[0])
	{
		
		if (jumpLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			jumpStaminar = 9.0f;
			jumpPower = 11.0f;
			jumpLevel = 1;
		}
		
	}
}
void PlayerStatus::FistExp()
{
	if (PLAYER->fistCount >= requiredExp_Fist[4])
	{
		
		if (fistLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			fistAnimSpeed = 1.2f;
			fistStaminar = 2.0f;
			fistLevel = 5;
		}
	
	}
	else if (PLAYER->fistCount >= requiredExp_Fist[3])
	{
		if (fistLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			fistAnimSpeed = 1.1f;
			fistStaminar = 2.5f;
			fistLevel = 4;
		}
		
	}
	else if (PLAYER->fistCount >= requiredExp_Fist[2])
	{
		if (fistLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			fistAnimSpeed = 1.0f;
			fistStaminar = 3.0f;
			fistLevel = 3;
		}
		
	}
	else if (PLAYER->fistCount >= requiredExp_Fist[1])
	{
		if (fistLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			fistAnimSpeed = 0.9f;
			fistStaminar = 3.5f;
			fistLevel = 2;
		}
		
	}
	else if (PLAYER->fistCount >= requiredExp_Fist[0])
	{
		if (fistLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			fistAnimSpeed = 0.8f;
			fistStaminar = 4.0f;
			fistLevel = 1;
		}
	}
}
void PlayerStatus::SwingExp()
{
	if (PLAYER->swingCount >= requiredExp_Swing[4])
	{
		if (swingLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			swingAnimSpeed = 1.2f;
			swingStaminar = 2.0f;
			swingLevel = 5;
		}
		
	}
	else if (PLAYER->swingCount >= requiredExp_Swing[3])
	{
		if (swingLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			swingAnimSpeed = 1.1f;
			swingStaminar = 2.5f;
			swingLevel = 4;
		}
		
	}
	else if (PLAYER->swingCount >= requiredExp_Swing[2])
	{
		if (swingLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			swingAnimSpeed = 1.0f;
			swingStaminar = 3.0f;
			swingLevel = 3;
		}
		
	}
	else if (PLAYER->swingCount >= requiredExp_Swing[1])
	{
		if (swingLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			swingAnimSpeed = 0.9f;
			swingStaminar = 3.5f;
			swingLevel = 2;
		}
	
	}
	else if (PLAYER->swingCount >= requiredExp_Swing[0])
	{
		if (swingLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			swingAnimSpeed = 0.8f;
			swingStaminar = 4.0f;
			swingLevel = 1;
		}
		
	}
}
void PlayerStatus::AxeExp()
{
	if (PLAYER->axeCount >= requiredExp_Axe[4])
	{
		if (axeLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			axeAnimSpeed = 1.2f;
			axeStaminar = 2.0f;
			axeLevel = 5;
		}
	
	}
	else if (PLAYER->axeCount >= requiredExp_Axe[3])
	{
		if (axeLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			axeAnimSpeed = 1.1f;
			axeStaminar = 2.5f;
			axeLevel = 4;
		}
		
	}
	else if (PLAYER->axeCount >= requiredExp_Axe[2])
	{
		if (axeLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			axeAnimSpeed = 1.0f;
			axeStaminar = 3.0f;
			axeLevel = 3;
		}
		
	}
	else if (PLAYER->axeCount >= requiredExp_Axe[1])
	{
		if (axeLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			axeAnimSpeed = 0.9f;
			axeStaminar = 3.5f;
			axeLevel = 2;
		}
		
	}
	else if (PLAYER->axeCount >= requiredExp_Axe[0])
	{
		if (axeLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			axeAnimSpeed = 0.8f;
			axeStaminar = 4.0f;
			axeLevel = 1;
		}
		
	}
}
void PlayerStatus::ShieldExp()
{
	if (shieldExp < requiredExp_Shield[4])
	{
		if (PLAYER->state == ShieldState::GetInstance())
		{
			shieldExp += DELTA;
		}
	}

	if (shieldExp >= requiredExp_Shield[4])
	{
		if (shieldLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			shieldSpeed = 4.0f;
			shieldStaminar = 1.5f;
			shieldLevel = 5;
		}
	}
	else if (shieldExp >= requiredExp_Shield[3])
	{
		if (shieldLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			shieldSpeed = 3.0f;
			shieldStaminar = 2.0f;
			shieldLevel = 4;
		}
		
	}
	else if (shieldExp >= requiredExp_Shield[2])
	{
		if (shieldLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			shieldSpeed = 2.5f;
			shieldStaminar = 2.5f;
			shieldLevel = 3;
		}
		
	}
	else if (shieldExp >= requiredExp_Shield[1])
	{
		if (shieldLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			shieldSpeed = 2.0f;
			shieldStaminar = 3.0f;
			shieldLevel = 2;
		}
		
	}
	else if (shieldExp >= requiredExp_Shield[0])
	{
		if (shieldLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			shieldSpeed = 1.5f;
			shieldStaminar = 3.5f;
			shieldLevel = 1;
		}
		
	}
}
void PlayerStatus::BlockExp()
{
	if (PLAYER->blockCount >= requiredExp_Block[4])
	{
		if (blcokdLevel != 5)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			blockStaminar = 5.0f;
			blockAbility = 20;
			blcokdLevel = 5;
		}
		
	}
	else if (PLAYER->blockCount >= requiredExp_Block[3])
	{
		if (blcokdLevel != 4)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			blockStaminar = 6.0f;
			blockAbility = 15;
			blcokdLevel = 4;
		}
		
	}
	else if (PLAYER->blockCount >= requiredExp_Block[2])
	{
		if (blcokdLevel != 3)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			blockStaminar = 7.0f;
			blockAbility = 10;
			blcokdLevel = 3;
		}
		
	}
	else if (PLAYER->blockCount >= requiredExp_Block[1])
	{
		if (blcokdLevel != 2)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			blockStaminar = 8.0f;
			blockAbility = 5;
			blcokdLevel = 2;
		}
		
	}
	else if (PLAYER->blockCount >= requiredExp_Block[0])
	{
		if (blcokdLevel != 1)
		{
			PLAYER->maxHitpoint += 1.0f;
			PLAYER->hitPoint = PLAYER->maxHitpoint;
			PLAYER->maxStaminar += 1.0f;
			PLAYER->staminar = PLAYER->maxStaminar;
			blockStaminar = 9.0f;
			blockAbility = 2;
			blcokdLevel = 1;
		}
		
	}
}

