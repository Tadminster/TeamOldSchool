#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerSound.h"

PlayerSound::PlayerSound()
{
}
PlayerSound::~PlayerSound()
{
}
void PlayerSound::Update()
{
	Walk();
	Run();
	Fist();
	Swing();
}
void PlayerSound::Walk()
{
	if (PLAYER->state == WalkState::GetInstance())
	{
		if (PLAYER->GetActor()->GetWorldPos().y < 0)
		{
			if (TIMER->GetTick(soundTime, 0.5f))
			{
				SOUND->Stop(PLAYER_WALK_01);
				SOUND->Play(PLAYER_WALK_WATER_01);
			}
		}
		else
		{
			if (TIMER->GetTick(soundTime, 0.5f))
			{
				SOUND->Stop(PLAYER_WALK_WATER_01);
				SOUND->Play(PLAYER_WALK_01);
			}
		}
	}
	else
	{
		SOUND->Stop(PLAYER_WALK_WATER_01);
		SOUND->Stop(PLAYER_WALK_01);
	}
}
void PlayerSound::Run()
{
	if (PLAYER->state == RunState::GetInstance())
	{
		if (PLAYER->GetActor()->GetWorldPos().y < 0)
		{
			if (TIMER->GetTick(soundTime, 0.45f))
			{
				SOUND->Stop(PLAYER_RUN_01);
				SOUND->Play(PLAYER_RUN_WATER_01);
			}
		}
		else
		{
			if (TIMER->GetTick(soundTime, 0.4f))
			{
				SOUND->Stop(PLAYER_RUN_WATER_01);
				SOUND->Play(PLAYER_RUN_01);
			}
		}
	}
	else
	{
		SOUND->Stop(PLAYER_RUN_WATER_01);
		SOUND->Stop(PLAYER_RUN_01);
	}
}
void PlayerSound::Fist()
{
	if (PLAYER->state == FistState::GetInstance())
	{
		if (PLAYER->equippedShield)
		{
			if (PLAYER->actor->anim->currentAnimator.currentFrame <= 12)
			{
				SOUND->Play(PLAYER_FIST_03);
			}
		}
		else
		{
			if (PLAYER->actor->anim->currentAnimator.currentFrame == 12)
			{
				SOUND->Play(PLAYER_FIST_01);
			}
			else if (PLAYER->actor->anim->currentAnimator.currentFrame == 20)
			{
				SOUND->Play(PLAYER_FIST_02);
			}
		}
	}
}
void PlayerSound::Swing()
{
	if (PLAYER->state == SwingState::GetInstance())
	{
		if (PLAYER->actor->anim->currentAnimator.currentFrame == 32) SOUND->Play(PLAYER_CLUB_SWING_01);
		else if(PLAYER->actor->anim->currentAnimator.currentFrame == 59) SOUND->Play(PLAYER_CLUB_SWING_02);
		else if(PLAYER->actor->anim->currentAnimator.currentFrame == 89) SOUND->Play(PLAYER_CLUB_SWING_03);
	}
}
