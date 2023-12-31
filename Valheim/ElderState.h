#pragma once
//엘더 헤더 cpp에 있는데 인식을 못함!
#include "Elder.h"

#define E_OPENING Elder_OpeningState::GetInstance()
#define E_IDLE Elder_IdleState::GetInstance()
#define E_WALK Elder_WalkState::GetInstance()
#define E_STOMP Elder_StompState::GetInstance()
#define E_JumpAttack Elder_JumpAttackState::GetInstance()
#define E_SUMMON Elder_SummonState::GetInstance()
#define E_DEATH Elder_DeathState::GetInstance()
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
	virtual void JumpAttack(Elder* elder) = 0;
	virtual void Summon(Elder* elder) = 0;
	virtual void Death(Elder* elder) = 0;
};
//Opening 클래스----------------------------------------------------------
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
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Idle 클래스----------------------------------------------------------
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
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Walk 클래스----------------------------------------------------------
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
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Stomp 클래스----------------------------------------------------------
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
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//JumpAttack 클래스----------------------------------------------------------
class Elder_JumpAttackState : public ElderState
{
	static Elder_JumpAttackState* instance;
public:
	static Elder_JumpAttackState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_JumpAttackState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Summon 클래스----------------------------------------------------------
class Elder_SummonState : public ElderState
{
	static Elder_SummonState* instance;
public:
	static Elder_SummonState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_SummonState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
//Death 클래스----------------------------------------------------------
class Elder_DeathState : public ElderState
{
	static Elder_DeathState* instance;
public:
	static Elder_DeathState* GetInstance()
	{
		if (instance == nullptr) instance = new Elder_DeathState();
		return instance;
	}
	void Opening(Elder* elder) override;
	void Idle(Elder* elder) override;
	void Walk(Elder* elder) override;
	void Stomp(Elder* elder) override;
	void JumpAttack(Elder* elder) override;
	void Summon(Elder* elder) override;
	void Death(Elder* elder) override;
};
