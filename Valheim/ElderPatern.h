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
//�� ��� Ŭ����-----------------------------------------------
class ElderStomp
{
	
public:
	ElderStomp();
	~ElderStomp();
	void ElderStompPatern(Elder* elder);
};
//Vine Shoot Ŭ����-----------------------------------------------
class ElderVineShoot
{

public:
	ElderVineShoot();
	~ElderVineShoot();
	void ElderVineShootPatern(Elder* elder);
};
//â ��ȯ Ŭ����-----------------------------------------------
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
