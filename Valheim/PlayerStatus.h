#pragma once
class PlayerStatus
{
	friend class Player;

	//Run-------------------------------------------------------------
	const float requiredExp_Run[5] = { 10.0f,30.0f,50.0f,70.0f,100.0f };
	float		runExp = 0;
	float		runAnimSpeed = 0.7f;
	float		runSpeed = 5.0;
	float		runStaminar = 10.0f;
	int			runLevel = 0;
	//Jump-------------------------------------------------------------
	const int	requiredExp_Jump[5] = { 2,5,8,12,16 };
	float		jumpPower = 10.0f;
	float		jumpStaminar = 10.0f;
	int			jumpLevel = 0;

	//fist-------------------------------------------------------------
	//swing-------------------------------------------------------------
	//axe-------------------------------------------------------------
	//shield-------------------------------------------------------------
	
	
	
	

public:
	PlayerStatus();
	~PlayerStatus();
	void Update();
	void RunExp();
	void JumpExp();
	float GetJumpPower() { return jumpPower; }
};

