#pragma once
#include "Goblin.h"
#define G_IDLE Goblin_IdleState::GetInstance()
#define G_IDLE2 Goblin_Idle2State::GetInstance()
#define G_RUN Goblin_RunState::GetInstance()
#define G_ATTACK Goblin_AttackState::GetInstance()
#define G_DEATH Goblin_DeathState::GetInstance()
class Goblin;

class GoblinState
{
protected:
	void SetElderState(Goblin* goblin, GoblinState* state)
	{
		goblin->SetState(state);
	}
public:
	virtual void Idle(Goblin* goblin) = 0;
	virtual void Idle2(Goblin* goblin) = 0;
	virtual void Run(Goblin* goblin) = 0;
	virtual void Attack(Goblin* goblin) = 0;
	virtual void Death(Goblin* goblin) = 0;
};
//Idle 클래스----------------------------------------------------------
class Goblin_IdleState : public GoblinState
{
	static Goblin_IdleState* instance;
public:
	static Goblin_IdleState* GetInstance()
	{
		if (instance == nullptr) instance = new Goblin_IdleState();
		return instance;
	}
	void Idle(Goblin* goblin) override;
	void Idle2(Goblin* goblin) override;
	void Run(Goblin* goblin) override;
	void Attack(Goblin* goblin) override;
	void Death(Goblin* goblin) override;
};
//Idle2 클래스----------------------------------------------------------
class Goblin_Idle2State : public GoblinState
{
	static Goblin_Idle2State* instance;
public:
	static Goblin_Idle2State* GetInstance()
	{
		if (instance == nullptr) instance = new Goblin_Idle2State();
		return instance;
	}
	void Idle(Goblin* goblin) override;
	void Idle2(Goblin* goblin) override;
	void Run(Goblin* goblin) override;
	void Attack(Goblin* goblin) override;
	void Death(Goblin* goblin) override;
};
//Run 클래스----------------------------------------------------------
class Goblin_RunState : public GoblinState
{
	static Goblin_RunState* instance;
public:
	static Goblin_RunState* GetInstance()
	{
		if (instance == nullptr) instance = new Goblin_RunState();
		return instance;
	}
	void Idle(Goblin* goblin) override;
	void Idle2(Goblin* goblin) override;
	void Run(Goblin* goblin) override;
	void Attack(Goblin* goblin) override;
	void Death(Goblin* goblin) override;
};
//Attack 클래스----------------------------------------------------------
class Goblin_AttackState : public GoblinState
{
	static Goblin_AttackState* instance;
public:
	static Goblin_AttackState* GetInstance()
	{
		if (instance == nullptr) instance = new Goblin_AttackState();
		return instance;
	}
	void Idle(Goblin* goblin) override;
	void Idle2(Goblin* goblin) override;
	void Run(Goblin* goblin) override;
	void Attack(Goblin* goblin) override;
	void Death(Goblin* goblin) override;
};
//Death 클래스----------------------------------------------------------
class Goblin_DeathState : public GoblinState
{
	static Goblin_DeathState* instance;
public:
	static Goblin_DeathState* GetInstance()
	{
		if (instance == nullptr) instance = new Goblin_DeathState();
		return instance;
	}
	void Idle(Goblin* goblin) override;
	void Idle2(Goblin* goblin) override;
	void Run(Goblin* goblin) override;
	void Attack(Goblin* goblin) override;
	void Death(Goblin* goblin) override;
};

