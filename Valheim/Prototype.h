#include "stdafx.h"

#pragma once
class Prototype
{
protected:
	Actor*		actor;
	Ray			groundRay;
	float		hitPoint;
public:
	virtual ~Prototype() 
	{ 
		actor->Release(); 
		actor = nullptr;
	}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
	virtual void RenderHierarchy() = 0;

	virtual Actor* GetActor() { return actor; }

	// @brief 오브젝트에 데미지를 줘야할 때 호출하는 함수
	// @param damage 데미지량
	virtual bool ReceivedDamageEvent(float damage) = 0;

	// @brief 오브젝트가 파괴되는 조건을 검사하는 함수
	// @brief 예를 들어, 체력이 0 이하이거나 아이템이 땅에 드랍되고 일정시간이 지났을 때
	// @return 파괴되어야 하는 경우 true, 아닌 경우 false
	virtual bool IsDestroyed() = 0;

	// @brief 오브젝트가 파괴되었을 때 호출되는 함수
	// @brief 예를 들어, 나무가 파괴되면 나뭇잎 떨어지는 파티클을 재생하고, 통나무 오브젝트를 생성.
	// @brief 몬스터가 파괴되면 아이템을 드랍.
	virtual void DestructionEvent() = 0;
};

