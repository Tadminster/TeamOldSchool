#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerSound.h"

PlayerSound::PlayerSound()
{
}

PlayerSound::~PlayerSound()
{
}
//PLAYER_FIST_02
void PlayerSound::Update()
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
