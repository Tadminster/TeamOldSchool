#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"

Elder_OpeningState* Elder_OpeningState::instance;
Elder_IdleState* Elder_IdleState::instance;
Elder_WalkState* Elder_WalkState::instance;
Elder_StompState* Elder_StompState::instance;

//Opening 상태--------------------------------------------------------------------------
void Elder_OpeningState::Opening(Elder* elder)
{
	elder->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 0);
	if (elder->GetActor()->anim->GetPlayTime() >= 0.95f)
	{
		elder->SetState(E_IDLE);
	}
}
void Elder_OpeningState::Idle(Elder* elder)
{
	//elder->GetState()->Idle(elder);
	/*if (elder->GetActor()->anim->currentAnimator.animIdx != 1)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	elder->SetState(E_IDLE);*/
}
//Opening을 그냥 FSM에서 뺄까..?
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
}
void Elder_IdleState::Walk(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 2)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
	elder->SetState(E_WALK);
}
void Elder_IdleState::Stomp(Elder* elder)
{
	elder->SetState(E_STOMP);
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
	elder->SetState(E_IDLE);
}
void Elder_WalkState::Walk(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 2)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
}
void Elder_WalkState::Stomp(Elder* elder)
{
	elder->SetState(E_STOMP);
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
//Stomp 상태--------------------------------------------------------------------------
void Elder_StompState::Opening(Elder* elder) {}
void Elder_StompState::Idle(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 1)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	elder->SetState(E_IDLE);
}

void Elder_StompState::Walk(Elder* elder)
{
	elder->SetState(Elder_WalkState::GetInstance());
}

void Elder_StompState::Stomp(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 3)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 3);
	}
}

void Elder_StompState::VineShoot(Elder* elder)
{
}

void Elder_StompState::Summon(Elder* elder)
{
}

void Elder_StompState::Death(Elder* elder)
{
}
