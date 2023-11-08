#include "stdafx.h"
#include "PlayerState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;

void IdleState::Idle()
{
	//애니메이션 중복 재생 방지
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 0) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 0);
	}
}

void IdleState::Move(char key)
{
	//애니메이션 중복 재생 방지
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	//방향키 입력값에 따른 이동
	switch (key) {
	case 'W':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * moveSpeed * DELTA);
		break;
	case 'A':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetRight() * moveSpeed * DELTA);
		break;
	case 'S':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetForward() * moveSpeed * DELTA);
		break;
	case 'D':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetRight() * moveSpeed * DELTA);
		break;
	}
	//플레이어 상태 Idle -> Move 전환
	SetPlayerState(MoveState::GetInstance());
}

void MoveState::Idle()
{
	//애니메이션 중복 재생 방지
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 0) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 0);
	}
	//플레이어 상태 Move -> Idle 전환
	SetPlayerState(IdleState::GetInstance());
}

void MoveState::Move(char key)
{
	//애니메이션 중복 재생 방지
	if (PLAYER->GetPlayer()->anim->currentAnimator.animIdx != 1) {
		PLAYER->GetPlayer()->anim->ChangeAnimation(AnimationState::LOOP, 1);
	}
	//방향키 입력값에 따른 이동
	switch (key) {
	case 'W':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetForward() * moveSpeed * DELTA);
		break;
	case 'A':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetRight() * moveSpeed * DELTA);
		break;
	case 'S':
		PLAYER->GetPlayer()->MoveWorldPos(-PLAYER->GetPlayer()->GetForward() * moveSpeed * DELTA);
		break;
	case 'D':
		PLAYER->GetPlayer()->MoveWorldPos(PLAYER->GetPlayer()->GetRight() * moveSpeed * DELTA);
		break;
	}
}
