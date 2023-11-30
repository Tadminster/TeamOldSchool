#pragma once
class PlayerStatus
{
	friend class Player;

	//const float runLevel[5] = { 10.0f,30.0f,60.0f,100.0f,150.0f };
	const float runLevel[5] = { 1.0f,3.0f,6.0f,10.0f,15.0f };
	float runExp = 0;
	float runAnimSpeed = 0.7f;
	float runSpeed = 5.0;
	float runStaminar = 10.0f;
public:
	PlayerStatus();
	~PlayerStatus();
	void RunExp();
};

