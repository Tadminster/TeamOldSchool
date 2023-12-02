#include "stdafx.h"
#include "Goblin.h"
#include "GoblinState.h"

Goblin_IdleState* Goblin_IdleState::instance;
Goblin_Idle2State* Goblin_Idle2State::instance;
Goblin_RunState* Goblin_RunState::instance;
Goblin_AttackState* Goblin_AttackState::instance;
Goblin_DeathState* Goblin_DeathState::instance;
//Idle 상태----------------------------------------------------------
void Goblin_IdleState::Idle(Goblin* goblin)
{
	if (goblin->GetActor()->anim->currentAnimator.animIdx != 0)
	{
		goblin->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 0);
	}
}
void Goblin_IdleState::Idle2(Goblin* goblin)
{
	goblin->SetState(G_IDLE2);
}
void Goblin_IdleState::Run(Goblin* goblin)
{
	goblin->SetState(G_RUN);
}
void Goblin_IdleState::Attack(Goblin* goblin)
{
	goblin->SetState(G_ATTACK);
}
void Goblin_IdleState::Death(Goblin* goblin)
{
	goblin->SetState(G_DEATH);
}
//Idle2 상태----------------------------------------------------------
void Goblin_Idle2State::Idle(Goblin* goblin)
{
	goblin->SetState(G_IDLE);
}
void Goblin_Idle2State::Idle2(Goblin* goblin)
{
	if (goblin->GetActor()->anim->currentAnimator.animIdx != 1)
	{
		goblin->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 1);
	}
	if (goblin->GetActor()->anim->currentAnimator.animState == AnimationState::STOP)
	{
		goblin->SetState(G_IDLE);
	}
}
void Goblin_Idle2State::Run(Goblin* goblin)
{
	goblin->SetState(G_RUN);
}
void Goblin_Idle2State::Attack(Goblin* goblin)
{
	goblin->SetState(G_ATTACK);
}
void Goblin_Idle2State::Death(Goblin* goblin)
{
	goblin->SetState(G_DEATH);
}
//Run 상태----------------------------------------------------------
void Goblin_RunState::Idle(Goblin* goblin)
{
	goblin->SetState(G_IDLE);
}
void Goblin_RunState::Idle2(Goblin* goblin)
{
	goblin->SetState(G_IDLE2);
}
void Goblin_RunState::Run(Goblin* goblin)
{
	if (goblin->GetActor()->anim->currentAnimator.animIdx != 2)
	{
		goblin->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
}
void Goblin_RunState::Attack(Goblin* goblin)
{
	goblin->SetState(G_ATTACK);
}
void Goblin_RunState::Death(Goblin* goblin)
{
	goblin->SetState(G_DEATH);
}
//Attack 상태----------------------------------------------------------
void Goblin_AttackState::Idle(Goblin* goblin)
{
	goblin->SetState(G_IDLE);
}
void Goblin_AttackState::Idle2(Goblin* goblin)
{
	goblin->SetState(G_IDLE2);
}
void Goblin_AttackState::Run(Goblin* goblin)
{
	goblin->SetState(G_RUN);
}
void Goblin_AttackState::Attack(Goblin* goblin)
{
	if (goblin->GetActor()->anim->currentAnimator.animIdx != 3)
	{
		goblin->GetActor()->anim->ChangeAnimation(AnimationState::LOOP, 3);
	}
}
void Goblin_AttackState::Death(Goblin* goblin)
{
	goblin->SetState(G_DEATH);
}
//Death 상태----------------------------------------------------------
void Goblin_DeathState::Idle(Goblin* goblin){}
void Goblin_DeathState::Idle2(Goblin* goblin){}
void Goblin_DeathState::Run(Goblin* goblin){}
void Goblin_DeathState::Attack(Goblin* goblin){}
void Goblin_DeathState::Death(Goblin* goblin)
{
	if (goblin->GetActor()->anim->currentAnimator.animIdx != 4)
	{
		goblin->GetActor()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 4);
	}
	if (goblin->deathTime < 3.0f) goblin->deathTime += DELTA;
	//if (goblin->deathTime >= 3.0f) goblin->~Goblin();
}
