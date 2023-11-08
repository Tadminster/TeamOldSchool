#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;

void IdleState::Idle()
{
	player->GetPlayer()->
		anim->ChangeAnimation(AnimationState::LOOP, 0);
}

void IdleState::Move()
{
	player->GetPlayer()->MoveWorldPos(player->GetPlayer()->GetForward() * 10.0f * DELTA);
	player->GetPlayer()->
		anim->ChangeAnimation(AnimationState::LOOP, 1);
	SetPlayerState(MoveState::GetInstance());
}

void MoveState::Idle()
{
	player->GetPlayer()->
		anim->ChangeAnimation(AnimationState::LOOP, 0);
	SetPlayerState(IdleState::GetInstance());
}

void MoveState::Move()
{
	player->GetPlayer()->MoveWorldPos(player->GetPlayer()->GetForward() * 10.0f * DELTA);
	player->GetPlayer()->
		anim->ChangeAnimation(AnimationState::LOOP, 1);
}
