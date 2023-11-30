#pragma once
class PlayerStatus
{
	friend class Player;
	int			totalLevel = 0;
	//Run-------------------------------------------------------------
	const float requiredExp_Run[5] = { 5.0f,10.0f,15.0f,20.0f,25.0f };
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
	//fist---------------------------------------------------------------
	const int	requiredExp_Fist[5] = { 4,10,16,24,32 };
	float		fistAnimSpeed = 0.7f;
	float		fistStaminar = 5.0f;
	int			fistLevel = 0;
	//swing--------------------------------------------------------------
	const int	requiredExp_Swing[5] = { 4,10,16,24,32 };
	float		swingAnimSpeed = 0.7f;
	float		swingStaminar = 5.0f;
	int			swingLevel = 0;
	////axe----------------------------------------------------------------
	const int	requiredExp_Axe[5] = { 2,5,8,12,16 };
	float		axeAnimSpeed = 0.7f;
	float		axeStaminar = 5.0f;
	int			axeLevel = 0;
	//shield-------------------------------------------------------------
	const float	requiredExp_Shield[5] = { 5.0f,10.0f,15.0f,20.0f,25.0f };
	float		shieldExp = 0;
	float		shieldSpeed = 1.0;
	float		shieldStaminar = 4.0f;
	int			shieldLevel = 0;
	//Block-------------------------------------------------------------
	const int	requiredExp_Block[5] = { 1,3,5,7,10 };
	float		blockStaminar = 10.0f;
	float		blockAbility = 0;
	int			blcokdLevel = 0;
public:
	PlayerStatus();
	~PlayerStatus();
	void Update();
	void RunExp();
	void JumpExp();
	void FistExp();
	void SwingExp();
	void AxeExp();
	void ShieldExp();
	void BlockExp();
};

