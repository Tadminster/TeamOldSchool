#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
WalkState* WalkState::instance;
RunState* RunState::instance;
JumpState* JumpState::instance;
SwingState* SwingState::instance;


//Idle 클래스----------------------------------------------------------
void IdleState::Idle()
{
	//애니메이션 중복 재생 방지
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
}
void IdleState::Walk()
{
	//플레이어 상태 Idle -> Walk 전환
	SetPlayerState(WalkState::GetInstance());
}
void IdleState::Run()
{
	//플레이어 상태 Idle -> Run 전환
	SetPlayerState(RunState::GetInstance());
}
void IdleState::Jump()
{
	//플레이어 상태 Idle -> Jump 전환
	SetPlayerState(JumpState::GetInstance());
}
void IdleState::Swing()
{
	//플레이어 상태 Idle -> Swing 전환
	SetPlayerState(SwingState::GetInstance());
}

//Walk 클래스----------------------------------------------------------
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

//Run 클래스----------------------------------------------------------
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
//Jump 클래스----------------------------------------------------------
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
	//Jump에서 Walk로 변할 수 없음
}
void JumpState::Run()
{
	//Jump에서 Run으로 변할 수 없음
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
	//Jump에서 Swing으로 변할 수 없음
}
//Swing 클래스----------------------------------------------------------
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


