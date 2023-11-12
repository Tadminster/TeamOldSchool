#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
WalkState* WalkState::instance;
RunState* RunState::instance;
JumpState* JumpState::instance;
SwingState* SwingState::instance;


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
	PLAYER->gravity = -10.0f;
	PLAYER->actor->anim->ChangeAnimation(AnimationState::ONCE_LAST, 4);
	PLAYER->isJump = true;
}
void JumpState::Swing()
{
	//Jump���� Swing���� ���� �� ����
}
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
void SwingState::Swing()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 6) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 6);
	}

	if (PLAYER->GetPlayer()->anim->GetPlayTime() >= 0.2f && PLAYER->GetPlayer()->anim->GetPlayTime()<=0.7f)
	{
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * SWINGSPEED * DELTA);
	}
}


