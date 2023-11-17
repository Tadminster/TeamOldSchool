#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"
Elder_OpeningState* Elder_OpeningState::instance;
Elder_IdleState* Elder_IdleState::instance;
Elder_WalkState* Elder_WalkState::instance;
//Opening 상태--------------------------------------------------------------------------
void Elder_OpeningState::Opening(Elder* elder)
{
	elder->SetState(Elder_OpeningState::GetInstance());
}

void Elder_OpeningState::Idle(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 1)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	elder->SetState(Elder_IdleState::GetInstance());
}

void Elder_OpeningState::Walk(Elder* elder) {}
void Elder_OpeningState::Stomp(Elder* elder) {}
void Elder_OpeningState::VineShoot(Elder* elder) {}
void Elder_OpeningState::Summon(Elder* elder) {}
void Elder_OpeningState::Death(Elder* elder) {}
//Idle 상태--------------------------------------------------------------------------
void Elder_IdleState::Opening(Elder* elder) {}
void Elder_IdleState::Idle(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 1)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	elder->SetState(Elder_IdleState::GetInstance());
}

void Elder_IdleState::Walk(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 2)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
	elder->SetState(Elder_WalkState::GetInstance());
}

void Elder_IdleState::Stomp(Elder* elder)
{
}

void Elder_IdleState::VineShoot(Elder* elder)
{
}

void Elder_IdleState::Summon(Elder* elder)
{
}

void Elder_IdleState::Death(Elder* elder)
{
}
//Walk 상태--------------------------------------------------------------------------
void Elder_WalkState::Opening(Elder* elder) {}
void Elder_WalkState::Idle(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 1)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	elder->SetState(Elder_IdleState::GetInstance());
}
void Elder_WalkState::Walk(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 2)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
	//elder->SetState(Elder_WalkState::GetInstance());
}

void Elder_WalkState::Stomp(Elder* elder)
{
}

void Elder_WalkState::VineShoot(Elder* elder)
{
}

void Elder_WalkState::Summon(Elder* elder)
{
}

void Elder_WalkState::Death(Elder* elder)
{
}
