#pragma once
#include "Elder.h"
#define SPEARNUM 10
class Elder;
class ElderPatern
{
	class ElderStomp* stomp;
	class ElderSummonSpear* summonSpear;

	/*Vector3 middlePosition = {};
	Vector3 squarePosition[3][3] = {};*/

public:
	ElderPatern(Elder* elder);
	~ElderPatern();
	void Update();
	void Render();
	void StompPatern(Elder* elder);
	void VineShootPatern(Elder* elder);
	void SummonPatern(Elder* elder);
};

class ElderStomp
{
	
public:
	ElderStomp();
	~ElderStomp();
	void ElderStompPatern(Elder* elder);
};

class ElderVineShoot
{

public:
	ElderVineShoot();
	~ElderVineShoot();
	void ElderVineShootPatern(Elder* elder);
};

class ElderSummonSpear
{
	Actor*			spear[SPEARNUM] = {};
	Ray				spearRay[SPEARNUM];
	Vector3			spearY[SPEARNUM] = {};
	Vector3			spearPosition = {};
	Vector3			targetInfo = {};
	Vector3			dir = {};
	float			distance = 0;
	
	int				spearIdx = 0;
	float			summonTime = 0;
	float			summonToIdle = 0;
	float			interval = 0;
public:
	ElderSummonSpear();
	~ElderSummonSpear();
	void Update();
	void Render();
	void SummonSpearPatern(Elder* elder);
};
