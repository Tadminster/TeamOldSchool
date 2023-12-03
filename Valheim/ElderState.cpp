#include "stdafx.h"
#include "Elder.h"
#include "ElderState.h"

Elder_OpeningState* Elder_OpeningState::instance;
Elder_IdleState* Elder_IdleState::instance;
Elder_WalkState* Elder_WalkState::instance;
Elder_StompState* Elder_StompState::instance;
Elder_JumpAttackState* Elder_JumpAttackState::instance;
Elder_SummonState* Elder_SummonState::instance;
Elder_DeathState* Elder_DeathState::instance;

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
void Elder_OpeningState::Walk(Elder* elder) {}
void Elder_OpeningState::Stomp(Elder* elder) {}
void Elder_OpeningState::JumpAttack(Elder* elder) {}
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
void Elder_IdleState::JumpAttack(Elder* elder)
{
	elder->SetState(E_JumpAttack);
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
void Elder_WalkState::JumpAttack(Elder* elder)
{
	elder->SetState(E_JumpAttack);
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
void Elder_StompState::JumpAttack(Elder* elder)
{
	elder->SetState(E_JumpAttack);
}
void Elder_StompState::Summon(Elder* elder)
{
	elder->SetState(E_SUMMON);
}
void Elder_StompState::Death(Elder* elder)
{
}

//JumpAttack 상태--------------------------------------------------------------------------
void Elder_JumpAttackState::Opening(Elder* elder) {}
void Elder_JumpAttackState::Idle(Elder* elder)
{
	elder->SetState(E_IDLE);
}
void Elder_JumpAttackState::Walk(Elder* elder)
{
	elder->SetState(E_WALK);
}
void Elder_JumpAttackState::Stomp(Elder* elder)
{
	elder->SetState(E_STOMP);
}
void Elder_JumpAttackState::JumpAttack(Elder* elder)
{
	if (elder->GetJumpAttackMotion() == 0)
	{
		if (elder->GetActor()->anim->currentAnimator.animIdx != 8)
		{
			elder->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 8);
		}
	}
	else if (elder->GetJumpAttackMotion() == 1)
	{
		if (elder->GetActor()->anim->currentAnimator.animIdx != 11)
		{
			elder->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 11);
		}
		if (elder->GetActor()->anim->currentAnimator.animIdx == 11)
		{
			if (elder->GetActor()->anim->currentAnimator.currentFrame == 10)
				SOUND->Play(ELDER_JUMPATTACK);
		}
	}
	
}
void Elder_JumpAttackState::Summon(Elder* elder)
{
	elder->SetState(E_SUMMON);
}
void Elder_JumpAttackState::Death(Elder* elder)
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
void Elder_SummonState::JumpAttack(Elder* elder)
{
	elder->SetState(E_JumpAttack);
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
//Death 상태--------------------------------------------------------------------------
void Elder_DeathState::Opening(Elder* elder) {}
void Elder_DeathState::Idle(Elder* elder) {}
void Elder_DeathState::Walk(Elder* elder){}
void Elder_DeathState::Stomp(Elder* elder){}
void Elder_DeathState::JumpAttack(Elder* elder){}
void Elder_DeathState::Summon(Elder* elder){}
void Elder_DeathState::Death(Elder* elder)
{
	if (elder->GetActor()->anim->currentAnimator.animIdx != 7)
	{
		elder->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 7);
	}

	elder->GetActor()->collider->SetLocalPos(Vector3(0, 1, -3.85f));
	elder->GetActor()->collider->scale = Vector3(1.8f, 1, 3.8f);

	
}
