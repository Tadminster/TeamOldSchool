#pragma once
#define SWINGSPEED 1
#define WALKSPEED 3
#define RUNSPEED 7
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
	virtual void Fist() = 0;
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
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
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
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
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
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
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
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
};
//Fist Ŭ����----------------------------------------------------------
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
	void Idle() override;
	void Walk() override;
	void Run() override;
	void Jump() override;
	void Fist() override;
	void Swing() override;
};
