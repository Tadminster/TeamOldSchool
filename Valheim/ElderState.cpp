#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"

Elder_OpeningState* Elder_OpeningState::instance;
Elder_IdleState* Elder_IdleState::instance;
Elder_WalkState* Elder_WalkState::instance;
Elder_StompState* Elder_StompState::instance;
Elder_VineShootState* Elder_VineShootState::instance;
Elder_SummonState* Elder_SummonState::instance;

//Opening 상태--------------------------------------------------------------------------
void Elder_OpeningState::Opening(Elder* elder)
{
	if (elder->GetActor()->anim->GetPlayTime() >= 0.95f)
	{
		elder->SetState(E_IDLE);
	}
}
void Elder_OpeningState::Idle(Elder* elder)
{
	elder->SetState(E_IDLE);
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
	elder->SetState(E_WALK);
}
void Elder_IdleState::Stomp(Elder* elder)
{
	elder->SetState(E_STOMP);
}
void Elder_IdleState::VineShoot(Elder* elder)
{
	elder->SetState(E_VINESHOOT);
}
void Elder_IdleState::Summon(Elder* elder)
{
	elder->SetState(E_SUMMON);
}
void Elder_IdleState::Death(Elder* elder)
{
}
//Walk 상태--------------------------------------------------------------------------
void Elder_WalkState::Opening(Elder* elder) {}
void Elder_WalkState::Idle(Elder* elder)
{
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
	elder->SetState(E_VINESHOOT);
}
void Elder_WalkState::Summon(Elder* elder)
{
	elder->SetState(E_SUMMON);
}
void Elder_WalkState::Death(Elder* elder)
{
}

//Stomp 상태--------------------------------------------------------------------------
void Elder_StompState::Opening(Elder* elder) {}
void Elder_StompState::Idle(Elder* elder)
{
	elder->SetState(E_IDLE);
}
void Elder_StompState::Walk(Elder* elder)
{
	elder->SetState(E_WALK);
}
void Elder_StompState::Stomp(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 3)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 3);
	}
}
void Elder_StompState::VineShoot(Elder* elder)
{
	elder->SetState(E_VINESHOOT);
}
void Elder_StompState::Summon(Elder* elder)
{
	elder->SetState(E_SUMMON);
}
void Elder_StompState::Death(Elder* elder)
{
}

//VineShoot 상태--------------------------------------------------------------------------
void Elder_VineShootState::Opening(Elder* elder) {}
void Elder_VineShootState::Idle(Elder* elder)
{
	elder->SetState(E_IDLE);
}
void Elder_VineShootState::Walk(Elder* elder)
{
	elder->SetState(E_WALK);
}
void Elder_VineShootState::Stomp(Elder* elder)
{
	elder->SetState(E_STOMP);
}
void Elder_VineShootState::VineShoot(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 4)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 4);
	}
}
void Elder_VineShootState::Summon(Elder* elder)
{
	elder->SetState(E_SUMMON);
}
void Elder_VineShootState::Death(Elder* elder)
{
}
//Summon 상태--------------------------------------------------------------------------
void Elder_SummonState::Opening(Elder* elder) {}
void Elder_SummonState::Idle(Elder* elder)
{
	elder->SetState(E_IDLE);
}
void Elder_SummonState::Walk(Elder* elder)
{
	elder->SetState(E_WALK);
}
void Elder_SummonState::Stomp(Elder* elder)
{
	elder->SetState(E_STOMP);
}
void Elder_SummonState::VineShoot(Elder* elder)
{
	elder->SetState(E_VINESHOOT);
}
void Elder_SummonState::Summon(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 5)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 5);
	}
}
void Elder_SummonState::Death(Elder* elder)
{
}
