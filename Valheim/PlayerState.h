#pragma once
#define SWINGSPEED 1
#define WALKSPEED 5
#define RUNSPEED 10
//State Ŭ�������� �����ϱ����� �߻�Ŭ����
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
	virtual void Swing() = 0;
};
//Idle Ŭ����----------------------------------------------------------
class IdleState : public PlayerState
{
	static IdleState* instance;
public:
	static IdleState* GetInstance()
	{
		if (instance == nullptr) instance = new IdleState();
		return instance;
	}
	virtual void Idle();
	virtual void Walk();
	virtual void Run();
	virtual void Jump();
	virtual void Swing();
};
//Walk Ŭ����----------------------------------------------------------
class WalkState : public PlayerState
{
	static WalkState* instance;
public:
	static WalkState* GetInstance()
	{
		if (instance == nullptr) instance = new WalkState();
		return instance;
	}
	virtual void Idle();
	virtual void Walk();
	virtual void Run();
	virtual void Jump();
	virtual void Swing();
};
//Run Ŭ����----------------------------------------------------------
class RunState : public PlayerState
{
	static RunState* instance;
public:
	static RunState* GetInstance()
	{
		if (instance == nullptr) instance = new RunState();
		return instance;
	}
	virtual void Idle();
	virtual void Walk();
	virtual void Run();
	virtual void Jump();
	virtual void Swing();
};
//Jump Ŭ����----------------------------------------------------------
class JumpState : public PlayerState
{
	static JumpState* instance;
public:
	static JumpState* GetInstance()
	{
		if (instance == nullptr) instance = new JumpState();
		return instance;
	}
	virtual void Idle();
	virtual void Walk();
	virtual void Run();
	virtual void Jump();
	virtual void Swing();
};
//Swing Ŭ����----------------------------------------------------------
class SwingState : public PlayerState
{
	static SwingState* instance;
public:
	static SwingState* GetInstance()
	{
		if (instance == nullptr) instance = new SwingState();
		return instance;
	}
	virtual void Idle();
	virtual void Walk();
	virtual void Run();
	virtual void Jump();
	virtual void Swing();
};
