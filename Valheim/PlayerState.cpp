#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;

void IdleState::Idle()
{
	//�ִϸ��̼� �ߺ� ��� ����
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 0) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 0);
	}
}

void IdleState::Move(char key)
{
	//�ִϸ��̼� �ߺ� ��� ����
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	//����Ű �Է°��� ���� �̵�
	switch (key) {
	case 'W':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * 10.0f * DELTA);
		break;
	case 'A':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetRight() * 10.0f * DELTA);
		break;
	case 'S':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetForward() * 10.0f * DELTA);
		break;
	case 'D':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetRight() * 10.0f * DELTA);
		break;
	}
	//�÷��̾� ���� Idle -> Move ��ȯ
	SetPlayerState(MoveState::GetInstance());
}

void MoveState::Idle()
{
	//�ִϸ��̼� �ߺ� ��� ����
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 0) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 0);
	}
	//�÷��̾� ���� Move -> Idle ��ȯ
	SetPlayerState(IdleState::GetInstance());
}

void MoveState::Move(char key)
{
	//�ִϸ��̼� �ߺ� ��� ����
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	//����Ű �Է°��� ���� �̵�
	switch (key) {
	case 'W':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * 10.0f * DELTA);
		break;
	case 'A':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetRight() * 10.0f * DELTA);
		break;
	case 'S':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetForward() * 10.0f * DELTA);
		break;
	case 'D':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetRight() * 10.0f * DELTA);
		break;
	}
}
