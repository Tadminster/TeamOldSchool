#pragma once
#define SWINGSPEED 1
#define WALKSPEED 3

//State 클래스들을 제어하기위한 추상클래스
class PlayerState
{
protected:
	void SetPlayerState(PlayerState* state)
	{
		PLAYER->SetState(state);
	}
public:
	virtual void Idle() = 0;
	virtual void Walk() = 0;
	virtual void Run() = 0;
	virtual void Jump() = 0;
	virtual void Fist() = 0;
	virtual void Swing() = 0;
	virtual void Axe() = 0;
	virtual void Shield() = 0;
	virtual void Death() = 0;
};
//Idle 클래스----------------------------------------------------------
class IdleState : public PlayerState
{
	static IdleState* instance;
public:
	static IdleState* GetInstance()
	{
		if (instance == nullptr) instance = new IdleState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Walk 클래스----------------------------------------------------------
class WalkState : public PlayerState
{
	static WalkState* instance;
public:
	static WalkState* GetInstance()
	{
		if (instance == nullptr) instance = new WalkState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Run 클래스----------------------------------------------------------
class RunState : public PlayerState
{
	static RunState* instance;
public:
	static RunState* GetInstance()
	{
		if (instance == nullptr) instance = new RunState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Jump 클래스----------------------------------------------------------
class JumpState : public PlayerState
{
	static JumpState* instance;
public:
	static JumpState* GetInstance()
	{
		if (instance == nullptr) instance = new JumpState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Fist 클래스----------------------------------------------------------
class FistState : public PlayerState
{
	static FistState* instance;
public:
	static FistState* GetInstance()
	{
		if (instance == nullptr) instance = new FistState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Swing 클래스----------------------------------------------------------
class SwingState : public PlayerState
{
	static SwingState* instance;
public:
	static SwingState* GetInstance()
	{
		if (instance == nullptr) instance = new SwingState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Axe 클래스----------------------------------------------------------
class AxeState : public PlayerState
{
	static AxeState* instance;
public:
	static AxeState* GetInstance()
	{
		if (instance == nullptr) instance = new AxeState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Shield 클래스----------------------------------------------------------
class ShieldState : public PlayerState
{
	static ShieldState* instance;
public:
	static ShieldState* GetInstance()
	{
		if (instance == nullptr) instance = new ShieldState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
//Death 클래스----------------------------------------------------------
class DeathState : public PlayerState
{
	static DeathState* instance;
public:
	static DeathState* GetInstance()
	{
		if (instance == nullptr) instance = new DeathState();
		return instance;
	}
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
	void Axe() override;
	void Shield() override;
	void Death() override;
};
