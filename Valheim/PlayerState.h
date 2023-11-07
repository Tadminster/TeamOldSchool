#pragma once
//State 클래스들을 제어하기위한 추상클래스
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
	virtual void Idle();
	virtual void Move();
};
//Move 클래스----------------------------------------------------------
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