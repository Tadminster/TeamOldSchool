#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
WalkState* WalkState::instance;
RunState* RunState::instance;
JumpState* JumpState::instance;
FistState* FistState::instance;
SwingState* SwingState::instance;
AxeState* AxeState::instance;
ShieldState* ShieldState::instance;
DeathState* DeathState::instance;

//Idle Ŭ����----------------------------------------------------------
void IdleState::Idle()
{
	//�ִϸ��̼� �ߺ� ��� ����
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
}
void IdleState::Walk()
{
	//�÷��̾� ���� Idle -> Walk ��ȯ
	SetPlayerState(WalkState::GetInstance());
}
void IdleState::Run()
{
	//�÷��̾� ���� Idle -> Run ��ȯ
	SetPlayerState(RunState::GetInstance());
}
void IdleState::Jump()
{
	//�÷��̾� ���� Idle -> Jump ��ȯ
	SetPlayerState(JumpState::GetInstance());
}
void IdleState::Swing()
{
	//�÷��̾� ���� Idle -> Swing ��ȯ
	SetPlayerState(SwingState::GetInstance());
}
void IdleState::Fist()
{
	SetPlayerState(FistState::GetInstance());
}
void IdleState::Axe()
{
	SetPlayerState(AxeState::GetInstance());
}
void IdleState::Shield()
{
	SetPlayerState(ShieldState::GetInstance());
}
void IdleState::Death()
{
	SetPlayerState(DeathState::GetInstance());
}

//Walk Ŭ����----------------------------------------------------------
void WalkState::Idle()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void WalkState::Walk()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 2) 
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
}
void WalkState::Run()
{
	SetPlayerState(RunState::GetInstance());
}
void WalkState::Jump()
{
	SetPlayerState(JumpState::GetInstance());
}
void WalkState::Swing()
{
	SetPlayerState(SwingState::GetInstance());
}
void WalkState::Fist()
{
	SetPlayerState(FistState::GetInstance());
}
void WalkState::Axe()
{
	SetPlayerState(AxeState::GetInstance());
}
void WalkState::Shield()
{
	SetPlayerState(ShieldState::GetInstance());
}
void WalkState::Death()
{
	SetPlayerState(DeathState::GetInstance());
}

//Run Ŭ����----------------------------------------------------------
void RunState::Idle()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) 
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void RunState::Walk()
{
	SetPlayerState(WalkState::GetInstance());
}
void RunState::Run()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 3)
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 3);
	}
}
void RunState::Jump()
{
	SetPlayerState(JumpState::GetInstance());
}
void RunState::Swing()
{
	SetPlayerState(SwingState::GetInstance());
}
void RunState::Fist()
{
	SetPlayerState(FistState::GetInstance());
}
void RunState::Axe()
{
	SetPlayerState(AxeState::GetInstance());
}
void RunState::Shield()
{
	SetPlayerState(ShieldState::GetInstance());
}
void RunState::Death()
{
	SetPlayerState(DeathState::GetInstance());
}
//Jump Ŭ����----------------------------------------------------------
void JumpState::Idle() 
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) 
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void JumpState::Walk()
{
	//Jump���� Walk�� ���� �� ����
}
void JumpState::Run()
{
	//Jump���� Run���� ���� �� ����
}
void JumpState::Jump()
{
	PLAYER->actor->SetWorldPosY(PLAYER->actor->GetWorldPos().y + 0.3f);
	PLAYER->isLand = false;
	//PLAYER->gravity = -10.0f;
	PLAYER->actor->anim->ChangeAnimation(AnimationState::ONCE_LAST, 4);
	PLAYER->isJump = true;
}
void JumpState::Fist()
{
	//Jump���� Fist���� ���� �� ����
}
void JumpState::Swing()
{
	//Jump���� Swing���� ���� �� ����
}
void JumpState::Axe()
{
	//Jump���� Axe���� ���� �� ����
}
void JumpState::Shield()
{
	//Jump���� Shield���� ���� �� ����
}
void JumpState::Death()
{
	SetPlayerState(DeathState::GetInstance());
}
//Fist Ŭ����----------------------------------------------------------
void FistState::Idle() 
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void FistState::Walk() {}
void FistState::Run() {}
void FistState::Jump() {}
void FistState::Fist() 
{
	if (PLAYER->equippedShield)
	{
		if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 12)
		{
			PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 12);
		}

		if (PLAYER->GetPlayer()->anim->currentAnimator.currentFrame == 45)
		{
			PLAYER->GetPlayer()->anim->currentAnimator.nextFrame = 45;
		}
	}
	else
	{
		if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 8)
		{
			PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 8);
		}

		if (PLAYER->GetPlayer()->anim->currentAnimator.currentFrame == 63)
		{
			PLAYER->GetPlayer()->anim->currentAnimator.nextFrame = 63;
		}
	}
}
void FistState::Swing() {}
void FistState::Axe() {}
void FistState::Shield() {}
void FistState::Death() {}
//Swing Ŭ����----------------------------------------------------------
void SwingState::Idle()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void SwingState::Walk() {}
void SwingState::Run()  {}
void SwingState::Jump() {}
void SwingState::Fist() {}
void SwingState::Swing()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 6) 
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 6);
	}

	if (PLAYER->GetPlayer()->anim->currentAnimator.currentFrame == 136)
	{
		PLAYER->GetPlayer()->anim->currentAnimator.nextFrame = 136;
	}

	/*if (PLAYER->GetPlayer()->anim->GetPlayTime() >= 0.2f && PLAYER->GetPlayer()->anim->GetPlayTime() <= 0.7f)
	{
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * SWINGSPEED * DELTA);
	}*/
}
void SwingState::Axe() {}
void SwingState::Shield() {}
void SwingState::Death() {}
//Axe Ŭ����----------------------------------------------------------
void AxeState::Idle()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1)
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void AxeState::Walk() {}
void AxeState::Run() {}
void AxeState::Jump() {}
void AxeState::Fist() {}
void AxeState::Swing() {}
void AxeState::Axe()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 9)
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 9);
	}

	if (PLAYER->GetPlayer()->anim->currentAnimator.currentFrame == 68)
	{
		PLAYER->GetPlayer()->anim->currentAnimator.nextFrame = 68;
	}
}
void AxeState::Shield() {}
void AxeState::Death()
{
	SetPlayerState(DeathState::GetInstance());
}
//Shield Ŭ����----------------------------------------------------------
void ShieldState::Idle()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1)
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void ShieldState::Walk() {}
void ShieldState::Run() {}
void ShieldState::Jump()
{
	SetPlayerState(JumpState::GetInstance());
}
void ShieldState::Fist() 
{
	SetPlayerState(FistState::GetInstance());
}
void ShieldState::Swing() 
{
	SetPlayerState(SwingState::GetInstance());
}
void ShieldState::Axe()
{
	SetPlayerState(AxeState::GetInstance());
}
void ShieldState::Shield()
{
		if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('S') || INPUT->KeyPress('D'))
		{
			if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 11)
			{
				PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 11);
			}
		}
		else
		{
			if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 10)
			{
				PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::ONCE_LAST, 10);
			}
		}
}
void ShieldState::Death()
{
	SetPlayerState(DeathState::GetInstance());
}
//Death Ŭ����----------------------------------------------------------
void DeathState::Idle() {}
void DeathState::Walk() {}
void DeathState::Run() {}
void DeathState::Jump() {}
void DeathState::Fist() {}
void DeathState::Swing() {}
void DeathState::Axe() {}
void DeathState::Shield() {}
void DeathState::Death()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 7)
	{
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 7);
	}
}
