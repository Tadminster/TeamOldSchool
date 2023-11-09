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
	//���� Idle�� ����
	//SetPlayerState(IdleState::GetInstance());
}
void IdleState::Walk(unsigned char key)
{
	//�÷��̾� ���� Idle -> Walk ��ȯ
	SetPlayerState(WalkState::GetInstance());
}
void IdleState::Run(unsigned char key)
{
	SetPlayerState(RunState::GetInstance());
}
void IdleState::Jump()
{
	SetPlayerState(JumpState::GetInstance());
}
void IdleState::Swing()
{
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
void WalkState::Walk(unsigned char key)
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 2 && !PLAYER->GetPlayerJump()) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 2);
	}
	//����Ű �Է°��� ���� Walk �̵�
	switch (key) {
	case 'W':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * WALKSPEED * DELTA);
		break;
	case 'A':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetRight() * WALKSPEED * DELTA);
		break;
	case 'S':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetForward() * WALKSPEED * DELTA);
		break;
	case 'D':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetRight() * WALKSPEED * DELTA);
		break;
	}
}
void WalkState::Run(unsigned char key)
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
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void RunState::Walk(unsigned char key)
{
	SetPlayerState(WalkState::GetInstance());
}
void RunState::Run(unsigned char key)
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 3 && !PLAYER->GetPlayerJump()) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 3);
	}

	switch (key) {
	case 'W':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * RUNSPEED * DELTA);
		break;
	case 'A':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetRight() * RUNSPEED * DELTA);
		break;
	case 'S':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetForward() * RUNSPEED * DELTA);
		break;
	case 'D':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetRight() * RUNSPEED * DELTA);
		break;
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
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void JumpState::Walk(unsigned char key)
{
	SetPlayerState(WalkState::GetInstance());
}
void JumpState::Run(unsigned char key)
{
	SetPlayerState(RunState::GetInstance());
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
	SetPlayerState(SwingState::GetInstance());
}
//Swing Ŭ����----------------------------------------------------------
void SwingState::Idle()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	SetPlayerState(IdleState::GetInstance());
}
void SwingState::Walk(unsigned char key)
{
	SetPlayerState(WalkState::GetInstance());
}
void SwingState::Run(unsigned char key)
{
	SetPlayerState(RunState::GetInstance());
}
void SwingState::Jump()
{
	SetPlayerState(JumpState::GetInstance());
}
void SwingState::Swing()
{
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 5) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 5);
	}
}


