#pragma once
//State Ŭ�������� �����ϱ����� �߻�Ŭ����
class PlayerState
{
protected:
	void SetPlayerState(PlayerState* state)
	{
		player->SetState(state);
	}
public:
	virtual void Idle() = 0;
	virtual void Move() = 0;
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
	virtual void Move();
};
//Move Ŭ����----------------------------------------------------------
class MoveState : public PlayerState
{
	static MoveState* instance;
public:
	static MoveState* GetInstance()
	{
		if (instance == nullptr) instance = new MoveState();
		return instance;
	}
	virtual void Idle();
	virtual void Move();
};