#pragma once
#include "Elder.h"
#define BUNDLENUM 5
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
//발 찍기 클래스-----------------------------------------------
class ElderStomp
{
	
public:
	ElderStomp();
	~ElderStomp();
	void ElderStompPatern(Elder* elder);
};
//Vine Shoot 클래스-----------------------------------------------
class ElderVineShoot
{

public:
	ElderVineShoot();
	~ElderVineShoot();
	void ElderVineShootPatern(Elder* elder);
};
//창 소환 클래스-----------------------------------------------
class ElderSummonSpear
{
	vector<Actor*>  spearBundle = {};
	Ray				spearRay;
	Vector3			spearY = {};
	Vector3			spearPosition = {};
	Vector3			targetInfo = {};
	Vector3			dir = {};
	float			distance = 0;
	
	int				spearCount = 0;
	int				spearIdx = 0;
	int				subIdx = 0;
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
