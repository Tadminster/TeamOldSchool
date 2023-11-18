#pragma once
//���� ��� cpp�� �ִµ� �ν��� ����!
#include "Elder.h"

#define E_OPENING Elder_OpeningState::GetInstance()
#define E_IDLE Elder_IdleState::GetInstance()
#define E_WALK Elder_WalkState::GetInstance()
#define E_STOMP Elder_StompState::GetInstance()
class Elder;

class ElderState
{
protected:
	void SetElderState(Elder* elder, ElderState* state)
	{
		elder->SetState(state);
	}
public:
	virtual void Opening(Elder* elder) = 0;
	virtual void Idle(Elder* elder) = 0;
	virtual void Walk(Elder* elder) = 0;
	virtual void Stomp(Elder* elder) = 0;
	virtual void VineShoot(Elder* elder) = 0;
	virtual void Summon(Elder* elder) = 0;
	virtual void Death(Elder* elder) = 0;
};
//Opening Ŭ����----------------------------------------------------------
class Elder_OpeningState : public ElderState
{
	static Elder_OpeningState* instance;
public:
	static Elder_OpeningState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_OpeningState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void VineShoot(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Idle Ŭ����----------------------------------------------------------
class Elder_IdleState : public ElderState
{
	static Elder_IdleState* instance;
public:
	static Elder_IdleState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_IdleState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void VineShoot(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Walk Ŭ����----------------------------------------------------------
class Elder_WalkState : public ElderState
{
	static Elder_WalkState* instance;
public:
	static Elder_WalkState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_WalkState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void VineShoot(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Stomp Ŭ����----------------------------------------------------------
class Elder_StompState : public ElderState
{
	static Elder_StompState* instance;
public:
	static Elder_StompState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_StompState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void VineShoot(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};