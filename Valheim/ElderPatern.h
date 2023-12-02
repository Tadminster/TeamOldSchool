#pragma once
#include "Elder.h"
#define BUNDLENUM 7
class Elder;
class ElderPatern
{
	class ElderStomp*		stomp;
	class ElderJumpAttack*	jumpAttack;
	class ElderSummonSpear* summonSpear;


protected:
	Vector3			targetInfo = {};
	Vector3			dir = {};
	float			distance = 0;

	vector<Actor*>  spearBundle = {};
	Ray				spearRay;
	Vector3			spearY = {};

	int				spearCount = 0;
	int				spearIdx = 0;
	float			spearHitTime = 0;
	

public:
	ElderPatern();
	ElderPatern(Elder* elder);
	~ElderPatern();
	void Update();
	void Render();
	void StompPatern(Elder* elder);
	void JumpAttackPatern(Elder* elder);
	void SummonPatern(Elder* elder);
};
//발 찍기 클래스-----------------------------------------------
class ElderStomp : public ElderPatern
{
	
public:
	ElderStomp();
	~ElderStomp();
	void ElderStompPatern(Elder* elder);
};
//점프어택 클래스-----------------------------------------------
class ElderJumpAttack : public ElderPatern
{
	int   respawnPhase = 0;
	float respawnTime = 0;
	float interval = 0;
	float jumpAttackToIdle = 0;
	bool  totalRender = false;
public:
	ElderJumpAttack(Elder* elder);
	~ElderJumpAttack();
	void Update();
	void Render();
	void ElderJumpAttackPatern(Elder* elder);
};
//창 소환 클래스-----------------------------------------------
class ElderSummonSpear : public ElderPatern
{
	float summonTime = 0;
	float summonToIdle = 0;
public:
	ElderSummonSpear();
	~ElderSummonSpear();
	void Update();
	void Render();
	void SummonSpearPatern(Elder* elder);
};
