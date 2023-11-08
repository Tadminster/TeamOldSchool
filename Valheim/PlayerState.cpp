#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;

void IdleState::Idle()
{
	PLAYER->GetActor()->
		anim->ChangeAnimation(AnimationState::LOOP, 0);
}

void IdleState::Move()
{
	PLAYER->GetActor()->
		anim->ChangeAnimation(AnimationState::LOOP, 1);
	SetPlayerState(MoveState::GetInstance());
}

void MoveState::Idle()
{
	PLAYER->GetActor()->
		anim->ChangeAnimation(AnimationState::LOOP, 0);
	SetPlayerState(IdleState::GetInstance());
}

void MoveState::Move()
{
	PLAYER->GetActor()->
		anim->ChangeAnimation(AnimationState::LOOP, 1);
}
